// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004 Andreas Huggel <ahuggel@gmx.net>
 * 
 * This program is part of the Exiv2 distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
/*
  File:      actions.cpp
  Version:   $Name:  $ $Revision: 1.2 $
  Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
  History:   08-Dec-03, ahu: created
 */
// *****************************************************************************
#include "rcsid.hpp"
EXIV2_RCSID("@(#) $Name:  $ $Revision: 1.2 $ $RCSfile: actions.cpp,v $")

// *****************************************************************************
// included header files
#include "actions.hpp"
#include "exiv2.hpp"
#include "utils.hpp"
#include "exif.hpp"

// + standard includes
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <ctime>

// *****************************************************************************
// local declarations
namespace {

    // Convert a string "YYYY:MM:DD HH:MI:SS" to a struct tm type, 
    // returns 0 if successful
    int str2Tm(const std::string& timeStr, struct tm* tm);

    // Convert a string "YYYY:MM:DD HH:MI:SS" to a time type, -1 on error
    time_t str2Time(const std::string& timeStr);

    // Convert a time type to a string "YYYY:MM:DD HH:MI:SS", "" on error
    std::string time2Str(time_t time);

    // Return an error message for the return code of Exif::ExifData::read
    std::string exifReadError(int rc, const std::string& path);

    // Return an error message for the return code of Exif::ExifData::write
    std::string exifWriteError(int rc, const std::string& path);

}

// *****************************************************************************
// class member definitions
namespace Action {

    Task::AutoPtr Task::clone() const
    {
        return AutoPtr(clone_());
    }

    TaskFactory* TaskFactory::instance_ = 0;

    TaskFactory& TaskFactory::instance()
    {
        if (0 == instance_) {
            instance_ = new TaskFactory;
        }
        return *instance_;
    } // TaskFactory::instance

    void TaskFactory::registerTask(TaskType type, Task::AutoPtr task)
    {
        Registry::iterator i = registry_.find(type);
        if (i != registry_.end()) {
            delete i->second;
        }
        registry_[type] = task.release();
    } // TaskFactory::registerTask

    TaskFactory::TaskFactory()
    {
        // Register a prototype of each known task
        registerTask(adjust,  Task::AutoPtr(new Adjust));
        registerTask(print,   Task::AutoPtr(new Print));
        registerTask(rename,  Task::AutoPtr(new Rename));
    } // TaskFactory c'tor

    Task::AutoPtr TaskFactory::create(TaskType type)
    {
        Registry::const_iterator i = registry_.find(type);
        if (i != registry_.end() && i->second != 0) {
            Task* t = i->second;
            return t->clone();
        }
        return Task::AutoPtr(0);
    } // TaskFactory::create

    int Print::run(const std::string& path)
    try {
        Exif::ExifData exifData;
        int rc = exifData.read(path);
        if (rc) {
            std::cerr << exifReadError(rc, path) << "\n";
            return rc;
        }
        Exif::ExifData::const_iterator md;
        for (md = exifData.begin(); md != exifData.end(); ++md) {
            std::cout << "0x" << std::setw(4) << std::setfill('0') << std::right
                      << std::hex << md->tag() << " " 
                      << std::setw(9) << std::setfill(' ') << std::left
                      << md->ifdItem() << " "
                      << std::setw(27) << std::setfill(' ') << std::left
                      << md->tagName() << " "
                      << std::dec << md->value() << "\n";
        }
        return 0;
    }
    catch(const Exif::Error& e)
    {
        std::cerr << "Exif exception in print action for file " 
                  << path << ":\n" << e << "\n";
        return 1;
    } // Print::run

    Print::AutoPtr Print::clone() const
    {
        return AutoPtr(dynamic_cast<Print*>(clone_()));
    }

    Task* Print::clone_() const
    {
        return new Print(*this);
    }

    int Rename::run(const std::string& path)
    try {
        Exif::ExifData exifData;
        int rc = exifData.read(path);
        if (rc) {
            std::cerr << exifReadError(rc, path) << "\n";
            return rc;
        }
        std::string key = "Image.DateTime.DateTimeOriginal";
        Exif::ExifData::iterator md = exifData.findKey(key);
        if (md == exifData.end()) {
            std::cerr << "Metadatum with key `" << key << "' "
                      << "not found in the file " << path << "\n";
            return 1;
        }
        std::string v = md->toString();
        if (v.length() == 0 || v[0] == ' ') {
            std::cerr << "Image file creation timestamp not set in the file " 
                      << path << "\n";
            return 1;
        }
        // Assemble the new filename from the timestamp
        struct tm tm;
        if (str2Tm(v, &tm) != 0) {
            std::cerr << "Failed to parse timestamp `" << v
                      << "' in the file " << path << "\n";
            return 1;
        }
        const size_t max = 1024;
        char basename[max];
        memset(basename, 0x0, max);
        if (strftime(basename, max, Params::instance().format_.c_str(), &tm) == 0) {
            std::cerr << "Filename format yields empty filename for the file "
                      << path << "\n";
            return 1;
        }
        std::string newPath 
            = Util::dirname(path) + "/" + basename + Util::suffix(path);
        if (   Util::dirname(newPath)  == Util::dirname(path)
            && Util::basename(newPath) == Util::basename(path)) {
            if (Params::instance().verbose_) {
                std::cout << "This file already has the correct name\n";
            }
            return 0;
        }
        if (Params::instance().verbose_) {
            std::cout << "Renaming file to " << newPath << "\n";
        }
        if (!Params::instance().force_ && Util::fileExists(newPath)) {
            std::cout << Params::instance().progname() 
                      << ": Overwrite `" << newPath << "'? ";
            std::string s;
            std::cin >> s;
            if (s[0] != 'y' && s[0] != 'Y') return 0;
        }
        if (::rename(path.c_str(), newPath.c_str()) == -1) {
            std::cerr << Params::instance().progname()  
                      << ": Failed to rename "
                      << path << " to " << newPath << ": "
                      << Util::strError() << "\n";
            return 1;
        }
        return 0;
    }
    catch(const Exif::Error& e)
    {
        std::cerr << "Exif exception in rename action for file " << path
                  << ":\n" << e << "\n";
        return 1;
    } // Rename::run

    Rename::AutoPtr Rename::clone() const
    {
        return AutoPtr(dynamic_cast<Rename*>(clone_()));
    }

    Task* Rename::clone_() const
    {
        return new Rename(*this);
    }

    int Adjust::run(const std::string& path)
    try {
        adjustment_ = Params::instance().adjustment_;

        Exif::ExifData exifData;
        int rc = exifData.read(path);
        if (rc) {
            std::cerr << exifReadError(rc, path) << "\n";
            return rc;
        }
        rc  = adjustDateTime(exifData, "Image.OtherTags.DateTime", path);
        rc += adjustDateTime(exifData, "Image.DateTime.DateTimeOriginal", path);
        rc += adjustDateTime(exifData, "Image.DateTime.DateTimeDigitized", path);
        if (rc) return 1;
        rc = exifData.write(path);
        if (rc) {
            std::cerr << exifWriteError(rc, path) << "\n";
        }
        return rc;
    }
    catch(const Exif::Error& e)
    {
        std::cerr << "Exif exception in adjust action for file " << path
                  << ":\n" << e << "\n";
        return 1;
    } // Adjust::run

    Adjust::AutoPtr Adjust::clone() const
    {
        return AutoPtr(dynamic_cast<Adjust*>(clone_()));
    }

    Task* Adjust::clone_() const
    {
        return new Adjust(*this);
    }

    int Adjust::adjustDateTime(Exif::ExifData& exifData,
                               const std::string& key, 
                               const std::string& path) const
    {
        Exif::ExifData::iterator md = exifData.findKey(key);
        if (md == exifData.end()) {
            // Key not found. That's ok, we do nothing.
            return 0;
        }
        std::string timeStr = md->toString();
        if (timeStr == "" || timeStr[0] == ' ') {
            std::cerr << path << ": Timestamp of metadatum with key `" 
                      << key << "' not set\n";
            return 1;
        }
        time_t time = str2Time(timeStr);
        if (time == (time_t)-1) {
            std::cerr << path << ": Failed to parse or convert timestamp `" 
                      << timeStr << "'\n";
            return 1;
        }
        if (Params::instance().verbose_) {
            std::cout << path << ": Adjusting timestamp by" 
                      << (adjustment_ < 0 ? " " : " +")
                      << adjustment_ << " seconds to ";
        }
        time += adjustment_;
        timeStr = time2Str(time);
        if (Params::instance().verbose_) {
            std::cout << timeStr << "\n";
        }
        md->setValue(timeStr);
        return 0;
    } // Adjust::adjustDateTime

}                                       // namespace Action

// *****************************************************************************
// local definitions
namespace {

    int str2Tm(const std::string& timeStr, struct tm* tm)
    {
        if (timeStr.length() == 0 || timeStr[0] == ' ') return 1;
        if (timeStr.length() < 19) return 2;
        if (   timeStr[4]  != ':' || timeStr[7]  != ':' || timeStr[10] != ' '
            || timeStr[13] != ':' || timeStr[16] != ':') return 3;
        if (0 == tm) return 4;
        ::memset(tm, 0x0, sizeof(struct tm));

        long tmp;
        if (!Util::strtol(timeStr.substr(0,4).c_str(), tmp)) return 5;
        tm->tm_year = tmp - 1900;
        if (!Util::strtol(timeStr.substr(5,2).c_str(), tmp)) return 6;
        tm->tm_mon = tmp - 1;
        if (!Util::strtol(timeStr.substr(8,2).c_str(), tmp)) return 7;
        tm->tm_mday = tmp;
        if (!Util::strtol(timeStr.substr(11,2).c_str(), tmp)) return 8;
        tm->tm_hour = tmp;
        if (!Util::strtol(timeStr.substr(14,2).c_str(), tmp)) return 9;
        tm->tm_min = tmp;
        if (!Util::strtol(timeStr.substr(17,2).c_str(), tmp)) return 10;
        tm->tm_sec = tmp;

        return 0;
    } // str2Tm

    time_t str2Time(const std::string& timeStr)
    {
        struct tm tm;
        if (str2Tm(timeStr, &tm) != 0) return (time_t)-1;
        return ::mktime(&tm);
    }

    std::string time2Str(time_t time)
    {
        struct tm tm;
        ::memset(&tm, 0x0, sizeof(struct tm));

        if (0 == ::localtime_r(&time, &tm)) return "";

        std::ostringstream os;
        os << std::setfill('0') 
           << tm.tm_year + 1900 << ":"
           << std::setw(2) << tm.tm_mon + 1 << ":"
           << std::setw(2) << tm.tm_mday << " "
           << std::setw(2) << tm.tm_hour << ":"
           << std::setw(2) << tm.tm_min << ":"
           << std::setw(2) << tm.tm_sec;

        return os.str();
    } // time2Str

    std::string exifReadError(int rc, const std::string& path)
    {
        std::string error;
        switch (rc) {
        case -1:
            error = "Couldn't open file `" + path + "'";
            break;
        case 1:
            error = "Couldn't read from the input stream";
            break;
        case 2:
            error = "This does not look like a JPEG image";
            break;
        case 3:
            error = "No Exif data found in the file";
            break;
        case -99:
            error = "Unsupported Exif or GPS data found in IFD 1";
            break;
        default:
            error = "Reading Exif data failed, rc = " + Exif::toString(rc);
            break;
        }
        return error;
    } // exifReadError

    std::string exifWriteError(int rc, const std::string& path)
    {
        std::string error;
        switch (rc) {
        case -1:
            error = "Couldn't open file `" + path + "'";
            break;
        case -2:
            error = "Couldn't open temporary file";
            break;
        case -3:
            error = "Renaming temporary file failed";
            break;
        case 1:
            error = "Couldn't read from the input stream";
            break;
        case 2:
            error = "This does not look like a JPEG image";
            break;
        case 3:
            error = "No JFIF APP0 or Exif APP1 segment found in the file";
            break;
        case 4:
            error = "Writing to the output stream failed";
            break;
        default:
            error = "Reading Exif data failed, rc = " + Exif::toString(rc);
            break;
        }
        return error;
    } // exifWriteError

}

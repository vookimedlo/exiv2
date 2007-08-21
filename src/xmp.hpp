// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004-2007 Andreas Huggel <ahuggel@gmx.net>
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
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301 USA.
 */
/*!
  @file    xmp.hpp
  @brief   Encoding and decoding of XMP data
  @version $Rev$
  @author  Andreas Huggel (ahu)
           <a href="mailto:ahuggel@gmx.net">ahuggel@gmx.net</a>
  @date    13-Jul-07, ahu: created
 */
#ifndef XMP_HPP_
#define XMP_HPP_

// *****************************************************************************
// included header files
#include "metadatum.hpp"
#include "types.hpp"
#include "value.hpp"
#include "properties.hpp"

// + standard includes
#include <string>
#include <vector>

// *****************************************************************************
// namespace extensions
namespace Exiv2 {

// *****************************************************************************
// class definitions

    /*!
      @brief Information related to an XMP property. An XMP metadatum consists
             of an XmpKey and a Value and provides methods to manipulate these.
     */
    class Xmpdatum : public Metadatum {
    public:
        //! @name Creators
        //@{
        /*!
          @brief Constructor for new tags created by an application. The
                 %Xmpdatum is created from a key / value pair. %Xmpdatum
                 copies (clones) the value if one is provided. Alternatively, a
                 program can create an 'empty' %Xmpdatum with only a key and
                 set the value using setValue().

          @param key The key of the %Xmpdatum.
          @param pValue Pointer to a %Xmpdatum value.
          @throw Error if the key cannot be parsed and converted
                 to a known schema namespace prefix and property name.
         */
        explicit Xmpdatum(const XmpKey& key,
                          const Value* pValue =0);
        //! Copy constructor
        Xmpdatum(const Xmpdatum& rhs);
        //! Destructor
        virtual ~Xmpdatum();
        //@}

        //! @name Manipulators
        //@{
        //! Assignment operator
        Xmpdatum& operator=(const Xmpdatum& rhs);
        /*!
          @brief Assign \em value to the %Xmpdatum. The type of the new Value
                 is set to UShortValue.
         */
        Xmpdatum& operator=(const uint16_t& value);
        /*!
          @brief Assign \em value to the %Xmpdatum.
                 Calls setValue(const std::string&).
         */
        Xmpdatum& operator=(const std::string& value);
        /*!
          @brief Assign \em value to the %Xmpdatum.
                 Calls setValue(const Value*).
         */
        Xmpdatum& operator=(const Value& value);
        void setValue(const Value* pValue);
        void setValue(const std::string& value);
        //@}

        //! @name Accessors
        //@{
        //! Not implemented. Calling this method will raise an exception.
        long copy(byte* buf, ByteOrder byteOrder) const;
        /*!
          @brief Return the key of the Xmpdatum. The key is of the form
                 '<b>Xmp</b>.prefix.property'. Note however that the
                 key is not necessarily unique, i.e., an XmpData may contain
                 multiple metadata with the same key.
         */
        std::string key() const;
        //! Return the (preferred) schema namespace prefix.
        std::string groupName() const;
        //! Return the property name.
        std::string tagName() const;
        std::string tagLabel() const;
        //! Properties don't have a tag number. Return 0.
        uint16_t tag() const;
        TypeId typeId() const;
        const char* typeName() const;
        // Todo: Remove this method from the baseclass
        //! The Exif typeSize doesn't make sense here. Return 0.
        long typeSize() const { return 0; }
        long count() const;
        long size() const;
        std::string toString() const;
        long toLong(long n =0) const;
        float toFloat(long n =0) const;
        Rational toRational(long n =0) const;
        Value::AutoPtr getValue() const;
        const Value& value() const;
        //@}

    private:
        // Pimpl idiom
        struct Impl;
        Impl* p_;

    }; // class Xmpdatum

    /*!
      @brief Output operator for Xmpdatum types, printing the interpreted
             tag value.
     */
    std::ostream& operator<<(std::ostream& os, const Xmpdatum& md);

    //! Container type to hold all metadata
    typedef std::vector<Xmpdatum> XmpMetadata;

    /*!
      @brief A container for XMP data. This is a top-level class of
             the %Exiv2 library.

      Provide high-level access to the XMP data of an image:
      - read XMP information from an XML block
      - access metadata through keys and standard C++ iterators
      - add, modify and delete metadata
      - serialize XMP data to an XML block
    */
    class XmpData {
    public:
        //! XmpMetadata iterator type
        typedef XmpMetadata::iterator iterator;
        //! XmpMetadata const iterator type
        typedef XmpMetadata::const_iterator const_iterator;

        //! @name Manipulators
        //@{
        /*!
          @brief Returns a reference to the %Xmpdatum that is associated with a
                 particular \em key. If %XmpData does not already contain such
                 an %Xmpdatum, operator[] adds object \em Xmpdatum(key).

          @note  Since operator[] might insert a new element, it can't be a const
                 member function.
         */
        Xmpdatum& operator[](const std::string& key);
        /*!
          @brief Add an %Xmpdatum from the supplied key and value pair. This
                 method copies (clones) the value.
          @return 0 if successful.
         */
        int add(const XmpKey& key, Value* value);
        /*!
          @brief Add a copy of the Xmpdatum to the XMP metadata.
          @return 0 if successful.
         */
        int add(const Xmpdatum& xmpdatum);
        /*!
          @brief Delete the Xmpdatum at iterator position pos, return the
                 position of the next Xmpdatum.

          @note  Iterators into the metadata, including pos, are potentially
                 invalidated by this call.
         */
        iterator erase(iterator pos);
        //! Delete all Xmpdatum instances resulting in an empty container.
        void clear();
        //! Sort metadata by key
        void sortByKey();
        //! Begin of the metadata
        iterator begin();
        //! End of the metadata
        iterator end();
        /*!
          @brief Find the first Xmpdatum with the given key, return an iterator
                 to it.
         */
        iterator findKey(const XmpKey& key);
        //@}

        //! @name Accessors
        //@{
        //! Begin of the metadata
        const_iterator begin() const;
        //! End of the metadata
        const_iterator end() const;
        /*!
          @brief Find the first Xmpdatum with the given key, return a const
                 iterator to it.
         */
        const_iterator findKey(const XmpKey& key) const;
        //! Return true if there is no XMP metadata
        bool empty() const;
        //! Get the number of metadata entries
        long count() const;
        //@}

    private:
        // DATA
        XmpMetadata xmpMetadata_;
    }; // class XmpData

    /*!
      @brief Stateless parser class for XMP packets. Images use this
             class to parse and serialize XMP packets. The parser uses
             the XMP toolkit to do the job.
     */
    class XmpParser {
    public:
        /*!
          @brief Decode XMP metadata from an XMP packet \em xmpPacket into
                 \em xmpData. The format of the XMP packet must follow the
                 XMP specification.

          @param xmpData   Container for the decoded XMP properties
          @param xmpPacket The raw XMP packet to decode
          @return 0 if successful;<BR>
                  1 if XMP support has not been compiled-in;<BR>
                  2 if the XMP toolkit failed to initialize<BR>
        */
        static int decode(      XmpData&     xmpData,
                          const std::string& xmpPacket);
        /*!
          @brief Encode (serialize) XMP metadata from \em xmpData into a
                 string xmpPacket. The XMP packet returned in the string
                 follows the XMP specification.
        */
        static void encode(      std::string& xmpPacket,
                           const XmpData&     xmpData);
    private:
        static bool initialized_; //! Indicates if the XMP Toolkit has been initialized

    }; // class XmpParser

}                                       // namespace Exiv2

#endif                                  // #ifndef XMP_HPP_

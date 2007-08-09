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
  @file    properties.hpp
  @brief   XMP property and type information.<BR>References:<BR>
  <a href="http://www.adobe.com/devnet/xmp/pdfs/xmp_specification.pdf">XMP Specification</a> from Adobe
  <I>(Property descriptions copied from the XMP specification with the permission of Adobe)</I>
  @version $Rev$
  @author  Andreas Huggel (ahu)
           <a href="mailto:ahuggel@gmx.net">ahuggel@gmx.net</a>
  @date    13-Jul-07, ahu: created
 */
#ifndef PROPERTIES_HPP_
#define PROPERTIES_HPP_

// *****************************************************************************
// included header files
#include "types.hpp"
#include "metadatum.hpp"

// + standard includes
#include <string>
#include <iosfwd>
#include <memory>

// *****************************************************************************
// namespace extensions
namespace Exiv2 {

// *****************************************************************************
// class declarations
    class XmpKey;

// *****************************************************************************
// class definitions

    //! Category of an XMP property
    enum XmpCategory { xmpInternal, xmpExternal };

    //! Information about one XMP property.
    struct XmpPropertyInfo {
        //! Comparison operator for name
        bool operator==(const std::string& name) const;

        const char*   name_;            //!< Property name
        const char*   title_;           //!< Property title or label
        const char*   xmpValueType_;    //!< XMP value type (for info only)
        TypeId        typeId_;          //!< Exiv2 default type for the property 
        XmpCategory   xmpCategory_;     //!< Category (internal or external)
        const char*   desc_;            //!< Property description
    };

    //! Structure mapping XMP namespaces and (preferred) prefixes.
    struct XmpNsInfo {
        //! For comparison with prefix
        struct Prefix {
            //! Constructor. 
            Prefix(const std::string& prefix);
            //! The prefix string.
            std::string prefix_;
        };
        //! For comparison with namespace
        struct Ns {
            //! Constructor. 
            Ns(const std::string& ns);
            //! The namespace string
            std::string ns_;
        };
        //! Comparison operator for namespace
        bool operator==(const Ns& ns) const;
        //! Comparison operator for prefix
        bool operator==(const Prefix& prefix) const;

        const char* ns_;                //!< Namespace
        const char* prefix_;            //!< (Preferred) prefix
        const XmpPropertyInfo* xmpPropertyInfo_; //!< List of known properties
        const char* desc_;              //!< Brief description of the namespace
    };

    //! Container for XMP property information. Implemented as a static class.
    class XmpProperties {
        //! Prevent construction: not implemented.
        XmpProperties();
        //! Prevent copy-construction: not implemented.
        XmpProperties(const XmpProperties& rhs);
        //! Prevent assignment: not implemented.
        XmpProperties& operator=(const XmpProperties& rhs);

    public:
        /*!
          @brief Return the title (label) of the property.
          @param key The property key
          @return The title (label) of the property
          @throw Error if the key is invalid.
         */
        static const char* propertyTitle(const XmpKey& key);
        /*!
          @brief Return the description of the property.
          @param key The property key
          @return The description of the property
          @throw Error if the key is invalid.
         */
        static const char* propertyDesc(const XmpKey& key);
        /*!
          @brief Return the type for property \em key
          @param key The property key
          @return The type of the property
          @throw Error if the key is invalid.
         */
        static TypeId propertyType(const XmpKey& key);
        /*!
          @brief Return information for the property for key.
                 Always returns a valid pointer.
          @param key The property key
          @return a pointer to the property information
          @throw Error if the key is invalid.
         */
        static const XmpPropertyInfo* propertyInfo(const XmpKey& key);
        /*!
           @brief Return the namespace name for the schema associated
                  with \em prefix.
           @param prefix Prefix
           @return the namespace name
           @throw Error if no namespace is registered with \em prefix.
         */
        static const char* ns(const std::string& prefix);
        /*!
           @brief Return the namespace description for the schema associated
                  with \em prefix.
           @param prefix Prefix
           @return the namespace description
           @throw Error if no namespace is registered with \em prefix.
         */
        static const char* nsDesc(const std::string& prefix);
        /*!
          @brief Return read-only list of built-in properties for \em prefix.
          @param prefix Prefix
          @return Pointer to the built-in properties for prefix, may be 0 if 
                  none is configured in the namespace info.
          @throw Error if no namespace is registered with \em prefix.
         */
        static const XmpPropertyInfo* propertyList(const std::string& prefix);
        /*!
          @brief Return information about a schema namespace for \em prefix.
                 Always returns a valid pointer.
          @param prefix The prefix
          @return a pointer to the related information
          @throw Error if no namespace is registered with \em prefix.
         */
        static const XmpNsInfo* nsInfo(const std::string& prefix);
        /*!
           @brief Return the (preferred) prefix for schema namespace \em ns
           @param ns Schema namespace
           @return the prefix or 0 if namespace \em ns is not registered.
         */
        static const char* prefix(const std::string& ns);
        //! Print a list of properties of a schema namespace to output stream \em os.
        static void printProperties(std::ostream& os, const std::string& prefix);

    }; // class XmpProperties

    /*!
      @brief Concrete keys for XMP metadata.
     */
    class XmpKey : public Key {
    public:
        //! Shortcut for an %XmpKey auto pointer.
        typedef std::auto_ptr<XmpKey> AutoPtr;

        //! @name Creators
        //@{
        /*!
          @brief Constructor to create an XMP key from a key string.

          @param key The key string.
          @throw Error if the first part of the key is not '<b>Xmp</b>' or
                 the remaining parts of the key cannot be parsed and
                 converted to a known schema prefix and property name.
        */
        explicit XmpKey(const std::string& key);
        /*!
          @brief Constructor to create an XMP key from a schema prefix
                 and a property name.

          @param prefix   Schema prefix name
          @param property Property name

          @throw Error if the schema prefix or the property name are not
                 known.
        */
        XmpKey(const std::string& prefix, const std::string& property);
        //! Copy constructor.
        XmpKey(const XmpKey& rhs);
        //! Virtual destructor.
        virtual ~XmpKey();
        //@}

        //! @name Manipulators
        //@{
        //! Assignment operator.
        XmpKey& operator=(const XmpKey& rhs);
        //@}

        //! @name Accessors
        //@{
        virtual std::string key() const;
        virtual const char* familyName() const;
        /*!
          @brief Return the name of the group (the second part of the key).
                 For XMP keys, the group name is the schema prefix name.
        */
        virtual std::string groupName() const;
        virtual std::string tagName() const;
        virtual std::string tagLabel() const;
        //! Properties don't have a tag number. Return 0.
        virtual uint16_t tag() const { return 0; }

        AutoPtr clone() const;

        // Todo: Should this be removed? What about tagLabel then?
        //! Return the schema namespace for the prefix of the key
        const char* ns() const;
        //@}

    private:
        //! Internal virtual copy constructor.
        virtual XmpKey* clone_() const;

    private:
        // Pimpl idiom
        struct Impl;
        Impl* p_;

    }; // class XmpKey

// *****************************************************************************
// free functions

    //! Output operator for property info
    std::ostream& operator<<(std::ostream& os, const XmpPropertyInfo& propertyInfo);

}                                       // namespace Exiv2

#endif                                  // #ifndef PROPERTIES_HPP_

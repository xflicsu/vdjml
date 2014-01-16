/** @file "/vdjml/include/vdjml/germline_db_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_DB_INFO_HPP_
#define GERMLINE_DB_INFO_HPP_
#include <string>
#include "boost/functional/hash.hpp"
#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/config.hpp"
#include "vdjml/object_ids.hpp"

namespace vdjml{
class Germline_db_map;
class Xml_reader;
class Xml_writer;

/**@brief 
*******************************************************************************/
class VDJML_DECL Gl_db_info {
   friend class Germline_db_map;

public:

   Gl_db_info(
            std::string const& name,
            std::string const& version,
            std::string const& species,
            std::string const& url
   )
   : id_(),
     name_(name),
     version_(version),
     species_(species),
     uri_(url)
   {}

   explicit Gl_db_info(
            Xml_reader& xr,
            const unsigned version
   );

   Gl_db_id id() const {return id_;}
   std::string const& name() const {return name_;}
   std::string const& version() const {return version_;}
   std::string const& species() const {return species_;}
   std::string const& uri() const {return uri_;}

   bool operator==(Gl_db_info const& ai) const {
      return
               name() == ai.name() &&
               version() == ai.version() &&
               species() == ai.species()
               ;
   }

   bool operator!= (Gl_db_info const& ai) const {return !(*this == ai);}

private:
   Gl_db_id id_;
   std::string name_;
   std::string version_;
   std::string species_;
   std::string uri_;
};

/**@brief
*******************************************************************************/
inline std::size_t hash_value(Gl_db_info const& gdi) {
   std::size_t h = 0;
   boost::hash_combine(h, gdi.name());
   boost::hash_combine(h, gdi.version());
   boost::hash_combine(h, gdi.species());
   return h;
}

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Gl_db_info const& gdi,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* GERMLINE_DB_INFO_HPP_ */

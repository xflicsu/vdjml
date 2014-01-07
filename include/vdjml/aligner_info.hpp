/** @file "/vdjml/include/vdjml/aligner_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ALIGNER_INFO_HPP_
#define ALIGNER_INFO_HPP_
#include <string>
#include "boost/functional/hash.hpp"
#include "vdjml/config.hpp"
#include "vdjml/aligner_id.hpp"
#include "vdjml/format_version.hpp"

namespace vdjml{
class Aligner_map;
class Xml_reader;
class Xml_writer;

/**@brief 
*******************************************************************************/
class VDJML_DECL Aligner_info {
   friend class Aligner_map;

public:

   Aligner_info(
            std::string const& name,
            std::string const& version,
            std::string const& parameters,
            const unsigned run_id
   )
   : id_(),
     name_(name),
     version_(version),
     parameters_(parameters),
     run_id_(run_id)
   {}

   explicit Aligner_info(
            Xml_reader& xr,
            const unsigned version
   );

   Aligner_id id() const {return id_;}
   std::string const& name() const {return name_;}
   std::string const& version() const {return version_;}
   std::string const& parameters() const {return parameters_;}
   unsigned run_id() const {return run_id_;}

   bool operator==(Aligner_info const& ai) const {
      return
               name() == ai.name() &&
               version() == ai.version() &&
               parameters() == ai.parameters()
               ;
   }

   bool operator!= (Aligner_info const& ai) const {return !(*this == ai);}

private:
   Aligner_id id_;
   std::string name_;
   std::string version_;
   std::string parameters_;
   unsigned run_id_;
};

/**@brief
*******************************************************************************/
inline std::size_t hash_value(Aligner_info const& ai) {
   std::size_t h = 0;
   boost::hash_combine(h, ai.name());
   boost::hash_combine(h, ai.version());
   boost::hash_combine(h, ai.parameters());
   return h;
}

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Aligner_info const& ai,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* ALIGNER_INFO_HPP_ */

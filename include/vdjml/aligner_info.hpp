/** @file "/vdjml/include/vdjml/aligner_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ALIGNER_INFO_HPP_
#define ALIGNER_INFO_HPP_
#include <string>
#include "vdjml/detail/object_id_base.hpp"
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"

namespace vdjml{
class Aligner_map;
class Xml_reader;
class Xml_writer;

/**@brief
*******************************************************************************/
class Aligner_id : public detail::Base_id<Aligner_id> {
public:
   explicit Aligner_id(const value_type x) : base(x) {}
   Aligner_id() : base(0) {}
};

/**@brief 
*******************************************************************************/
class Aligner_info {
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

   Aligner_id id() const {return id_;}
   std::string const& name() const {return name_;}
   std::string const& version() const {return version_;}
   std::string const& parameters() const {return parameters_;}
   unsigned run_id() const {return run_id_;}

private:
   Aligner_id id_;
   std::string name_;
   std::string version_;
   std::string parameters_;
   unsigned run_id_;
};

/**@brief
*******************************************************************************/
VDJML_DECL Aligner_info read(
         Xml_reader& xr,
         const unsigned version
);

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Aligner_info const& ai,
         const unsigned version = 0
);

}//namespace vdjml
#endif /* ALIGNER_INFO_HPP_ */

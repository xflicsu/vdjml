/** @file "/vdjml/include/vdjml/germline_db_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_DB_INFO_HPP_
#define GERMLINE_DB_INFO_HPP_
#include <string>
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{
class Germline_db_map;

/**@brief
*******************************************************************************/
class Gdb_id : public detail::Base_id<Gdb_id> {
public:
   explicit Gdb_id(const value_type x) : base(x) {}
   Gdb_id() : base(0) {}
};

/**@brief 
*******************************************************************************/
class Germline_db_info {
   friend class Germline_db_map;

public:

   Germline_db_info(
            std::string const& name,
            std::string const& version,
            std::string const& num_system,
            std::string const& species,
            std::string const& url
   )
   : id_(),
     name_(name),
     version_(version),
     num_system_(num_system),
     species_(species),
     url_(url)
   {}

   Gdb_id id() const {return id_;}
   std::string const& name() const {return name_;}
   std::string const& version() const {return version_;}
   std::string const& num_system() const {return num_system_;}
   std::string const& species() const {return species_;}
   std::string const& url() const {return url_;}

private:
   Gdb_id id_;
   std::string name_;
   std::string version_;
   std::string num_system_;
   std::string species_;
   std::string url_;
};

}//namespace vdjml
#endif /* GERMLINE_DB_INFO_HPP_ */

/** @file "/vdjml/lib/result_builder.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/result_builder.hpp"

#include "vdjml/read_result.hpp"
#include "vdjml/results_meta.hpp"

namespace vdjml{ namespace detail {

/*
*******************************************************************************/
Gl_db_id Result_factory_impl::set_default_gl_database(
         std::string const& name,
         std::string const& version,
         std::string const& species,
         std::string const& url
) {
   def_gldb_ =
            rm_.germline_db_map().insert(
                     Gl_db_info(name, version, species, url)
            );
   return def_gldb_;
}

Aligner_id Result_factory_impl::set_default_aligner(
         std::string const& name,
         std::string const& version,
         std::string const& parameters,
         const unsigned run_id
) {
   def_aligner_ =
            rm_.aligner_map().insert(
                     Aligner_info(name, version, parameters, run_id)
            );
   return def_aligner_;
}

Numsys_id Result_factory_impl::set_default_num_system(std::string const& name) {
   def_numsys_ = rm_.num_system_map().insert(name);
   return def_numsys_;
}


}//namespace detail

/*
*******************************************************************************/
Result_builder::Result_builder(
         detail::Result_factory_impl& rf,
         std::string const& id
)
: detail::Result_factory_impl(rf), r_(new Read_result(id))
{}

/*
*******************************************************************************/
Result_builder::Result_builder(Results_meta& rm, std::string const& id)
: detail::Result_factory_impl(rm), r_(new Read_result(id))
{}


}//namespace vdjml

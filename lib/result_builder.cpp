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

namespace vdjml {

/*
*******************************************************************************/
Result_builder::Result_builder(Results_meta& rm, std::string const& id)
: meta_(rm), r_(new Read_result(id))
{}


}//namespace vdjml

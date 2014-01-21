/** @file "/vdjml/lib/gene_region_type.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/gene_region_type.hpp"

namespace vdjml {

/*
*******************************************************************************/
const Region_id Gene_region_type::fr1 = Region_id(1);
const Region_id Gene_region_type::fr2 = Region_id(2);
const Region_id Gene_region_type::fr3 = Region_id(3);
const Region_id Gene_region_type::cdr1 = Region_id(4);
const Region_id Gene_region_type::cdr2 = Region_id(5);
const Region_id Gene_region_type::cdr3 = Region_id(6);
const Region_id Gene_region_type::vd_junction = Region_id(7);
const Region_id Gene_region_type::dj_junction = Region_id(8);

}//namespace vdjml

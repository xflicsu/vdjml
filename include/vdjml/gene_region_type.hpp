/** @file "/vdjml/include/vdjml/gene_region_type.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GENE_REGION_TYPE_HPP_
#define GENE_REGION_TYPE_HPP_
#include "vdjml/object_ids.hpp"
#include "vdjml/config.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
struct VDJML_DECL Gene_region_type {
   static const Region_id fr1;
   static const Region_id fr2;
   static const Region_id fr3;
   static const Region_id cdr1;
   static const Region_id cdr2;
   static const Region_id cdr3;
   static const Region_id vd_junction;
   static const Region_id dj_junction;
};

}//namespace vdjml
#endif /* GENE_REGION_TYPE_HPP_ */

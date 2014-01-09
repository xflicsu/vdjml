/** @file "/vdjml/include/vdjml/object_ids.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef OBJECT_IDS_HPP_
#define OBJECT_IDS_HPP_
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{

/** Aligner software ID */
VDJML_OBJECT_ID(Aligner_id);

/** Germline database ID */
VDJML_OBJECT_ID(Gl_db_id);

/** Numbering system ID */
VDJML_OBJECT_ID(Numsys_id);

/** Segment match ID */
VDJML_OBJECT_ID(Seg_match_id);

/** Germline segment ID */
VDJML_OBJECT_ID(Gl_seg_id);

/** Gene region type ID */
VDJML_OBJECT_ID(Region_id);

}//namespace vdjml
#endif /* OBJECT_IDS_HPP_ */

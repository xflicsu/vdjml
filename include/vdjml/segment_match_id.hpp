/** @file "/vdjml/include/vdjml/segment_match_id.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_ID_HPP_
#define SEGMENT_MATCH_ID_HPP_
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{

/**@brief
*******************************************************************************/
class Sm_id : public detail::Base_id<Sm_id> {
public:
   explicit Sm_id(const value_type x) : base(x) {}
   Sm_id() : base(0) {}
};

}//namespace vdjml
#endif /* SEGMENT_MATCH_ID_HPP_ */

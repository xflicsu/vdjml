/** @file "/vdjml/include/vdjml/germline_segment_id.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_SEGMENT_ID_HPP_
#define GERMLINE_SEGMENT_ID_HPP_

namespace vdjml{

/**@brief
*******************************************************************************/
class Gls_id : public detail::Base_id<Gls_id> {
public:
   explicit Gls_id(const value_type x) : base(x) {}
   Gls_id() : base(0) {}
};

}//namespace vdjml
#endif /* GERMLINE_SEGMENT_ID_HPP_ */

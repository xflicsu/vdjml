/** @file "/vdjml/include/vdjml/aligner_id.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ALIGNER_ID_HPP_
#define ALIGNER_ID_HPP_
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{

/**@brief
*******************************************************************************/
class Aligner_id : public detail::Base_id<Aligner_id> {
public:
   explicit Aligner_id(const value_type x) : base(x) {}
   Aligner_id() : base(0) {}
};


}//namespace vdjml
#endif /* ALIGNER_ID_HPP_ */

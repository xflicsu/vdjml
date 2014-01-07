/** @file "/vdjml/include/vdjml/num_system.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef NUM_SYSTEM_HPP_
#define NUM_SYSTEM_HPP_
#include <string>
#include <iosfwd>
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{
class Num_system_map;

/**@brief
*******************************************************************************/
class Numsys_id : public detail::Base_id<Numsys_id> {
public:
   explicit Numsys_id(const value_type x) : base(x) {}
   Numsys_id() : base(0) {}
};

/**@brief 
*******************************************************************************/
struct Num_system {
   Numsys_id id_;
   std::string name_;
};

/**
*******************************************************************************/
template<class ChT, class Tr> inline
std::basic_ostream<ChT,Tr>& operator<<(
      std::basic_ostream<ChT,Tr>& os,
      Num_system const& ns
) {
   return os << ns.name_;
}

}//namespace vdjml
#endif /* NUM_SYSTEM_HPP_ */

/** @file "/vdjml/include/vdjml/percent.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef PERCENT_HPP_
#define PERCENT_HPP_
#include <iosfwd>
#include <iomanip>

namespace vdjml{

/**@brief 
*******************************************************************************/
struct Percent {
   Percent(const float f = 0.0) : f_(f) {}
   float f_;
};


/**
*******************************************************************************/
template<class ChT, class Tr> inline
std::basic_ostream<ChT,Tr>& operator<<(
      std::basic_ostream<ChT,Tr>& os,
      const Percent p
) {
   return os << std::setprecision(4) << p.f_ << '%';
}

}//namespace vdjml
#endif /* PERCENT_HPP_ */

/** @file "/vdjml/include/vdjml/percent.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef PERCENT_HPP_
#define PERCENT_HPP_
#include <iosfwd>
#include <iomanip>
#include <cmath>
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Percent {
   static const float err() {return 0.001;}

public:
   Percent(const float f = 0.0) : f_(f) {}

   bool operator==(const Percent p) const {
      return std::abs(f_ - p.f_) <= err();
   }

   bool operator<(const Percent p) const {
      return err() < (p.f_ - f_);
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Percent)

   float percent() const {return f_;}
   float fraction() const {return f_ * 0.01;}

   template<class ChT, class Tr> friend
   std::basic_ostream<ChT,Tr>& operator<<(
            std::basic_ostream<ChT,Tr>& os,
            const Percent p
   ) {
      return os << std::setprecision(4) << p.f_ << '%';
   }

private:
   float f_;
};


/**
*******************************************************************************/

}//namespace vdjml
#endif /* PERCENT_HPP_ */

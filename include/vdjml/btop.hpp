/** @file "/vdjml/include/vdjml/btop.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef BTOP_HPP_
#define BTOP_HPP_
#include <string>
#include <iosfwd>
#include "boost/algorithm/string/case_conv.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{

/**@brief Store BTOP (Blast traceback operations)
*******************************************************************************/
class Btop {
public:
   explicit Btop(std::string const& val)
   : val_(val)
   {
      boost::to_upper(val_);
   }

   std::string str() const {return val_;}
   bool empty() const {return val_.empty();}
   bool operator==(Btop const& bt) const {return val_ == bt.val_;}
   bool operator<(Btop const& bt) const {return val_ < bt.val_;}
   VDJML_COMPARISON_OPERATOR_MEMBERS(Btop)

private:
   std::string val_;
};

/**
*******************************************************************************/
template<class ChT, class Tr> inline
std::basic_ostream<ChT,Tr>& operator<<(
      std::basic_ostream<ChT,Tr>& os,
      Btop const& btop
) {
   return os << btop.str();
}

}//namespace vdjml
#endif /* BTOP_HPP_ */

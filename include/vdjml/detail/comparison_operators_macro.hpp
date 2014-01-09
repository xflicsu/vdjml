/** @file "/vdjml/include/vdjml/detail/comparison_operators_macro.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef COMPARISON_OPERATORS_MACRO_HPP_
#define COMPARISON_OPERATORS_MACRO_HPP_

#define VDJML_COMPARISON_OPERATOR_MEMBERS(name) \
   bool operator!=(name const& x) const {       \
      return !( *this == x );                   \
   }                                            \
   bool operator>(name const& x) const {        \
      return x < *this;                         \
   }                                            \
   bool operator<=(name const& x) const {       \
      return !( x < *this );                    \
   }                                            \
   bool operator>=(name const& x) const {       \
      return !( *this < x );                    \
   }                                            \
/* */


#endif /* COMPARISON_OPERATORS_MACRO_HPP_ */

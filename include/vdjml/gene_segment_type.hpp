/** @file "/vdjml/include/vdjml/gene_segment_type.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GENE_SEGMENT_TYPE_HPP_
#define GENE_SEGMENT_TYPE_HPP_
#include "vdjml/exception.hpp"

namespace vdjml{

/**@brief Gene segment types
*******************************************************************************/
enum Gs_type {
   V_gs, D_gs, J_gs
};

/**@brief Gene segment types
*******************************************************************************/
inline Gs_type segment_type(const char c) {
   switch(c) {
   case 'V':
   case 'v':
      return V_gs;
   case 'D':
   case 'd':
      return D_gs;
   case 'J':
   case 'j':
      return J_gs;
   }
   std::string s("invalid segment letter \"");
   s += c;
   s += '"';
   BOOST_THROW_EXCEPTION(
            base_exception()
            << base_exception::msg_t(s)
   );
}

/**@brief Gene segment types
*******************************************************************************/
inline char segment_type(const Gs_type gst) {
   switch(gst) {
   case V_gs: return 'V';
   case D_gs: return 'D';
   case J_gs: return 'J';
   }
}


}//namespace vdjml
#endif /* GENE_SEGMENT_TYPE_HPP_ */

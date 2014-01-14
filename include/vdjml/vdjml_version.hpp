/** @file "/vdjml/include/vdjml/vdjml_version.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_VERSION_HPP_
#define VDJML_VERSION_HPP_
#include "boost/lexical_cast.hpp"
#include "vdjml/vdjml_current_version.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
inline unsigned version_major(const unsigned version) {
   return version / 1000;
}

/**@brief
*******************************************************************************/
inline unsigned version_minor(const unsigned version) {
   return version % 1000;
}

/**@brief
*******************************************************************************/
inline std::string version_string(const unsigned version) {
   return
            boost::lexical_cast<std::string>(version_major(version)) + '.' +
            boost::lexical_cast<std::string>(version_minor(version))
            ;
}

/**@brief
*******************************************************************************/
inline bool is_supported(const unsigned version) {
   if( VDJML_CURRENT_VERSION < version ) return false;
   return true;
}

}//namespace vdjml
#endif /* VDJML_VERSION_HPP_ */

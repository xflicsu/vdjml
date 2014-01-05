/** @file "/vdjml/include/vdjml/lib_info.hpp"
part of VDJML project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
@details
Main doxygen page and library info API.
*******************************************************************************/
#ifndef VDJMLLIB_INFO_HPP_
#define VDJMLLIB_INFO_HPP_
#include <string>
#include <iosfwd>
#include "vdjml/config.hpp"

/**
@mainpage %VDJML -- serializes and parses results of immune receptor sequence
alignment in VDJML format

@namespace vdjml
@brief Main namespace of %VDJML library

@namespace vdjml::test
@brief Namespace for unit-tests

*/

namespace vdjml{

/**@brief library info
*******************************************************************************/
struct VDJML_DECL Lib_info {
   static std::string const& name();
   static std::string const& version();
   static std::string const& description();
//   static std::string const& copyright();
   static std::string const& license();
   static std::string const& other_libs();
   static int version_1();
   static int version_2();
   static int version_3();
   static std::string const& version_e();
   static int build();

   template<class Ch, class Tr> static std::basic_ostream<Ch,Tr>&
   print(std::basic_ostream<Ch,Tr>& os) {
      os << name() << " - " << description() << ' ';
      return print_version(os);
   }

   template<class Ch, class Tr> static std::basic_ostream<Ch,Tr>&
   print_version(std::basic_ostream<Ch,Tr>& os) {
      os
      << version()
      << ", " << other_libs()
      << ", build:" << build()
      ;
      return os;
   }
};

}//namespace vdjml
#endif /* VDJMLLIB_INFO_HPP_ */

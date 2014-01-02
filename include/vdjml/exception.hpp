/** @file "/vdjml/include/vdjml/exception.hpp"
part of VDJML project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include "boost/exception/all.hpp"

namespace vdjml{

/**
Example:
   BOOST_THROW_EXCEPTION(
         base_exception()
         << base_exception::msg_t("exception occurred")
         << base_exception::nested_t(boost::current_exception())
   );
*******************************************************************************/
struct base_exception : virtual public std::exception, virtual public boost::exception {
   typedef boost::error_info<struct errinfo_message_, std::string> msg_t;
   typedef boost::error_info<struct errinfo_str1_, std::string> str1_t;
   typedef boost::error_info<struct errinfo_str2_, std::string> str2_t;
   typedef boost::error_info<struct errinfo_str3_, std::string> str3_t;
   typedef boost::error_info<struct errinfo_int1_, int> int1_t;
   typedef boost::error_info<struct errinfo_int2_, int> int2_t;
   typedef boost::errinfo_nested_exception nested_t;
};

}//namespace vdjml
#endif /* EXCEPTION_HPP_ */

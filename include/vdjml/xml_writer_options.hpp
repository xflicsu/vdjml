/** @file "/vdjml/include/vdjml/xml_writer_options.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef XML_WRITER_OPTIONS_HPP_
#define XML_WRITER_OPTIONS_HPP_
#include <string>

namespace vdjml{

/**@brief 
*******************************************************************************/
struct Xml_writer_options {

   explicit Xml_writer_options(
            std::string const& indent = "   ",
            std::string const& encoding = "UTF-8",
            char quote = '"',
            std::string const& xml_version = "1.0",
            const std::size_t buff_size = 1024
   )
   : indent_(indent),
     encoding_(encoding),
     quote_(quote),
     xml_version_(xml_version),
     buff_size_(buff_size)
   {}

   std::string indent_;
   std::string encoding_;
   char quote_;
   std::string xml_version_;
   std::size_t buff_size_;
};

}//namespace vdjml
#endif /* XML_WRITER_OPTIONS_HPP_ */

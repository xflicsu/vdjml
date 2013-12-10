/** @file "/vdjml/include/vdjml/xml_reader.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef XML_READER_HPP_
#define XML_READER_HPP_
#include <iosfwd>
#include "vdjml/config.hpp"

namespace vdjml{
class Result_store;

/**@brief 
*******************************************************************************/
class VDJML_DECL Xml_reader {
public:
   void operator()(std::istream& is, Result_store& rs);

private:

};


}//namespace vdjml
#endif /* XML_READER_HPP_ */

/** @file "/vdjml/include/vdjml/xml_writer.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef XML_WRITER_HPP_
#define XML_WRITER_HPP_
#include <iosfwd>
#include "vdjml/config.hpp"

namespace vdjml{
class Aligner_info;
class Germline_db_info;
class Result_store;

/**@brief 
*******************************************************************************/
class VDJML_DECL Xml_writer {
public:
   explicit Xml_writer(const unsigned version)
   : version_(version)
   {}

	void put(Result_store const& rs);
	void put(Aligner_info const& ai);
	void put(Germline_db_info const& gdi);

private:
	unsigned version_;
};

}//namespace vdjml
#endif /* XML_WRITER_HPP_ */

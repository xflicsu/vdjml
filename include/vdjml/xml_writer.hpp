/** @file "/vdjml/include/vdjml/xml_writer.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef XML_WRITER_HPP_
#define XML_WRITER_HPP_
#include <iostream>
#include "vdjml/config.hpp"
#include "boost/lexical_cast.hpp"

typedef struct _xmlBuffer xmlBuffer;
typedef xmlBuffer *xmlBufferPtr;
typedef struct _xmlTextWriter xmlTextWriter;
typedef xmlTextWriter *xmlTextWriterPtr;

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Xml_writer {
public:
   explicit Xml_writer(
            std::ostream& os,
            const std::size_t buff_size = 1024
   );
	~Xml_writer();
	void open(std::string const& name, const bool is_attr);
	void open(
	         std::string const& name,
	         const bool is_attr,
	         std::string const& ns,
	         std::string const& pref = ""
	);

	void close();

	void value(std::string const& val);

	template<class T> void value(T const& t) {
	   value(boost::lexical_cast<std::string>(t));
	}

private:
	std::ostream& os_;
	xmlBufferPtr buff_;
	xmlTextWriterPtr writer_;

	void flush();
};

}//namespace vdjml
#endif /* XML_WRITER_HPP_ */

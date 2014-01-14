/** @file "/vdjml/include/vdjml/xml_writer.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef XML_WRITER_HPP_
#define XML_WRITER_HPP_
#include <string>
#include <iostream>
#include "boost/lexical_cast.hpp"
#include "boost/noncopyable.hpp"
#include "vdjml/config.hpp"
#include "vdjml/xml_writer_options.hpp"

typedef struct _xmlBuffer xmlBuffer;
typedef xmlBuffer *xmlBufferPtr;
typedef struct _xmlTextWriter xmlTextWriter;
typedef xmlTextWriter *xmlTextWriterPtr;

namespace vdjml{

enum Node_type {ELEM, ATTR};

/**@brief
*******************************************************************************/
class VDJML_DECL Xml_writer : boost::noncopyable {
public:

   explicit Xml_writer(
            std::ostream& os,
            Xml_writer_options const& opts = Xml_writer_options()
   );

	~Xml_writer();

	void open(std::string const& name, const Node_type et);

	void open(
	         std::string const& name,
	         const Node_type et,
	         std::string const& ns,
	         std::string const& pref = ""
	);

	void close();

	void value(std::string const& val);

	void value(char const* val);

	template<class T> void value(T const& t) {
	   value(boost::lexical_cast<std::string>(t));
	}

	template<class T> void node(
	         std::string const& name,
	         const Node_type et,
	         T const& val
	) {
	   open(name, et);
	   value(val);
	   close();
	}

private:
	std::ostream& os_;
	xmlBufferPtr buff_;
	xmlTextWriterPtr writer_;
	Node_type last_node_;

	void flush();
};

}//namespace vdjml
#endif /* XML_WRITER_HPP_ */

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

enum Node_type {ELEM, ATTR};

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


/**@brief
*******************************************************************************/
class VDJML_DECL Xml_writer {
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

private:
	std::ostream& os_;
	xmlBufferPtr buff_;
	xmlTextWriterPtr writer_;
	Node_type last_node_;

	void flush();
};

inline std::string version_to_string(const unsigned version) {
   return
            boost::lexical_cast<std::string>(version / 1000) + '.' +
            boost::lexical_cast<std::string>(version % 1000)
            ;
}

}//namespace vdjml
#endif /* XML_WRITER_HPP_ */

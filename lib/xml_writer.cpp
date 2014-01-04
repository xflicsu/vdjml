/** @file "/vdjml/lib/xml_writer.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/xml_writer.hpp"

#include "libxml/xmlwriter.h"
#include "libxml/xmlIO.h"

#include "vdjml/aligner_info.hpp"

namespace vdjml {

/*
*******************************************************************************/
Xml_writer::Xml_writer(
         std::ostream& os,
         const std::size_t buff_size
)
: os_(os),
  buff_(xmlBufferCreateSize(buff_size)),
  writer_(xmlNewTextWriterMemory(buff_, 0))
{
   xmlTextWriterSetIndent(writer_, 1);
   xmlTextWriterSetIndentString(writer_, (const xmlChar*)"   ");
   xmlTextWriterStartDocument(writer_, "1.0", "UTF-8", "yes");
   xmlTextWriterStartElementNS(writer_,
            (const xmlChar*)0,
            (const xmlChar*)"element1",
            (const xmlChar*)"http://some.uri.com"
   );
   flush();
   xmlTextWriterStartElement(writer_, (const xmlChar*)"element2");
   xmlTextWriterWriteString(writer_, (const xmlChar*)"");
   flush();
   os_ << "blah";
   xmlTextWriterStartElement(writer_, (const xmlChar*)"element3");
   xmlTextWriterStartAttribute(writer_, (const xmlChar*)"attr");
   xmlTextWriterWriteString(writer_, (const xmlChar*)"blah");
//   xmlTextWriterEndAttribute(writer_);
   xmlTextWriterEndElement(writer_);
   xmlTextWriterEndElement(writer_);
   xmlTextWriterEndElement(writer_);
   flush();
}

/*
*******************************************************************************/
void Xml_writer::flush() {
   xmlTextWriterFlush(writer_);
   os_ << ( xmlBufferContent(buff_));
   xmlBufferEmpty(buff_);
}

/*
*******************************************************************************/
Xml_writer::~Xml_writer() {
   flush();
   xmlFreeTextWriter(writer_);
   xmlBufferFree(buff_);
}

}//namespace vdjml

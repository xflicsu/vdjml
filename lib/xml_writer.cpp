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
         Xml_writer_options const& opts
)
: os_(os),
  buff_(xmlBufferCreateSize(opts.buff_size_)),
  writer_(xmlNewTextWriterMemory(buff_, 0)),
  last_node_(ELEM)
{
   if( opts.indent_.size() ) {
      xmlTextWriterSetIndent(writer_, 1);
      xmlTextWriterSetIndentString(writer_, (const xmlChar*)opts.indent_.c_str());
   }

   xmlTextWriterStartDocument(
            writer_,
            opts.xml_version_.c_str(),
            opts.encoding_.c_str(),
            0
   );
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
   xmlTextWriterEndDocument(writer_);
   flush();
   xmlFreeTextWriter(writer_);
   xmlBufferFree(buff_);
}

/*
*******************************************************************************/
void Xml_writer::open(std::string const& name, const Node_type et) {
   if( et == ELEM ) {
      xmlTextWriterStartElement(writer_, (const xmlChar*)name.c_str());
   } else if( et == ATTR ){
      xmlTextWriterStartAttribute(writer_, (const xmlChar*)name.c_str());
   }
   last_node_ = et;
}

/*
*******************************************************************************/
void Xml_writer::open(
         std::string const& name,
         const Node_type et,
         std::string const& ns_uri,
         std::string const& pref
) {
   if( et == ELEM ) {
      xmlTextWriterStartElementNS(
               writer_,
               (const xmlChar*)(pref.empty() ? 0 : pref.c_str()),
               (const xmlChar*)name.c_str(),
               (const xmlChar*)(ns_uri.empty() ? 0 : ns_uri.c_str())
      );
   } else if( et == ATTR ){
      xmlTextWriterStartAttributeNS(
               writer_,
               (const xmlChar*)(pref.empty() ? 0 : pref.c_str()),
               (const xmlChar*)name.c_str(),
               (const xmlChar*)(ns_uri.empty() ? 0 : ns_uri.c_str())
      );
   }
   last_node_ = et;
}

/*
*******************************************************************************/
void Xml_writer::close() {
   if( last_node_ == ELEM ) {
      xmlTextWriterEndElement(writer_);
   } else if( last_node_ == ATTR ) {
      xmlTextWriterEndAttribute(writer_);
      last_node_ = ELEM;
   }
}

/*
*******************************************************************************/
void Xml_writer::value(std::string const& val) {
   xmlTextWriterWriteString(writer_, (const xmlChar*)val.c_str());
}

/*
*******************************************************************************/
void Xml_writer::value(char const* val) {
   xmlTextWriterWriteString(writer_, (const xmlChar*)val);
}

}//namespace vdjml

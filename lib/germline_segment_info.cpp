/** @file "/vdjml/lib/germline_segment_info.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/germline_segment_info.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/results_meta.hpp"

namespace vdjml {

/**
*******************************************************************************/
void write(
         Xml_writer& xw,
         Gl_segment_info const& gsi,
         Results_meta const& rm,
         const unsigned version
) {
   xw.node("name", ATTR, gsi.name_);
   xw.node("germline_db", ATTR, gsi.db_);
   xw.node("type", ATTR, segment_type(gsi.gst_));
}

}//namespace vdjml

/** @file "/vdjml/lib/segment_match.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/segment_match.hpp"

#include "boost/foreach.hpp"

#include "vdjml/xml_writer.hpp"
#include "vdjml/results_meta.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Germline_segment_match const& gsm,
         Results_meta const& rm,
         const unsigned version
) {
   xw.open("germline_segment", ELEM);
   xw.node("num_system", ATTR, rm.num_system_map()[gsm.num_system_]);
   write(xw, rm.germline_segment_map()[gsm.gl_segment_], rm, version);
   xw.node("aligner", ATTR, gsm.aligner_);
   xw.node("pos", ATTR, gsm.range_.first());
   xw.node("len", ATTR, gsm.range_.length());
   write(xw, (Match_metrics const&)gsm, version);
   xw.close(); //germline_segment, ELEM
}

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Segment_match const& sm,
         Results_meta const& rm,
         const unsigned version
) {
   xw.open("read_segment_match", ELEM);
   xw.node("id", ATTR, sm.id());
   xw.node("pos", ATTR, sm.range().first());
   xw.node("len", ATTR, sm.range().length());
   xw.node("btop", ELEM, sm.btop().str());
   BOOST_FOREACH(Germline_segment_match const& gsm, sm.germline_segments()) {
      write(xw, gsm, rm, version);
   }
   xw.close(); //read_segment_match, ELEM
}

}//namespace vdjml

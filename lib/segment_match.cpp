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
#include "vdjml/exception.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Gl_segment_match const& gsm,
         Results_meta const& rm,
         const unsigned version
) {
   xw.open("germline_segment", ELEM);
   xw.node("id", ATTR, gsm.id_);
   xw.node("num_system", ATTR, rm.num_system_map()[gsm.num_system_]);
   write(xw, rm.germline_segment_map()[gsm.gl_segment_], rm, version);
   xw.node("aligner", ATTR, gsm.aligner_);
   write(xw, gsm.range_, version);
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
   write(xw, sm.range(), version);
   xw.node("btop", ELEM, sm.btop().str());
   BOOST_FOREACH(Gl_segment_match const& gsm, sm.germline_segments()) {
      write(xw, gsm, rm, version);
   }
   BOOST_FOREACH(Aa_substitution const& aas, sm.aa_substitutions()) {
      write(xw, aas, version);
   }
   xw.close(); //read_segment_match, ELEM
}

/*
*******************************************************************************/
void merge(Segment_match& sm1, Segment_match const& sm2) {
   if( sm1.btop() != sm2.btop() || sm1.range() != sm2.range() ) {
      BOOST_THROW_EXCEPTION(
               Segment_match::Err()
               << Segment_match::Err::msg_t("same BTOP and range are required")
      );
   }
   BOOST_FOREACH(Gl_segment_match const& gsm, sm2.germline_segments()) {
      sm1.insert(gsm);
   }
}

}//namespace vdjml

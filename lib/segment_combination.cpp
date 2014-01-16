/** @file "/vdjml/lib/segment_combination.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/segment_combination.hpp"

#include "boost/foreach.hpp"

#include "vdjml/xml_writer.hpp"
#include "vdjml/results_meta.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Gene_region const& gr,
         Results_meta const& rm,
         const unsigned version
) {
   xw.open("region", ELEM);
   xw.node("name", ATTR, rm.gene_region_map()[gr.region_]);
   xw.node("num_system", ATTR, rm.num_system_map()[gr.num_system_]);
   write(xw, gr.range_, version);
   write(xw, (Match_metrics const&)gr, version);
   xw.close(); //region, ELEM
}

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Segment_combination const& sc,
         Results_meta const& rm,
         const unsigned version
) {
   xw.open("combination", ELEM);
   xw.open("segments", ATTR);
   if( sc.segments().size() ) {
      xw.value(sc.segments()[0]);
      for(std::size_t n = 1; n != sc.segments().size(); ++n) {
         xw.value(',');
         xw.value(sc.segments()[n]);
      }
   }
   xw.close(); //segments, ATTR

   BOOST_FOREACH(Gene_region const& gr, sc.regions()) {
      write(xw, gr, rm, version);
   }

   xw.close(); //combination, ELEM
}

}//namespace vdjml

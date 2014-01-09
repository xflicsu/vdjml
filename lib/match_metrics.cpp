/** @file "/vdjml/lib/match_metrics.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/match_metrics.hpp"
#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Match_metrics const& mm,
         const unsigned version
) {
   xw.node("score", ATTR, mm.score());
   xw.node("identity", ATTR, mm.identity());
   xw.node("insertions", ATTR, mm.insertions());
   xw.node("deletions", ATTR, mm.deletions());
   xw.node("substitutions", ATTR, mm.substitutions());

   if( mm.stop_codon() ) {
      xw.node("stop_codon", ATTR, mm.stop_codon());
   }

   if( mm.mutated_invariant() ) {
      xw.node("mutated_invariant", ATTR, mm.mutated_invariant());
   }

   if( mm.is_inverted() ) {
      xw.node("is_inverted", ATTR, mm.is_inverted());
   }

}

}//namespace vdjml

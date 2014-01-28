/** @file "/vdjml/lib/match_metrics.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/match_metrics.hpp"

#include <limits>

#include "vdjml/xml_writer.hpp"

namespace vdjml {

const int Match_metrics::unscore = std::numeric_limits<score_t>::max();

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Match_metrics const& mm,
         const unsigned version
) {
   xw.node("identity", ATTR, mm.identity());
   if( mm.score() != Match_metrics::unscore ) xw.node("score", ATTR, mm.score());
   if( mm.insertions() ) xw.node("insertions", ATTR, mm.insertions());
   if( mm.deletions() ) xw.node("deletions", ATTR, mm.deletions());
   if( mm.substitutions() ) xw.node("substitutions", ATTR, mm.substitutions());
   if( mm.stop_codon() ) xw.node("stop_codon", ATTR, mm.stop_codon());
   if( mm.mutated_invariant() ) xw.node("mutated_invariant", ATTR, mm.mutated_invariant());
   if( mm.is_inverted() ) xw.node("is_inverted", ATTR, mm.is_inverted());

}

}//namespace vdjml

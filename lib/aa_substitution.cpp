/** @file "/vdjml/lib/aa_substitution.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/aa_substitution.hpp"
#include "boost/foreach.hpp"

#include "vdjml/xml_writer.hpp"
#include "vdjml/exception.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Aa_substitution const& aas,
         const unsigned version
) {
   xw.open("aa_substitution", ELEM);
   xw.node("read_pos", ATTR, aas.read_pos_);
   xw.node("from", ATTR, to_capital(aas.from_));
   xw.node("to", ATTR, to_capital(aas.to_));
   BOOST_FOREACH(Gl_position const& gp, aas.gl_pos_) {
      xw.open("germline_position", ELEM);
      xw.node("germline_segment_id", ATTR, gp.gsm_);
      xw.node("germline_pos", ATTR, gp.gl_pos_);
      xw.close(); //"germline_position", ELEM
   }
   xw.close(); //"aa_substitution", ELEM
}

}//namespace vdjml

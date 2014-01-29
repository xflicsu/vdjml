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
   xw.node("read_pos", ATTR, aas.read_pos_0_);
   xw.node("aa_read", ATTR, to_capital(aas.aa_read_));
   xw.node("aa_gl", ATTR, to_capital(aas.aa_gl_));
   BOOST_FOREACH(Gl_position const& gp, aas.gl_pos_) {
      xw.open("germline_position", ELEM);
      xw.node("segment", ATTR, gp.gsm_);
      xw.node("pos", ATTR, gp.gl_pos_);
      xw.close(); //"germline_position", ELEM
   }
   xw.close(); //"aa_substitution", ELEM
}

}//namespace vdjml

/** @file "/vdjml/lib/interval.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/interval.hpp"
#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         interval_short const& range,
         const unsigned version
) {
   xw.node("pos0", ATTR, range.pos_0());
   xw.node("len", ATTR, range.length());
}

}//namespace vdjml

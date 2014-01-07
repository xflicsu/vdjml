/** @file "/vdjml/lib/read_result.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/read_result.hpp"
#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
Read_result::Read_result(
         Xml_reader& xr,
         const unsigned version
)
: id_()
{

}

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Read_result const& rr,
         const unsigned version
) {
   xw.open("read", ELEM);
   xw.node("id", ATTR, rr.id());

   xw.open("alignment", ELEM);

   xw.close(); //alignment ELEM

   xw.close(); //read ELEM
}

}//namespace vdjml

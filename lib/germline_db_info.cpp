/** @file "/vdjml/lib/germline_db_info.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/germline_db_info.hpp"

#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
Germline_db_info::Germline_db_info(
            Xml_reader& xr,
            const unsigned version
)
{

}

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Germline_db_info const& gdi,
         const unsigned version
) {
   xw.open("germline_db", ELEM);

   xw.node("id", ATTR, gdi.id());
   xw.node("name", ATTR, gdi.name());
   xw.node("species", ATTR, gdi.species());
   xw.node("version", ATTR, gdi.version());
   if( gdi.uri().size() ) xw.node("uri", ATTR, gdi.uri());

   xw.close(); //germline_db ELEM
}

}//namespace vdjml

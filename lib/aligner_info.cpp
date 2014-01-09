/** @file "/vdjml/lib/aligner_info.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/aligner_info.hpp"
#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
Aligner_info::Aligner_info(
            Xml_reader& xr,
            const unsigned version
)
{

}

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Aligner_info const& ai,
         const unsigned version
) {
   xw.open("aligner", ELEM);

   xw.node("id", ATTR, ai.id());
   xw.node("name", ATTR, ai.name());
   xw.node("version", ATTR, ai.version());
   xw.node("run_id", ATTR, ai.run_id());
   if( ai.parameters().size() ) xw.node("parameters", ELEM, ai.parameters());

   xw.close(); //aligner ELEM
}

}//namespace vdjml

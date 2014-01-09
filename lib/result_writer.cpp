/** @file "/vdjml/lib/result_writer.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/result_writer.hpp"


#include "vdjml/xml_writer.hpp"

namespace vdjml {

/*
*******************************************************************************/
Result_writer::Result_writer(
         std::ostream& os,
         Result_store const& rs,
         const unsigned version,
         Xml_writer_options const& opts
)
: xw_(os, opts)
{

}


/*
*******************************************************************************/
void Result_writer::write(Read_result const& rr) {

}

/*
*******************************************************************************/
void Result_writer::close() {

}


}//namespace vdjml

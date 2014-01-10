/** @file "/vdjml/lib/results_meta.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/results_meta.hpp"

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/foreach.hpp"

#include "vdjml/xml_writer.hpp"
#include "vdjml/lib_info.hpp"

namespace vdjml {

/*
*******************************************************************************/
Results_meta::Results_meta(
         Xml_reader& xr,
         const unsigned version
)
{
   //todo:
}

/*
*******************************************************************************/

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Results_meta const& rs,
         const unsigned version
) {
   xw.open("meta", ELEM);

   xw.open("generator", ELEM);
   xw.node("name", ATTR, Lib_info::name());
   xw.node("version", ATTR, Lib_info::version());
   xw.node("time_gmt", ATTR, boost::posix_time::second_clock::universal_time());
   xw.close(); //generator ELEM

   BOOST_FOREACH(Aligner_info const& ai, rs.aligner_map()) {
      write(xw, ai, version);
   }

   BOOST_FOREACH(Gl_db_info const& gdi, rs.germline_db_map()) {
      write(xw, gdi, version);
   }

   xw.close(); //meta ELEM
}

}//namespace vdjml

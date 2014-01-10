/** @file "/vdjml/lib/result_store.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/result_store.hpp"

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/foreach.hpp"

#include "vdjml/read_result.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/lib_info.hpp"
#include "vdjml/aligner_info.hpp"
#include "vdjml/germline_db_info.hpp"

namespace vdjml {

Result_store::Result_store(
            Xml_reader& xr,
            const unsigned version
)
: rm_(new Results_meta())
{
   //todo:
}

namespace {

/*
*******************************************************************************/
void write_0(
         Xml_writer& xw,
         Result_store const& rs,
         const unsigned version
) {
   write(xw, rs.meta(), version);
   xw.open("read_results", ELEM);
   BOOST_FOREACH(Read_result const& rr, rs) {
      write(xw, rr, rs.meta(), version);
   }
   xw.close(); //read_results ELEM
}

}//anonymous namespace

/*
*******************************************************************************/
void write(
         Xml_writer& xw,
         Result_store const& rs,
         const unsigned version
) {
   xw.open("vdjml_results", ELEM, "http://vdjserver.org/xml/schema/vdjml/");
   xw.node("version", ATTR, version_to_string(version));

   switch (version) {
      case 0:
         write_0(xw, rs, version);
         break;
      default:
         BOOST_THROW_EXCEPTION(
                  base_exception()
                  << base_exception::msg_t("unsupported format version")
                  << base_exception::int1_t(version)
         );
   }

   xw.close();
}


}//namespace vdjml

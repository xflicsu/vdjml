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
#include "vdjml/read_result_writer.hpp"
#include "vdjml/lib_info.hpp"
#include "vdjml/aligner_info.hpp"
#include "vdjml/germline_db_info.hpp"
#include "vdjml/vdjml_version.hpp"

namespace vdjml {

Result_store::Result_store(
            Xml_reader& xr,
            const unsigned version
)
: rm_(new Results_meta())
{
   //todo:
}

/*
*******************************************************************************/
void write_to_file(
         std::string const& path,
         Result_store const& rs,
         const Compression compr,
         const unsigned version,
         Xml_writer_options const& xwo
) {
   Read_result_writer rrw(path, rs.meta(), compr, version, xwo);
   BOOST_FOREACH(Read_result const& rr, rs) {
      rrw(rr);
   }
}

/*
*******************************************************************************/
void write(
         std::ostream& os,
         Result_store const& rs,
         const Compression compr,
         const unsigned version,
         Xml_writer_options const& xwo
) {
   Read_result_writer rrw(os, rs.meta(), compr, version, xwo);
   BOOST_FOREACH(Read_result const& rr, rs) {
      rrw(rr);
   }
}


}//namespace vdjml

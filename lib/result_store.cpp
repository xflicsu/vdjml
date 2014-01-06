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

/*
*******************************************************************************/
std::size_t Result_store::size() const {
   //todo:
   return 0;
}

/*
*******************************************************************************/
Result_store::const_iterator Result_store::begin() const {
   //todo:
   return 0;
}

/*
*******************************************************************************/
Result_store::const_iterator Result_store::end() const {
   //todo:
   return 0;
}

/*
*******************************************************************************/
Read_result const* Result_store::find_id(std::string const* id) const {
   //todo:
   return 0;
}

/*
*******************************************************************************/
void Result_store::insert(Read_result const& rr) {
   //todo:
}

/*
*******************************************************************************/
Result_store read(
         Xml_reader& xr,
         const unsigned version
) {

}

namespace {

/*
*******************************************************************************/
void write_0(
         Xml_writer& xw,
         Result_store const& rs,
         const unsigned version
) {
   xw.open("meta", ELEM);
   xw.open("generator", ELEM);

   xw.open("name", ATTR);
   xw.value(Lib_info::name());
   xw.close();

   xw.open("version", ATTR);
   xw.value(Lib_info::version());
   xw.close();

   xw.open("time_gmt", ATTR);
   xw.value(boost::posix_time::second_clock::universal_time());
   xw.close();

   xw.open("aligners", ELEM);
   BOOST_FOREACH(Aligner_info const& ai, rs.aligner_map()) {
      write(xw, ai, version);
   }
   xw.close();

   xw.open("germline_dbs", ELEM);
   BOOST_FOREACH(Germline_db_info const& gdi, rs.germline_db_map()) {
      write(xw, gdi, version);
   }
   xw.close();
   xw.close();

   xw.open("read_results", ELEM);
   BOOST_FOREACH(Read_result const& rr, rs) {
      write(xw, rr, version);
   }
   xw.close();

   xw.close();
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
   xw.open("version", ATTR);
   xw.value(version_to_string(version));

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

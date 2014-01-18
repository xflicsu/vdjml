/** @file "/vdjml/binding/python/read_result_writer.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/read_result_writer.hpp"
#include "vdjml/results_meta.hpp"
#include "vdjml/read_result.hpp"
#include "vdjml/compression.hpp"
using vdjml::Results_meta;
using vdjml::Read_result_writer;

void export_result_writer() {

   bp::class_<Read_result_writer, boost::noncopyable >(
            "Result_writer",
            "Incrementally serialize VDJ alignment results",
            bp::init<
               std::string const&,  Results_meta const&,
               vdjml::Compression, const unsigned,
               vdjml::Xml_writer_options const&
            >(
                     (
                              bp::arg("file_name"),
                              bp::arg("meta"),
                              bp::arg("compression") = vdjml::Unknown_compression,
                              bp::arg("version") = VDJML_CURRENT_VERSION,
                              bp::arg("options") = vdjml::Xml_writer_options()
                     )
            )
   )
   .def(
            "__call__",
            &Read_result_writer::operator(),
            (
                     bp::arg("result")
            ),
            "serialize read result"
   )
   ;
}

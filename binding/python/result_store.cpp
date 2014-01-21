/** @file "/vdjml/binding/python/result_store.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/result_store.hpp"
using vdjml::Results_meta;
using vdjml::Result_store;

void export_result_store() {
   bp::class_<Result_store>(
            "Result_store",
            "Storage of sequencing read results",
            bp::init<boost::shared_ptr<Results_meta> >(
               bp::arg("results_meta") = boost::shared_ptr<Results_meta>()
            )
   )
   .def("__len__", &Result_store::size)
   .def("empty", &Result_store::empty)
   .def(
      "__iter__",
      bp::range<bp::return_value_policy<bp::copy_const_reference> >(
               &Result_store::begin, &Result_store::end
      )
   )
   .def(
      "insert",
      static_cast<
         void (Result_store::*)(std::auto_ptr<vdjml::Read_result>)
      >(&Result_store::insert),
      "add new result"
   )
   .def(
      "meta",
      static_cast<
         Results_meta& (Result_store::*)()
      >(&Result_store::meta),
      bp::return_internal_reference<>()
   )
   ;

   bp::def(
      "write_to_file", &vdjml::write_to_file,
      (
               bp::arg("path"),
               bp::arg("store"),
               bp::arg("compression") = vdjml::Unknown_compression,
               bp::arg("version") = unsigned(VDJML_CURRENT_VERSION),
               bp::arg("options") = vdjml::Xml_writer_options()
      )
   );
}

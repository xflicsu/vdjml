/** @file "/vdjml/binding/python/read_result.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/read_result.hpp"
#include "vdjml/result_store.hpp"
using vdjml::Read_result;
using vdjml::Segment_match;
using vdjml::Seg_match_id;
using vdjml::Segment_match_map;
using vdjml::Results_meta;
using vdjml::Result_store;

void export_read_result() {
   bp::class_<Read_result, std::auto_ptr<Read_result> >(
            "Read_result",
            "Analysis results for one sequencing read",
            bp::init<std::string>()
   )
   .def("id", &Read_result::id, bp::return_internal_reference<>(), "read ID string")
   .def(
            "__getitem__",
            static_cast<
               Segment_match const& (Read_result::*)(const Seg_match_id) const
            >(&Read_result::operator[]),
            bp::return_internal_reference<>(),
            "access segment match"
   )
   .def(
            "segment_matches",
            static_cast<
               Segment_match_map const& (Read_result::*)() const
            >(&Read_result::segment_matches),
            bp::return_internal_reference<>(),
            "map of segment matches"
   )
   .def(
            "segment_combinations",
            static_cast<
            Read_result::seg_comb_store const& (Read_result::*)() const
            >(&Read_result::segment_combinations),
            bp::return_internal_reference<>(),
            "list of segment combinations"
   )
   ;
}

void export_result_store() {
   bp::class_<Result_store>(
            "Result_store",
            "Storage of sequencing read results",
            bp::init<boost::shared_ptr<Results_meta> >()
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
               void (Result_store::*)(std::auto_ptr<Read_result>)
            >(&Result_store::insert),
            "add new result"
   )
   .def(
            "meta",
            static_cast<
               Results_meta& (Result_store::*)()
            >(&Result_store::meta),
            bp::return_internal_reference<>())
   ;


   bp::enum_<vdjml::Compression>("Compression")
   .value("Unknown_compression", vdjml::Unknown_compression)
   .value("Uncompressed", vdjml::Uncompressed)
   .value("gzip", vdjml::gzip)
   .value("bzip2", vdjml::bzip2)
   .value("zlib", vdjml::zlib)
   ;

   bp::def(
            "write_to_file", &vdjml::write_to_file,
            (
                     bp::arg("path"),
                     bp::arg("store"),
                     bp::arg("compression") = vdjml::Unknown_compression,
                     bp::arg("version") = unsigned(VDJML_CURRENT_VERSION)
            )
   );
}

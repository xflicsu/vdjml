/** @file "/vdjml/binding/python/results_meta.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/results_meta.hpp"
using vdjml::Results_meta;

void export_results_meta() {
   bp::class_<Results_meta, std::auto_ptr<Results_meta> >(
      "Results_meta",
      "Metadata for a collection of alignment results of sequencing reads"
   )
   .def(
         "__getitem__",
         static_cast<
            vdjml::Aligner_info const&
            (Results_meta::*)(const vdjml::Aligner_id) const
         >(&Results_meta::operator[]),
         bp::return_internal_reference<>(),
         "get aligner info"
   )
   .def(
         "__getitem__",
         static_cast<
            vdjml::Gl_db_info const&
            (Results_meta::*)(const vdjml::Gl_db_id) const
         >(&Results_meta::operator[]),
         bp::return_internal_reference<>(),
         "get germline DB info"
   )
   .def(
         "__getitem__",
         static_cast<
            std::string const& (Results_meta::*)(const vdjml::Numsys_id) const
         >(&Results_meta::operator[]),
         bp::return_internal_reference<>(),
         "get numbering system name"
   )
   .def(
         "__getitem__",
         static_cast<
            vdjml::Gl_segment_info const&
            (Results_meta::*)(const vdjml::Gl_seg_id) const
         >(&Results_meta::operator[]),
         bp::return_internal_reference<>(),
         "get germline segment info"
   )
   .def(
         "__getitem__",
         static_cast<
         std::string const& (Results_meta::*)(const vdjml::Region_id) const
         >(&Results_meta::operator[]),
         bp::return_internal_reference<>(),
         "get gene region info"
   )
   .def(
         "add_gl_db",
         &Results_meta::add_gl_db,
         (
            bp::arg("name"),
            bp::arg("version"),
            bp::arg("species"),
            bp::arg("url") = ""
         ),
         "add information about a database of germline segments"
   )
   .def(
         "add_aligner",
         &Results_meta::add_aligner,
         (
            bp::arg("name"),
            bp::arg("version"),
            bp::arg("parameters"),
            bp::arg("run_id") = 0
         ),
         "add information about aligner software"
   )
   .def(
         "add_segment",
         &Results_meta::add_segment,
         (
            bp::arg("gl_db"),
            bp::arg("vdj"),
            bp::arg("name")
         ),
         "add information about germline segment"
   )
   ;
}


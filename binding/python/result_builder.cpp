/** @file "/vdjml/binding/python/result_builder.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/result_builder.hpp"
#include "vdjml/results_meta.hpp"
using vdjml::Result_factory;
using vdjml::Result_builder;
using vdjml::Seg_match_id;
using vdjml::Segment_match_builder;
using vdjml::Segment_combination_builder;

void export_result_builder() {

   /**  */
   bp::class_<Segment_combination_builder>(
            "Segment_combination_builder",
            "Construct alignment results for a combination of germline gene segments",
            bp::no_init
   )
   .def(
            "add_region",
            static_cast<
               void (Segment_combination_builder::*)(
                        std::string const&,
                        vdjml::interval_short const&,
                        vdjml::Match_metrics const&,
                        vdjml::Numsys_id num_system
               )
            >(&Segment_combination_builder::add_region),
            "add gene region alignment info"
   )
   .def(
            "add_region",
            static_cast<
               void (Segment_combination_builder::*)(
                        const vdjml::Region_id,
                        vdjml::interval_short const&,
                        vdjml::Match_metrics const&,
                        vdjml::Numsys_id num_system
               )
            >(&Segment_combination_builder::add_region),
            "add gene region alignment info"
   )
   ;

   /**  */
   bp::class_<Segment_match_builder>(
            "Segment_match_builder",
            "Construct alignment results for one sequencing read segment match",
            bp::no_init
   )
   .def(
            "add_gl_segment",
            static_cast<
               vdjml::Gl_seg_match_id (Segment_match_builder::*)(
                        const vdjml::Gl_seg_id,
                        vdjml::interval_short const&,
                        vdjml::Match_metrics const&,
                        vdjml::Numsys_id num_system,
                        vdjml::Aligner_id aligner
               )
            >(&Segment_match_builder::add_gl_segment),
            "add germline segment alignment info"
   )
   .def(
            "add_gl_segment",
            static_cast<
               vdjml::Gl_seg_match_id (Segment_match_builder::*)(
                        const char,
                        std::string const&,
                        vdjml::interval_short const&,
                        vdjml::Match_metrics const&,
                        vdjml::Gl_db_id gl_database,
                        vdjml::Numsys_id num_system,
                        vdjml::Aligner_id aligner
               )
            >(&Segment_match_builder::add_gl_segment),
            "add germline segment alignment info"
   )
   .def("add_aa_substitution", &Segment_match_builder::add_aa_substitution)
   ;

   /**  */
   bp::class_<Result_builder>(
            "Result_builder",
            "Construct alignment results for one sequencing read",
            bp::init<vdjml::Results_meta&, std::string const&>(
                     (bp::arg("meta"), bp::arg("read_id"))
            )
   )
   .def(
            "get",
            static_cast<
               vdjml::Read_result const& (Result_builder::*)() const
            >(&Result_builder::get),
            bp::return_internal_reference<>(),
            "get result object"
   )
   .def("add_segment_match", &Result_builder::add_segment_match)
   .def(
            "add_segment_combination",
            &Result_builder::add_segment_combination,
            (
                     bp::arg("seg_match_1"),
                     bp::arg("seg_match_2") = Seg_match_id(),
                     bp::arg("seg_match_3") = Seg_match_id(),
                     bp::arg("seg_match_4") = Seg_match_id(),
                     bp::arg("seg_match_5") = Seg_match_id()
            )
   )
   ;

   /**  */
   bp::class_<Result_factory>(
            "Result_factory",
            "Construct alignment results for many sequencing reads",
            bp::init<vdjml::Results_meta&>()
   )
   .def("new_result", &Result_factory::new_result, "new result builder")
   .def(
            "set_default_gl_database",
            static_cast<
               void (Result_factory::*)(const vdjml::Gl_db_id)
            >(&Result_factory::set_default_gl_database),
            "set default germline database"
   )
   .def(
            "set_default_gl_database",
            static_cast<
            vdjml::Gl_db_id (Result_factory::*)(
                     std::string const&,
                     std::string const&,
                     std::string const&,
                     std::string const&
            )
            >(&Result_factory::set_default_gl_database),
            "set default germline database",
            (bp::arg("name"), bp::arg("version"),
                     bp::arg("species"), bp::arg("url") = "")
   )
   .def(
            "set_default_aligner",
            static_cast<
               void (Result_factory::*)(const vdjml::Aligner_id)
            >(&Result_factory::set_default_aligner),
            "set default aligner"
   )
   .def(
            "set_default_aligner",
            static_cast<
            vdjml::Aligner_id (Result_factory::*)(
                     std::string const&,
                     std::string const&,
                     std::string const&,
                     const unsigned
            )
            >(&Result_factory::set_default_aligner),
            "set default aligner",
            (bp::arg("name"), bp::arg("version"),
                     bp::arg("parameters"), bp::arg("run_id"))
   )
   .def(
            "set_default_num_system",
            static_cast<
               void (Result_factory::*)(const vdjml::Numsys_id)
            >(&Result_factory::set_default_num_system),
            "set default numbering system"
   )
   .def(
            "set_default_num_system",
            static_cast<
            vdjml::Numsys_id (Result_factory::*)(std::string const&)
            >(&Result_factory::set_default_num_system),
            "set default numbering system",
            (bp::arg("name"))
   )
   ;
}

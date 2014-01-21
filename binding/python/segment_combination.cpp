/** @file "/vdjml/binding/python/segment_combination.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/segment_combination.hpp"
using vdjml::Gene_region;
using vdjml::Segment_combination;
using vdjml::Seg_match_id;

void export_segment_combination() {

   bp::class_<Gene_region>(
      "Gene_region",
      "information about gene region alignment",
      bp::init<
         const vdjml::Numsys_id,
         const vdjml::Region_id,
         vdjml::interval_short const&,
         vdjml::Match_metrics const&
      >(
               (
                        bp::arg("num_system"),
                        bp::arg("region"),
                        bp::arg("range"),
                        bp::arg("mm")
               )
      )
   )
   .def(boost::python::self < boost::python::self)
   .def(boost::python::self > boost::python::self)
   .def(boost::python::self <= boost::python::self)
   .def(boost::python::self >= boost::python::self)
   .def(boost::python::self == boost::python::self)
   .def(boost::python::self != boost::python::self)
   .def("score", &Gene_region::score)
   .def("identity", &Gene_region::identity)
   .def("insertions", &Gene_region::insertions)
   .def("deletions", &Gene_region::deletions)
   .def("substitutions", &Gene_region::stop_codon)
   .def("stop_codon", &Gene_region::score)
   .def("mutated_invariant", &Gene_region::mutated_invariant)
   .def("is_inverted", &Gene_region::is_inverted)
   .def_readonly("num_system_", &Gene_region::num_system_)
   .def_readonly("region_", &Gene_region::region_)
   .def_readonly("range_", &Gene_region::range_)
   ;

   bp::class_<Segment_combination>(
      "Segment_combination",
      "combination of aligned germline segments",
      bp::init<
         const Seg_match_id,
         const Seg_match_id,
         const Seg_match_id,
         const Seg_match_id,
         const Seg_match_id
      >(
               (
                        bp::arg("seg_match_1"),
                        bp::arg("seg_match_2") = Seg_match_id(),
                        bp::arg("seg_match_3") = Seg_match_id(),
                        bp::arg("seg_match_4") = Seg_match_id(),
                        bp::arg("seg_match_5") = Seg_match_id()
               )
      )
   )
   .def("insert_region", &Segment_combination::insert_region)
   ;
}


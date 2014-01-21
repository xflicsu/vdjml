/** @file "/vdjml/binding/python/segment_match.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/segment_match.hpp"
using vdjml::Segment_match;
using vdjml::Gl_segment_match;
using vdjml::Gl_seg_match_id;
using vdjml::Aa_substitution;
using vdjml::Gl_position;
typedef Segment_match::germline_segment_map gl_segment_map;
typedef Segment_match::aa_substitution_set aa_substitutions;

void export_segment_match() {

   bp::class_<Gl_position>(
      "Gl_position",
      "position in a germline sequence",
      bp::init<const Gl_seg_match_id, const unsigned>(
       (bp::arg("id"), bp::arg("gl_pos"))
      )
   )
   .def_readonly("gsm_", &Gl_position::gsm_, "germline segment match ID")
   .def_readonly(
            "gl_pos_",
            &Gl_position::gl_pos_,
            "0-based position of first nucleotide in germline DB entry"
   )
   ;

   bp::class_<Aa_substitution>(
      "Aa_substitution",
      "amino acid substitution",
      bp::init<const unsigned, const char, const char>(
       (bp::arg("read_pos"), bp::arg("aa_from"), bp::arg("aa_to"))
      )
   )
   .def_readonly(
            "read_pos_",
            &Aa_substitution::read_pos_,
            "0-based position of first nucleotide in the read"
   )
   .def_readonly(
            "from_",
            &Aa_substitution::from_,
            "amino acid in germline"
   )
   .def_readonly(
            "to_",
            &Aa_substitution::to_,
            "amino acid in read"
   )
   ;

   bp::class_<aa_substitutions>(
      "Aa_substitutions_set",
      "Set of amino acid substitutions",
      bp::no_init
   )
   .def("__len__", &aa_substitutions::size, "todo:")
   .def("empty", &aa_substitutions::empty, "todo:")
   .def(
         "__getitem__",
         static_cast<
            Aa_substitution const&
            (aa_substitutions::*)
            (const std::size_t) const
         >(&aa_substitutions::operator[]),
         bp::return_internal_reference<>(),
         "amino acid substitution"
   )
   .def(
      "__iter__",
      bp::range<bp::return_value_policy<bp::copy_const_reference> >(
         static_cast<
            aa_substitutions::const_iterator (aa_substitutions::*)() const
         >(&aa_substitutions::begin),
         static_cast<
            aa_substitutions::const_iterator (aa_substitutions::*)() const
         >(&aa_substitutions::end)
      )
   )
   ;

   bp::class_<Gl_segment_match>(
      "Gl_segment_match",
      "Describe alignment to germline segment",
      bp::init<
         const vdjml::Numsys_id,
         const vdjml::Aligner_id,
         const vdjml::Gl_seg_id,
         vdjml::interval_short const&,
         vdjml::Match_metrics const&
      >(
               (
                        bp::arg("num_system"),
                        bp::arg("aligner"),
                        bp::arg("germline_segment"),
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
   .def("score", &Gl_segment_match::score)
   .def("identity", &Gl_segment_match::identity)
   .def("insertions", &Gl_segment_match::insertions)
   .def("deletions", &Gl_segment_match::deletions)
   .def("substitutions", &Gl_segment_match::stop_codon)
   .def("stop_codon", &Gl_segment_match::score)
   .def("mutated_invariant", &Gl_segment_match::mutated_invariant)
   .def("is_inverted", &Gl_segment_match::is_inverted)
   .def_readonly("id_", &Gl_segment_match::id_)
   .def_readonly("num_system_", &Gl_segment_match::num_system_)
   .def_readonly("aligner_", &Gl_segment_match::aligner_)
   .def_readonly("gl_segment_", &Gl_segment_match::gl_segment_)
   .def_readonly("range_", &Gl_segment_match::range_)
   ;

   bp::class_<gl_segment_map>(
      "Gl_segment_map",
      "Map of germline segments aligned to read interval",
      bp::no_init
   )
   .def("__len__", &gl_segment_map::size, "todo:")
   .def("empty", &gl_segment_map::empty, "todo:")
   .def(
         "__getitem__",
         static_cast<
            Gl_segment_match const&
            (gl_segment_map::*)
            (const Gl_seg_match_id) const
         >(&gl_segment_map::operator[]),
         bp::return_internal_reference<>(),
         "germline segment match"
   )
   .def(
      "__iter__",
      bp::range<bp::return_value_policy<bp::copy_const_reference> >(
         static_cast<
            gl_segment_map::const_iterator (gl_segment_map::*)() const
         >(&gl_segment_map::begin),
         static_cast<
            gl_segment_map::const_iterator (gl_segment_map::*)() const
         >(&gl_segment_map::end)
      )
   )
   ;

   bp::class_<Segment_match>(
      "Segment_match",
      "Alignment results for a read segment",
      bp::init<vdjml::Btop const&, vdjml::interval_short const&>(
         (
            bp::arg("btop"), bp::arg("read_range")
         )
      )
   )
   .def("id", &Segment_match::id, "segment match ID")
   .def(
      "btop",
      &Segment_match::btop,
      bp::return_internal_reference<>(),
      "BTOP alignment description"
   )
   .def(
      "range",
      &Segment_match::range,
      bp::return_internal_reference<>(),
      "matched read interval"
   )
   .def(
            "insert",
            static_cast<
               Gl_seg_match_id (Segment_match::*)(Gl_segment_match const&)
            >(&Segment_match::insert),
            "insert germline segment match"
   )
   .def(
            "insert",
            static_cast<
               void (Segment_match::*)(Aa_substitution const&)
            >(&Segment_match::insert),
            "insert amino acid substitution"
   )
   ;
}

/** @file "/vdjml/binding/python/read_result.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/read_result.hpp"
using vdjml::Read_result;

void export_read_result() {

   bp::class_<Read_result, std::auto_ptr<Read_result> >(
            "Read_result",
            "Analysis results for one sequencing read",
            bp::init<std::string>()
   )
   .def(
            "id",
            &Read_result::id, bp::return_value_policy<bp::copy_const_reference>(),
            "read ID string"
   )
   .def(
            "__getitem__",
            static_cast<
               vdjml::Segment_match const& (Read_result::*)(const vdjml::Seg_match_id) const
            >(&Read_result::operator[]),
            bp::return_internal_reference<>(),
            "access segment match"
   )
   .def(
            "segment_matches",
            static_cast<
               vdjml::Segment_match_map const& (Read_result::*)() const
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
   .def(
            "insert",
            static_cast<
               vdjml::Seg_match_id (Read_result::*)(vdjml::Segment_match const&)
            >(&Read_result::insert),
            "insert segment match"
   )
   .def(
            "insert",
            static_cast<
               void (Read_result::*)(vdjml::Segment_combination const&)
            >(&Read_result::insert),
            "insert combination of segment matches"
   )
   ;
}

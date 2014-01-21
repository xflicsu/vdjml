/** @file "/vdjml/binding/python/object_ids.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
#include "boost/preprocessor/stringize.hpp"
#include "vdjml/object_ids.hpp"

#define VDJML_EXPORT_OBJECT_ID(full_name, short_name, doc_str)                \
   boost::python::class_<full_name>(                                          \
               BOOST_PP_STRINGIZE(short_name),                                \
               doc_str                                                        \
            )                                                                 \
            .def(boost::python::init<full_name::value_type>())                \
            .def(str(boost::python::self))                                    \
            .def(boost::python::self < boost::python::self)                   \
            .def(boost::python::self > boost::python::self)                   \
            .def(boost::python::self <= boost::python::self)                  \
            .def(boost::python::self >= boost::python::self)                  \
            .def(boost::python::self == boost::python::self)                  \
            .def(boost::python::self != boost::python::self)                  \
            .def("__call__", &full_name::operator())                          \
/*  */

void export_ids() {
   VDJML_EXPORT_OBJECT_ID(vdjml::Aligner_id, Aligner_id, "Aligner software ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Gl_db_id, Gl_db_id, "Germline database ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Numsys_id, Numsys_id, "Numbering system ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Seg_match_id, Seg_match_id, "Segment match ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Gl_seg_id, Gl_seg_id, "Germline segment ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Gl_seg_match_id, Gl_seg_match_id, "Germline segment match ID");
   VDJML_EXPORT_OBJECT_ID(vdjml::Region_id, Region_id, "Gene region type ID");
}


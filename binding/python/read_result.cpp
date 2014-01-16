/** @file "/vdjml/binding/python/read_result.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/read_result.hpp"
#include "vdjml/result_store.hpp"
using vdjml::Read_result;

void export_read_result() {
   bp::class_<Read_result>(
            "Read_result",
            "Analysis results of a single sequencing read",
            bp::init<std::string>()
   )
   .def("id", &Read_result::id, bp::return_internal_reference<>(), "read ID string")
   ;
}

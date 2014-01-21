/** @file "/vdjml/binding/python/vdjml.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/exception.hpp"

void export_ids();
void export_misc_types();
void export_read_result();
void export_result_store();
void export_results_meta();
void export_result_writer();
void export_segment_match();
void export_segment_combination();
void export_result_builder();

namespace{
void exception_translator(boost::exception const& e) {
   PyErr_SetString(
         PyExc_RuntimeError, boost::diagnostic_information(e).c_str()
   );
}

}//anonymous namespace

BOOST_PYTHON_MODULE(_vdjml_py) {
   bp::register_exception_translator<boost::exception>(&exception_translator);
   bp::object package = bp::scope();
   package.attr("__path__") = "_vdjml_py";
   export_ids();
   export_misc_types();
   export_read_result();
   export_result_store();
   export_results_meta();
   export_result_writer();
   export_segment_match();
   export_segment_combination();
   export_result_builder();
}

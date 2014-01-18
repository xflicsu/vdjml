/** @file "/vdjml/binding/python/vdjml.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

void export_ids();
void export_read_result();
void export_result_store();
void export_results_meta();
void export_result_writer();

BOOST_PYTHON_MODULE(_vdjml) {
   bp::object package = bp::scope();
   package.attr("__path__") = "_vdjml";
   export_ids();
   export_read_result();
   export_result_store();
   export_results_meta();
   export_result_writer();
}

/** @file "/vdjml/lib/test/result_meta_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE result_meta_run
#include "boost/test/unit_test.hpp"
#include <iostream>
#include "test/exception_fixture.hpp"
#include "vdjml/results_meta.hpp"
#include "vdjml/xml_writer.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Results_meta rm;
   Xml_writer xw(std::cout);
   rm.germline_db_map().insert(
            Gl_db_info("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org")
   );

   rm.germline_db_map().insert(
            Gl_db_info("IGHV", "123-0", "Mus musculus", "http://www.imgt.org")
   );

   rm.aligner_map().insert(
            Aligner_info("IMGT", "42-13", "", 0)
   );

   write(xw, rm);
//   BOOST_ERROR("");
}

}//namespace test
}//namespace vdjml

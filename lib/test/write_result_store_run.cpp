/** @file "/vdjml/lib/test/write_result_store_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE write_result_store_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/result_store.hpp"
#include <iostream>
//#include "sample_data.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Xml_writer xw(std::cout);
   Result_store rs;

   rs.meta().germline_db_map().insert(
            Germline_db_info("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org")
   );

   rs.meta().germline_db_map().insert(
            Germline_db_info("IGHV", "123-0", "Mus musculus", "http://www.imgt.org")
   );

   rs.meta().aligner_map().insert(
            Aligner_info("IMGT", "42-13", "", 0)
   );

   write(xw, rs);

   BOOST_ERROR("");

}

}//namespace test
}//namespace vdjml

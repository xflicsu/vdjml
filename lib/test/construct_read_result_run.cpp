/** @file "/vdjml/lib/test/construct_read_result_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE construct_read_result_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include <iostream>
#include "test/exception_fixture.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/results_meta.hpp"
#include "vdjml/result_builder.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Results_meta rm ;
   Result_factory rf(rm);
   rf.set_default_aligner("V-QUEST", " 3.2.32", "", 0);
   rf.set_default_gl_database("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org");
   rf.set_default_num_system(Num_system::imgt);

   Result_builder rb1 = rf.new_result("Y14934");

   std::auto_ptr<Read_result> p1 = rb1.release();
   BOOST_CHECK(p1.get());
   std::auto_ptr<Read_result> p2 = rb1.release();
   BOOST_CHECK(!p2.get());

}

}//namespace test
}//namespace vdjml

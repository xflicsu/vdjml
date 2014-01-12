/** @file "/vdjml/lib/test/construct_read_result_run.cpp" 
part of vdjml project.
@n @n Distributed under GNU General Public License, Version 3;
see doc/license.txt.
@n Copyright Mikhail K Levin 2014
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
}

}//namespace test
}//namespace vdjml

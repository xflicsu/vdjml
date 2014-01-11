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
   Result_builder rb(rm, "Y14934");
}

}//namespace test
}//namespace vdjml

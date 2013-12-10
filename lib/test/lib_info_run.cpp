/** @file "/vdjml/lib/test/lib_info_run.cpp"
part of VDJML project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Author Mikhail K Levin 2013
*******************************************************************************/
#define BOOST_TEST_MODULE lib_info_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/lib_info.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test Test library info class
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   BOOST_CHECK_EQUAL(Lib_info::name(), "VDJML");
   BOOST_CHECK( ! Lib_info::version().empty() );
   BOOST_CHECK_GT( Lib_info::build(), 0 );
}

}//namespace test
}//namespace vdjml

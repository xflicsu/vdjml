/** @file "/vdjml/lib/test/interval_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE interval_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/interval.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   interval_65k i1 = interval_65k::first_last_0(10, 20);
   BOOST_CHECK_EQUAL(i1.pos_0(), 10U);
   BOOST_CHECK_EQUAL(i1.pos_1(), 11U);
   BOOST_CHECK_EQUAL(i1.length(), 11U);
   BOOST_CHECK_EQUAL(i1.last_0(), 20U);
   BOOST_CHECK_EQUAL(i1.last_1(), 21U);

   interval_65k i2 = interval_65k::first_last_1(10, 20);
   BOOST_CHECK_EQUAL(i2.pos_0(), 9U);
   BOOST_CHECK_EQUAL(i2.pos_1(), 10U);
   BOOST_CHECK_EQUAL(i2.length(), 11U);
   BOOST_CHECK_EQUAL(i2.last_0(), 19U);
   BOOST_CHECK_EQUAL(i2.last_1(), 20U);

   BOOST_CHECK(i1 != i2);
   BOOST_CHECK(i1 > i2);

   BOOST_CHECK_THROW(interval_65k::first_last_0(10, 9), Interval_err);
   BOOST_CHECK_THROW(interval_65k::first_last_1(0, 10), Interval_err);
}

}//namespace test
}//namespace vdjml

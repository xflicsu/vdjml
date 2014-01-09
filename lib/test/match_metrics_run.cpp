/** @file "/vdjml/lib/test/match_metrics_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE match_metrics_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/match_metrics.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Match_metrics mm1(-1, 42.2, 0, 0, 0);
   BOOST_CHECK_EQUAL(mm1.score(), -1);
   BOOST_CHECK_EQUAL(mm1.identity(), 42.2f);
   BOOST_CHECK( ! mm1.stop_codon() );
   BOOST_CHECK( ! mm1.mutated_invariant() );
   BOOST_CHECK( ! mm1.is_inverted() );

   Match_metrics mm2(-1, 42.2, 0, 0, 0, true);
   BOOST_CHECK_EQUAL(mm2.score(), -1);
   BOOST_CHECK_EQUAL(mm2.identity(), 42.2f);
   BOOST_CHECK(   mm2.stop_codon() );
   BOOST_CHECK( ! mm2.mutated_invariant() );
   BOOST_CHECK( ! mm2.is_inverted() );

   Match_metrics mm3(-1, 42.2, 0, 0, 0, false, true);
   BOOST_CHECK_EQUAL(mm3.score(), -1);
   BOOST_CHECK_EQUAL(mm3.identity(), 42.2f);
   BOOST_CHECK( ! mm3.stop_codon() );
   BOOST_CHECK(   mm3.mutated_invariant() );
   BOOST_CHECK( ! mm3.is_inverted() );

   Match_metrics mm4(-1, 42.2, 0, 0, 0, false, true, true);
   BOOST_CHECK_EQUAL(mm4.score(), -1);
   BOOST_CHECK_EQUAL(mm4.identity(), 42.2f);
   BOOST_CHECK( ! mm4.stop_codon() );
   BOOST_CHECK(   mm4.mutated_invariant() );
   BOOST_CHECK(   mm4.is_inverted() );
}

}//namespace test
}//namespace vdjml

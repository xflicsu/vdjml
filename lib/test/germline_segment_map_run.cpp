/** @file "/vdjml/lib/test/germline_segment_map_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE germline_segment_map_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/germline_segment_map.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Gl_segment_map gsm;
   const Gl_seg_id id1 = gsm.insert(Gl_db_id(1), 'V', "IGHV3-21*01");
   const Gl_seg_id id2 = gsm.insert(Gl_db_id(1), 'V', "IGHV3-21*02");
   BOOST_CHECK_NE(id1, id2);
   const Gl_seg_id id2a = gsm.insert(Gl_db_id(1), 'V', "IGHV3-21*02");
   BOOST_CHECK_EQUAL(id2, id2a);
   const Gl_seg_id id3 = gsm.insert(Gl_db_id(2), 'V', "IGHV3-21*02");

   BOOST_CHECK_THROW(
            gsm.insert(Gl_db_id(2), 'D', "IGHV3-21*02"),
            Gl_segment_map::Err
   ); //same name, DB -- different type

   BOOST_CHECK_NE(id2, id3);
   Gl_segment_map::name_range nr1 = gsm.find("IGHV3-21*01");
   BOOST_CHECK_EQUAL(distance(nr1), 1);
   Gl_segment_map::name_range nr2 = gsm.find("IGHV3-21*02");
   BOOST_CHECK_EQUAL(distance(nr2), 2);

   BOOST_CHECK(gsm.find(Gl_db_id(1), "IGHV3-21*01"));
   BOOST_CHECK(gsm.find(Gl_db_id(2), "IGHV3-21*02"));
   BOOST_CHECK( ! gsm.find(Gl_db_id(1), "IGHV3-21*03"));
   BOOST_CHECK( ! gsm.find(Gl_db_id(3), "IGHV3-21*02"));
}

}//namespace test
}//namespace vdjml

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
#include "vdjml/read_result.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test test read result ownership
*******************************************************************************/
BOOST_AUTO_TEST_CASE( ownership ) {
   Results_meta rm ;
   Result_factory rf(rm);
   rf.set_default_aligner("V-QUEST", " 3.2.32", "", 0);
   rf.set_default_gl_database("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org");
   rf.set_default_num_system(Num_system::imgt);

   Result_builder rb1 = rf.new_result("Y14934");

   std::auto_ptr<Read_result> p1 = rb1.release();
   BOOST_CHECK(p1.get());
   BOOST_CHECK_THROW(rb1.get(), Result_builder::Err);
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case02 ) {
   Results_meta rm ;
   Result_factory rf(rm);
   rf.set_default_aligner("V-QUEST", " 3.2.32", "", 0);
   rf.set_default_gl_database("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org");
   rf.set_default_num_system(Num_system::imgt);

   Result_builder rb1 = rf.new_result("Y14934");

   const Seg_match_id smid1 = rb1.add_segment_match(
            "61AC10A-136",
            interval_short::first_last_1(1, 275),
            'V',
            "IGHV3-21*01",
            interval_short::first_last_1(22, 296),
            Match_metrics(264, 96.0, 0, 0, 11)
   ).get().id();

   const Seg_match_id smid1a = rb1.add_segment_match(
            "61AC10A-136",
            interval_short::first_last_1(1, 275),
            'V',
            "IGHV3-21*02",
            interval_short::first_last_1(22, 296),
            Match_metrics(264, 96.0, 0, 0, 11)
   ).get().id(); //this entry should be merged with previous

   BOOST_CHECK_EQUAL(rb1.get().segment_match_map().size(), 1U);
   BOOST_CHECK_EQUAL(smid1, smid1a);

   Segment_match_builder smb2 =
            rb1.add_segment_match(
                     "20", interval_short::first_last_1(275, 295),
                     'D', "IGHD3-22*01",
                     interval_short::first_last_1(11, 31),
                     Match_metrics(22, 100, 0, 0, 0)
   );

   Segment_match_builder smb3 =
            rb1.add_segment_match(
                     "5AC35", interval_short::first_last_1(311, 351),
                     'J', "IGHJ4*02",
                     interval_short::first_last_1(7, 47),
                     Match_metrics(40, 97.6, 0, 0, 1)
   );


}

}//namespace test
}//namespace vdjml

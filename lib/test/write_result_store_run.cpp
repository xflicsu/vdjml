/** @file "/vdjml/lib/test/write_result_store_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE write_result_store_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "test/sample_data.hpp"
#include "vdjml/result_store.hpp"
#include <iostream>
#include <fstream>

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Result_store rs;

   Gl_db_id dbid1 =
            rs.meta().add_gl_db(
                     "IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org"
            );
   rs.meta().add_gl_db("IGHV", "123-0", "Mus musculus", "http://www.imgt.org");

   Aligner_id aid1 = rs.meta().add_aligner("V-QUEST", "3.2.32", "", 0);

   const Gl_seg_id seg_id1 = rs.meta().add_segment(dbid1, 'V', "IGHV3-21*01");
   const Gl_seg_id seg_id2 = rs.meta().add_segment(dbid1, 'V', "IGHV3-21*02");
   const Gl_seg_id seg_id3 = rs.meta().add_segment(dbid1, 'D', "IGHD3-22*01");
   const Gl_seg_id seg_id4 = rs.meta().add_segment(dbid1, 'J', "IGHJ4*02");

   Read_result rr1("Y14934");
   Segment_match sm1(Btop("61AC10A-136"), interval_short::first_last_1(1, 275));
   const Gl_segment_match gsm1(
            Num_system::imgt,
            aid1,
            seg_id1,
            interval_short::first_last_1(22, 296),
            Match_metrics(96.0, 264, 0, 0, 11)
   );
   sm1.insert(gsm1);

   const Gl_segment_match gsm2(
            Num_system::imgt,
            aid1,
            seg_id2,
            interval_short::first_last_1(22, 296),
            Match_metrics(96.0, 264, 0, 0, 11)
   );
   sm1.insert(gsm2);
   const Seg_match_id sm_id1 = rr1.insert(sm1);

   Segment_match sm2(Btop("20"), interval_short::first_last_1(275, 295));
   const Gl_segment_match gsm3(
            Num_system::imgt,
            aid1,
            seg_id3,
            interval_short::first_last_1(11, 31),
            Match_metrics(100, 22, 0, 0, 0)
   );
   sm2.insert(gsm3);
   const Seg_match_id sm_id2 = rr1.insert(sm2);

   Segment_match sm3(Btop("5AC35"), interval_short::first_last_1(311, 351));
   const Gl_segment_match gsm4(
            Num_system::imgt,
            aid1,
            seg_id4,
            interval_short::first_last_1(7, 47),
            Match_metrics(97.6, 40, 0, 0, 1)
   );
   sm3.insert(gsm4);
   const Seg_match_id sm_id3 = rr1.insert(sm3);

   Segment_combination sc1(sm_id1, sm_id2, sm_id3);
   sc1.insert_region(
                     Num_system::imgt,
                     Gene_region_type::fr1,
                     interval_short::first_last_1(1,54),
                     Match_metrics(100, 54, 0, 0, 0)
   );
   sc1.insert_region(
                     Num_system::imgt,
                     Gene_region_type::cdr1,
                     interval_short::first_last_1(55,78),
                     Match_metrics(83.3, 24, 0, 0, 4)
   );
   sc1.insert_region(
                     Num_system::imgt,
                     Gene_region_type::fr2,
                     interval_short::first_last_1(79,129),
                     Match_metrics(98, 59, 0, 0, 1)
   );
   rr1.insert(sc1);

   rs.insert(rr1);

   write(std::cout, rs);
   const std::string out = temp_file_path("out1.vdjml");
   write_to_file(out, rs);

//   BOOST_ERROR("");

}

}//namespace test
}//namespace vdjml

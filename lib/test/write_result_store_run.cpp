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
   Result_store rs;

   Gl_db_id dbid1 =
            rs.meta().add_gl_db(
                     "IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org"
            );
   rs.meta().add_gl_db("IGHV", "123-0", "Mus musculus", "http://www.imgt.org");

   Aligner_id aid1 = rs.meta().add_aligner("V-QUEST", " 3.2.32", "", 0);

   const Gl_segment_info seg1(dbid1, 'V', "IGHV3-21*01");
   const Gl_seg_id seg_id1 = rs.meta().germline_segment_map().insert(seg1);

   const Gl_segment_info seg2(dbid1, 'V', "IGHV3-21*02");
   const Gl_seg_id seg_id2 = rs.meta().germline_segment_map().insert(seg2);

   const Gl_segment_info seg3(dbid1, 'D', "IGHD3-22*01");
   const Gl_seg_id seg_id3 = rs.meta().germline_segment_map().insert(seg3);

   const Gl_segment_info seg4(dbid1, 'J', "IGHJ4*02");
   const Gl_seg_id seg_id4 = rs.meta().germline_segment_map().insert(seg4);

   Read_result rr1("Y14934");
   Segment_match sm1(Btop("61AC10A-136"), interval_65k::first_last_1(1, 275));
   const Germline_segment_match gsm1(
            Num_system_map::imgt().first,
            aid1,
            seg_id1,
            interval_65k::first_last_1(22, 296),
            Match_metrics(264, 96.0, 0, 0, 11)
   );
   sm1.insert(gsm1);

   const Germline_segment_match gsm2(
            Num_system_map::imgt().first,
            aid1,
            seg_id2,
            interval_65k::first_last_1(22, 296),
            Match_metrics(264, 96.0, 0, 0, 11)
   );
   sm1.insert(gsm2);
   const Seg_match_id sm_id1 = rr1.insert(sm1);

   Segment_match sm2(Btop("20"), interval_65k::first_last_1(275, 295));
   const Germline_segment_match gsm3(
            Num_system_map::imgt().first,
            aid1,
            seg_id3,
            interval_65k::first_last_1(11, 31),
            Match_metrics(22, 100, 0, 0, 0)
   );
   sm2.insert(gsm3);
   const Seg_match_id sm_id2 = rr1.insert(sm2);

   Segment_match sm3(Btop("5AC35"), interval_65k::first_last_1(311, 351));
   const Germline_segment_match gsm4(
            Num_system_map::imgt().first,
            aid1,
            seg_id4,
            interval_65k::first_last_1(7, 47),
            Match_metrics(40, 97.6, 0, 0, 1)
   );
   sm3.insert(gsm4);
   const Seg_match_id sm_id3 = rr1.insert(sm3);

   Segment_combination sc1(sm_id1, sm_id2, sm_id3);
   sc1.grv_.push_back(
            Gene_region(
                     Num_system_map::imgt().first,
                     Gene_region_map::fr1().first,
                     interval_65k::first_last_1(1,54),
                     Match_metrics(54, 100, 0, 0, 0)
            )
   );
   sc1.grv_.push_back(
            Gene_region(
                     Num_system_map::imgt().first,
                     Gene_region_map::cdr1().first,
                     interval_65k::first_last_1(55,78),
                     Match_metrics(24, 83.3, 0, 0, 4)
            )
   );
   sc1.grv_.push_back(
            Gene_region(
                     Num_system_map::imgt().first,
                     Gene_region_map::fr2().first,
                     interval_65k::first_last_1(79,129),
                     Match_metrics(59, 98, 0, 0, 1)
            )
   );
   rr1.insert(sc1);

   rs.insert(rr1);

   Xml_writer xw(std::cout);
   write(xw, rs);

//   BOOST_ERROR("");

}

}//namespace test
}//namespace vdjml

#!/usr/bin/env python

'''
vdjml/binding/python/test/write_result_store.py is part of VDJML project
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
Author Mikhail K Levin 2014
'''

import unittest
import vdjml

class Test(unittest.TestCase):
    def test_1(self):
        rs = vdjml.Result_store()
        db = rs.meta().add_gl_db(
                                 'IGHV', '123-0', 'Homo Sapiens', 
                                 'http://www.imgt.org'
                                 )
        aligner = rs.meta().add_aligner('V-QUEST', '3.2.32', '', 0)
        seg_id1 = rs.meta().add_segment(db, 'V', 'IGHV3-21*01')
        seg_id2 = rs.meta().add_segment(db, 'V', 'IGHV3-21*02')
        seg_id3 = rs.meta().add_segment(db, 'D', 'IGHD3-22*01')
        seg_id4 = rs.meta().add_segment(db, 'J', 'IGHJ4*02')
        
        rr1 = vdjml.Read_result("Y14934")
        sm1 = vdjml.Segment_match(vdjml.Btop('61AC10A-136'), vdjml.Interval.first_last_1(1, 275))
        gsm1 = vdjml.Gl_segment_match(
                                      vdjml.Num_system.imgt, 
                                      aligner, 
                                      seg_id1,
                                      vdjml.Interval.first_last_1(22, 296),
                                      vdjml.Match_metrics(96.0, 264, 11)
                                      )
        sm1.insert(gsm1)
        
        gsm2 = vdjml.Gl_segment_match(
                                      vdjml.Num_system.imgt, 
                                      aligner, 
                                      seg_id2,
                                      vdjml.Interval.first_last_1(22, 296),
                                      vdjml.Match_metrics(96.0, 264, 11)
                                      )
        sm1.insert(gsm2)
        sm_id1 = rr1.insert(sm1)
        
        sm2 = vdjml.Segment_match(vdjml.Btop('20'), vdjml.Interval.first_last_1(275, 295))
        gsm3 = vdjml.Gl_segment_match(
                                      vdjml.Num_system.imgt, 
                                      aligner, 
                                      seg_id3,
                                      vdjml.Interval.first_last_1(11, 31),
                                      vdjml.Match_metrics(100, 22)
                                      )
        sm2.insert(gsm3)
        sm_id2 = rr1.insert(sm2)
        
        sm3 = vdjml.Segment_match(vdjml.Btop('5AC35'), vdjml.Interval.first_last_1(311, 351))
        gsm4 = vdjml.Gl_segment_match(
                                      vdjml.Num_system.imgt, 
                                      aligner, 
                                      seg_id3,
                                      vdjml.Interval.first_last_1(7, 47),
                                      vdjml.Match_metrics(97.6, 40, 1)
                                      )
        sm3.insert(gsm4)
        sm_id3 = rr1.insert(sm2)
        
        sc1 = vdjml.Segment_combination(sm_id1, sm_id2, sm_id3)
        sc1.insert_region(
                          vdjml.Num_system.imgt,
                          vdjml.Gene_region_type.fr1,
                          vdjml.Interval.first_last_1(1,54),
                          vdjml.Match_metrics(100, 54)
                          )
        sc1.insert_region(
                          vdjml.Num_system.imgt,
                          vdjml.Gene_region_type.cdr1,
                          vdjml.Interval.first_last_1(55,78),
                          vdjml.Match_metrics(83.3, 24, 4)
                          )
        sc1.insert_region(
                          vdjml.Num_system.imgt,
                          vdjml.Gene_region_type.fr2,
                          vdjml.Interval.first_last_1(79, 129),
                          vdjml.Match_metrics(98, 59, 1)
                          )
        
        rr1.insert(sc1)
        
        rs.insert(rr1);
        vdjml.write_to_file('out/temp/pyout1.vdjml', rs)
        
if __name__ == '__main__': unittest.main()

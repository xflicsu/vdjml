#!/usr/bin/env python

'''
vdjml/binding/python/test/build_results.py is part of VDJML project
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
Author Mikhail K Levin 2014
'''

import unittest
import vdjml

class Test(unittest.TestCase):
    def test_1(self):
        # create results metainformation object
        meta = vdjml.Results_meta()
        
        # create results factory
        fact = vdjml.Result_factory(meta)
        
        fact.set_default_aligner(
                                 name='V-QUEST', 
                                 version='3.2.32', 
                                 parameters='', 
                                 run_id=0
                                 )
        
        fact.set_default_gl_database(
                                     name='IGHV', 
                                     version='123-0', 
                                     species='Homo Sapiens', 
                                     url='http://www.imgt.org'
                                     )
        
        fact.set_default_num_system(vdjml.Num_system.imgt)
        
        # create result builder 
        rb1 = fact.new_result(read_id='Y14934')
        
        smb1 = rb1.add_segment_match(
                                    btop='61AC10A-136',
                                    read_range=vdjml.Interval.first_last_1(1, 275),
                                    vdj='V',
                                    seg_name='IGHV3-21*01',
                                    gl_range=vdjml.Interval.first_last_1(22, 296),
                                    metric=vdjml.Match_metrics(
                                                               score=264, 
                                                               identity=96.0, 
                                                               insertions=0, 
                                                               deletions=0, 
                                                               substitutions=11
                                                               )
                                     )
        smb1.add_aa_substitution(
                                 read_pos_0=60, 
                                 aa_read='P', 
                                 aa_gl='T', 
                                 gl_pos_0=83
                                 )
        
        smb1a = rb1.add_segment_match(
                                    btop='61AC10A-136',
                                    read_range=vdjml.Interval.first_last_1(1, 275),
                                    vdj='V',
                                    seg_name='IGHV3-21*02',
                                    gl_range=vdjml.Interval.first_last_1(22, 296),
                                    metric=vdjml.Match_metrics(
                                                               score=264, 
                                                               identity=96.0, 
                                                               substitutions=11
                                                               )
                                     )
        #segment matches smb1 and smb1a have same BTOPs and same read ranges
        #therefore they should be merged automatically
        self.assertEqual(smb1.get().id(), smb1a.get().id())
        
        smb2 = rb1.add_segment_match(
                                     btop='20', 
                                     read_range=vdjml.Interval.first_last_1(275, 295),
                                     vdj='D', 
                                     seg_name='IGHD3-22*01',
                                     gl_range=vdjml.Interval.first_last_1(11, 31),
                                     metric=vdjml.Match_metrics(22, 100)
                                     )
        
        smb3 = rb1.add_segment_match(
                                     btop='5AC35', 
                                     read_range=vdjml.Interval.first_last_1(311, 351),
                                     vdj='J', 
                                     seg_name='IGHJ4*02',
                                     gl_range=vdjml.Interval.first_last_1(7, 47),
                                     metric=vdjml.Match_metrics(40, 97.6, 0, 0, 1)
                                     )
        
        scb = rb1.add_segment_combination(
                                          smb1.get().id(),
                                          smb2.get().id(),
                                          smb3.get().id() 
                                          )
        scb.add_region(
                        name='FR1',
                        read_range=vdjml.Interval.first_last_1(1,54),
                        metric=vdjml.Match_metrics(54, 100, 0, 0, 0)
                       )
        scb.add_region(
                        name='CDR1',
                        read_range=vdjml.Interval.first_last_1(55,78),
                        metric=vdjml.Match_metrics(24, 83.3, 0, 0, 4)
                       )
        scb.add_region(
                        name='FR2',
                        read_range=vdjml.Interval.first_last_1(79,129),
                        metric=vdjml.Match_metrics(59, 98, 0, 0, 1)
                       )
        
        rrw1 = vdjml.Result_writer('out/temp/py_out_2.vdjml', meta)
        rrw1(rb1.get())
    
if __name__ == '__main__': unittest.main()

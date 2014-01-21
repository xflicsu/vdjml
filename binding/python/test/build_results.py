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
        meta = vdjml.Results_meta()
        fact = vdjml.Result_factory(meta)
        fact.set_default_aligner('V-QUEST', '3.2.32', '', 0)
        fact.set_default_gl_database(
                                     'IGHV', 
                                     '123-0', 
                                     'Homo Sapiens', 
                                     'http://www.imgt.org'
                                     )
        fact.set_default_num_system(vdjml.Num_system.imgt)
        
        rb1 = fact.new_result('Y14934')
        
        smb1 = rb1.add_segment_match(
                                    '61AC10A-136',
                                    vdjml.Interval.first_last_1(1, 275),
                                    'V',
                                    'IGHV3-21*01',
                                    vdjml.Interval.first_last_1(22, 296),
                                    vdjml.Match_metrics(264, 96.0, 0, 0, 11)
                                     )
        smb1.add_aa_substitution(61, 'P', 'T', 84)
        
        smb1a = rb1.add_segment_match(
                                    '61AC10A-136',
                                    vdjml.Interval.first_last_1(1, 275),
                                    'V',
                                    'IGHV3-21*02',
                                    vdjml.Interval.first_last_1(22, 296),
                                    vdjml.Match_metrics(264, 96.0, 0, 0, 11)
                                     )
        #segment matches smb1 and smb1a have same BTOPs and same read ranges
        #therefore they should be merged automatically
        self.assertEqual(smb1.get().id(), smb1a.get().id())
        
        smb2 = rb1.add_segment_match(
                                     '20', 
                                     vdjml.Interval.first_last_1(275, 295),
                                     'D', 
                                     'IGHD3-22*01',
                                     vdjml.Interval.first_last_1(11, 31),
                                     vdjml.Match_metrics(22, 100, 0, 0, 0)
                                     )
        
        smb3 = rb1.add_segment_match(
                                     '5AC35', 
                                     vdjml.Interval.first_last_1(311, 351),
                                     'J', 
                                     'IGHJ4*02',
                                     vdjml.Interval.first_last_1(7, 47),
                                     vdjml.Match_metrics(40, 97.6, 0, 0, 1)
                                     )
        
        scb = rb1.add_segment_combination(
                                          smb1.get().id(),
                                          smb2.get().id(),
                                          smb3.get().id() 
                                          )
        scb.add_region(
                        'FR1',
                        vdjml.Interval.first_last_1(1,54),
                        vdjml.Match_metrics(54, 100, 0, 0, 0)
                       )
        scb.add_region(
                        'CDR1',
                        vdjml.Interval.first_last_1(55,78),
                        vdjml.Match_metrics(24, 83.3, 0, 0, 4)
                       )
        scb.add_region(
                        'FR2',
                        vdjml.Interval.first_last_1(79,129),
                        vdjml.Match_metrics(59, 98, 0, 0, 1)
                       )
        
        rrw1 = vdjml.Result_writer('out/temp/py_out_2.vdjml', meta)
        rrw1(rb1.get())
    
if __name__ == '__main__': unittest.main()

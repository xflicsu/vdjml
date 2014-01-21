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
        fact.set_default_aligner("V-QUEST", " 3.2.32", "", 0)
        fact.set_default_gl_database("IGHV", "123-0", "Homo Sapiens", "http://www.imgt.org")
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
        
    
if __name__ == '__main__': unittest.main()

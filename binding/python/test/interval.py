#!/usr/bin/env python

'''
vdjml/binding/python/test/interval.py is part of VDJML project
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
Author Mikhail K Levin 2014
'''

import unittest
import vdjml

class Test(unittest.TestCase):
    def test_1(self):
        #Interval should not be instantiated directly
        with self.assertRaises(RuntimeError) : i0 = vdjml.Interval()
        #use static methods instead:
        i1 = vdjml.Interval.pos0_len(10, 5)
        i2 = vdjml.Interval.first_last_0(10, 14)
        self.assertEqual(i1, i2)
        i3 = vdjml.Interval.first_last_1(11, 15)
        self.assertEqual(i1, i3)
        i4 = vdjml.Interval.first_last_1(10, 14)
        self.assertGreater(i1, i4)
        
if __name__ == '__main__': unittest.main()

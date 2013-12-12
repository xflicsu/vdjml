#!/usr/bin/env python

'''
vdjml/binding/python/test/test.py is part of VDJML project
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
Author Mikhail K Levin 2013
'''

import unittest
import vdjml

class Test(unittest.TestCase):
    def test_1(self):
        rr1 = vdjml.Read_result("id")

if __name__ == '__main__': unittest.main()

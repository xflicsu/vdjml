#!/usr/bin/env python

import sys, shutil, os

root_dir = os.path.abspath(sys.argv[1])
dir_from_py_test = os.path.join(root_dir, 'binding', 'python', 'test')
dir_to_py = os.path.join(root_dir, 'out', 'binding', 'python')
dir_to_py_test = os.path.join(dir_to_py, 'test')
shutil.rmtree(dir_to_py_test, ignore_errors=True)
shutil.copytree(
                dir_from_py_test, 
                dir_to_py_test, 
                ignore =shutil.ignore_patterns('*.jam')
                )

shutil.copy(os.path.join(root_dir, 'README.txt'), dir_to_py)
dir_to_py_doc = os.path.join(dir_to_py, 'doc')
if not os.path.exists(dir_to_py_doc): os.mkdir(dir_to_py_doc)
shutil.copy(os.path.join(root_dir, 'doc', 'license.txt'), dir_to_py_doc)

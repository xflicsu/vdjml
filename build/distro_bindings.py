#!/usr/bin/env python

import sys, shutil, os, sphinx, glob

def mkdir(d0, *d):
    if d: dir = os.path.join(d0, *d)
    else: dir = d0
    if not os.path.exists(dir): os.makedirs(dir)
    return dir

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
dir_to_py_doc_src = mkdir(dir_to_py_doc, 'src')
shutil.copy(
            os.path.join(root_dir, 'doc', 'py_index.txt'), 
            os.path.join(dir_to_py_doc_src, 'index.rst')
            )
shutil.copy(
            os.path.join(root_dir, 'doc', 'license.txt'), 
            os.path.join(dir_to_py_doc_src, 'license.rst')
            )
mkdir(dir_to_py_doc_src, '_static')
mkdir(dir_to_py_doc_src, '_templates')

sphinx.main(['', '-a', '-b', 'html', 'doc/src', 'doc'])


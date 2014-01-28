#!/usr/bin/env python

'''
vdjml/binding/python/test/result_generator.py is part of VDJML project
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
Author Mikhail K Levin 2014
'''

import unittest
import vdjml

def get_results(factory, n_max):
    '''
    Example of result generator.
    VDJ alignment results are obtained from some source, e.g., a file.
    This generator recycles same results.
    It will stop after creating n_max results. 
    '''
    n = 0
    while n < n_max: #or check for the end of source file
        n += 1
        rb = factory.new_result('READ_ID_' + str(n))
        smb1 = rb.add_segment_match(
                                    btop='61AC10A-136',
                                    read_range=vdjml.Interval.first_last_1(1, 275),
                                    vdj='V',
                                    seg_name='IGHV3-21*01',
                                    gl_range=vdjml.Interval.first_last_1(22, 296),
                                    metric=vdjml.Match_metrics(
                                                               identity=96.0,
                                                               score=264, 
                                                               substitutions=11,
                                                               insertions=0, 
                                                               deletions=0,
                                                               stop_codon=False,
                                                               mutated_invariant=False,
                                                               is_inverted=False
                                                               )
                                     )
        smb1.add_aa_substitution(
                                 read_pos_0=60, 
                                 aa_read='P', 
                                 aa_gl='T', 
                                 gl_pos_0=83
                                 )
        
        smb1a = rb.add_segment_match(
                                    btop='61AC10A-136',
                                    read_range=vdjml.Interval.first_last_1(1, 275),
                                    vdj='V',
                                    seg_name='IGHV3-21*02',
                                    gl_range=vdjml.Interval.first_last_1(22, 296),
                                    metric=vdjml.Match_metrics(
                                                               identity=96.0,
                                                               score=264,
                                                               substitutions=11
                                                               )
                                     )
        #segment matches smb1 and smb1a have same BTOPs and same read ranges
        #therefore they should be merged automatically
        
        smb2 = rb.add_segment_match(
                                     btop='20', 
                                     read_range=vdjml.Interval.first_last_1(275, 295),
                                     vdj='D', 
                                     seg_name='IGHD3-22*01',
                                     gl_range=vdjml.Interval.first_last_1(11, 31),
                                     metric=vdjml.Match_metrics(100, 22)
                                     )
        
        smb3 = rb.add_segment_match(
                                     btop='5AC35', 
                                     read_range=vdjml.Interval.first_last_1(311, 351),
                                     vdj='J', 
                                     seg_name='IGHJ4*02',
                                     gl_range=vdjml.Interval.first_last_1(7, 47),
                                     metric=vdjml.Match_metrics(97.6, 40, 1)
                                     )
        
        scb = rb.add_segment_combination(
                                          smb1.get().id(),
                                          smb2.get().id(),
                                          smb3.get().id() 
                                          )
        scb.add_region(
                        name='FR1',
                        read_range=vdjml.Interval.first_last_1(1,54),
                        metric=vdjml.Match_metrics(100.0, 54)
                       )
        scb.add_region(
                        name='CDR1',
                        read_range=vdjml.Interval.first_last_1(55,78),
                        metric=vdjml.Match_metrics(83.3, 24, 4)
                       )
        scb.add_region(
                        name='FR2',
                        read_range=vdjml.Interval.first_last_1(79,129),
                        metric=vdjml.Match_metrics(98, 59, 1)
                       )
        
        #critical piece: this is what makes this function a generator
        yield rb.release() 

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
        
        #make read result writer
        rrw = vdjml.Result_writer('out/temp/py_out_3.vdjml', meta)
        #alternatively, write compressed VDJML
        #rrw = vdjml.Result_writer('out/temp/py_out_3.vdjml.gz', meta)
        #rrw = vdjml.Result_writer('out/temp/py_out_3.vdjml.bz2', meta)
        
        for result in get_results(fact, 10):
            #write out the result
            rrw(result)
            # or do anything else with it
    
if __name__ == '__main__': unittest.main()

#!/usr/bin/env python
#
# Copyright 2004,2007 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
import eventstream as es;
import random;


class qa_es (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_square_ff (self):
        print ("ok")
        #print dir(es);
    
    def test_002_es_source (self):

        tb = gr.top_block();

        # create the arbiter shared memory space
        arb = es.es_make_arbiter();

        # create the source event queue
        queue = es.queue();

        # create the source block and set a max stream length on it
        src = es.source( arb, queue, [gr.sizeof_float] );
        src.set_max(20);
       
        # add a singular event
        vec = es.pmt_float_vector([1,2,3,4]);
        e1 = es.event_create_gen_vector_f( 3, vec );
        h1 = es.es_handler_insert_vector();
        h1p = es.make_handler_pmt( h1 );

        #e1 = es.es_make_event_gen_vector_f(arb, [1,2,3,4]);
        #e1.set_time(13)

        #print (dir(es))
        #e1 = es.event_create( "test_event", 13, 4 );
        #e1 = es.event_create( "test_event", 13, 4 );
        queue.register_event_type( es.event_type( e1 ) );
        queue.bind_handler( es.event_type( e1 ), h1p );
        queue.add_event(e1);
        
        # set up a vector sink for printing
        snk = gr.vector_sink_f();
        tb.connect(src, snk);

        # run the graph to completion and print output stream
        tb.run();
        print (snk.data());
    

if __name__ == '__main__':
    gr_unittest.main ()


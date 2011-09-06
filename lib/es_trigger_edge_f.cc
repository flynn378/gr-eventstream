/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <es/es.h>
#include <gr_io_signature.h>
#include <stdio.h>
#include <string.h>

/*
 * Create a new instance of es_trigger_edge_f and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
es_trigger_edge_f_sptr 
es_make_trigger_edge_f (pmt_t arb, es_queue_sptr queue, float thresh, int length, int lookback) {
  return es_trigger_edge_f_sptr (new es_trigger_edge_f (arb,queue,thresh,length,lookback));

}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr_block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.  In this case, we accept
 * only 1 input and 1 output.
 */
static const int MIN_IN = 1;	// mininum number of input streams
static const int MAX_IN = 1;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

es_trigger_edge_f::es_trigger_edge_f (pmt_t _arb, es_queue_sptr _queue, float thresh, int length, int lookback)
  : d_thresh(thresh), es_trigger (_arb, _queue, sizeof(float), "es_trigger_edge_f")
{
    printf("num event_types = %d\n", event_types.size());
    event_types[0] = pmt_intern("event_trigger");
    d_length = length;
    d_lookback = lookback;   
}

es_trigger_edge_f::~es_trigger_edge_f ()
{
}

int 
es_trigger_edge_f::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
  
  float *in = (float*) input_items[0];
  float *out = (float*) output_items[0];
    
  printf("es_trigger_edge_f::work() running.\n");
    
  // copy input to output
  memcpy(out, in, noutput_items*sizeof(float));
 
  d_lastval = (d_time==0)?in[0]:d_lastval;
  if(d_time == 0){ d_lastval = in[0]; }
  
  for(int i=0; i<noutput_items; i++){
    //printf("in[i]=%f, d_thresh=%f, d_lastval=%f\n", in[i], d_thresh, d_lastval);
    if(in[i] > d_thresh && d_lastval < d_thresh){
    
        // create an event at the appropriate time,
        //  factoring lookback and event length specified in constructor
        pmt_t e1 = event_create( event_type(0), d_time-d_lookback, d_length );
      
        // add event to our queue
        event_queue->add_event(e1);
    }
    d_lastval = in[i];
    d_time++;
  }
  
  // consume the current input items
  d_time += noutput_items;
  return noutput_items;
  
}



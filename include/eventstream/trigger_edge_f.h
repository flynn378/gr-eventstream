/* -*- c++ -*- */
/*
 * Copyright 2011 Free Software Foundation, Inc.
 * 
 * This file is part of gr-eventstream
 * 
 * gr-eventstream is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * gr-eventstream is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-eventstream; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_EVENTSTREAM_TRIGGER_EDGE_F_H
#define INCLUDED_EVENTSTREAM_TRIGGER_EDGE_F_H

#include <gnuradio/sync_block.h>
#include <pmt/pmt.h>
#include <eventstream/queue.h>
#include <eventstream/trigger.h>

namespace gr {
namespace eventstream {
class eventstream_trigger_edge_f;
using namespace pmt;

typedef boost::shared_ptr<eventstream_trigger_edge_f> eventstream_trigger_edge_f_sptr;

eventstream_trigger_edge_f_sptr eventstream_make_trigger_edge_f (float thresh, int length, int lookback, int itemsize, int guard=1);

class eventstream_trigger_edge_f : public eventstream_trigger
{
private:
  friend eventstream_trigger_edge_f_sptr eventstream_make_trigger_edge_f (float thresh, int length, int lookback, int itemsize, int guard);

  eventstream_trigger_edge_f (float thresh, int length, int lookback, int itemsize, int guard=1);  	// private constructor
  int d_guard;
  uint64_t d_lasttrigger;

 public:
  ~eventstream_trigger_edge_f ();	// public destructor
  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);

  void set_thresh(float thresh);

  float d_thresh;
  float d_lastval;
};
}
}

#endif /* INCLUDED_EVENTSTREAM_TRIGGER_EDGE_F_H */

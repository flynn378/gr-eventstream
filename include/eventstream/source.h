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
#ifndef INCLUDED_EVENTSTREAM_SOURCE_H
#define INCLUDED_EVENTSTREAM_SOURCE_H

#include <gnuradio/sync_block.h>
#include <pmt/pmt.h>
#include <eventstream/queue.h>
#include <eventstream/source_thread.hh>
#include <eventstream/event_acceptor.h>
#include <functional>
#include <boost/function.hpp>
#include <boost/lockfree/queue.hpp>
namespace gr {
namespace eventstream {

enum eventstream_source_merge_behavior {
  MEMCPY,
  ADD_INT8S,
  ADD_INT16S,
  ADD_FLOATS,
};

class eventstream_source;
using namespace pmt;

typedef boost::shared_ptr<eventstream_source> eventstream_source_sptr;

eventstream_source_sptr eventstream_make_source (gr_vector_int out_sig, int nthreads=1, enum eventstream_queue_early_behaviors = DISCARD, enum eventstream_source_merge_behavior = MEMCPY);

class eventstream_source : public virtual gr::sync_block, public virtual eventstream_event_acceptor
{
private:
  friend eventstream_source_sptr eventstream_make_source (gr_vector_int out_sig, int nthreads, enum eventstream_queue_early_behaviors, enum eventstream_source_merge_behavior);

  eventstream_source (gr_vector_int out_sig, int nthreads=1, enum eventstream_queue_early_behaviors = DISCARD, enum eventstream_source_merge_behavior = MEMCPY);  	// private constructor

  eventstream_handler_sptr ih;

 public:
  ~eventstream_source ();	// public destructor

  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);

  eventstream_source_merge_behavior d_merge_mode;

  void set_max(unsigned long long maxlen);

  boost::condition qq_cond;

  boost::lockfree::queue<eventstream_eh_pair*> qq;        // work items to start
  boost::lockfree::queue<unsigned long long> dq; // finished time indexes

  boost::mutex lin_mut;
  std::vector<pmt_t> readylist;

  std::vector<boost::shared_ptr<eventstream_source_thread> > threadpool;

  bool cb(eventstream_eh_pair** eh);

  int n_threads;

  unsigned long long d_maxlen;
  unsigned long long d_time;
  unsigned int d_history;

  unsigned long long time();
};
}
}

#endif /* INCLUDED_EVENTSTREAM_SQUARE_FF_H */

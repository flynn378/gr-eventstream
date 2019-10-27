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

#ifndef INCLUDED_EVENTSTREAM_SINK_H
#define INCLUDED_EVENTSTREAM_SINK_H

#include <gnuradio/sync_block.h>
#include <pmt/pmt.h>
#include <eventstream/queue.h>
#include <eventstream/event_loop_thread.hh>
#include <eventstream/eh_pair.hh>
#include <eventstream/event_acceptor.h>
#include <boost/lockfree/queue.hpp>
#include <semaphore.h>

#include <gnuradio/top_block.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

namespace gr {
namespace eventstream {
    
class eventstream_sink;
using namespace pmt;
using namespace boost::accumulators;

typedef accumulator_set<double, stats<tag::rolling_mean> > acc_avg_t;
typedef boost::shared_ptr<eventstream_sink> eventstream_sink_sptr;

enum eventstream_congestion_behaviors {
            DROP,
            BLOCK
};

eventstream_sink_sptr eventstream_make_sink (
    gr_vector_int insig,
    int n_threads,
    int sample_history_in_kilosamples=64,
    enum eventstream_queue_early_behaviors = DISCARD,
    enum eventstream_search_behaviors = SEARCH_BINARY,
    enum eventstream_congestion_behaviors = DROP);

class eventstream_sink : public virtual eventstream_handler, public virtual eventstream_event_acceptor
{
private:
  pmt::pmt_t latest_tags;

  //New constructor with user-selectable sample history.
  friend eventstream_sink_sptr eventstream_make_sink (
    gr_vector_int insig,
    int n_threads,
    int sample_history_in_kilosamples,
    enum eventstream_queue_early_behaviors,
    enum eventstream_search_behaviors,
    enum eventstream_congestion_behaviors);
  eventstream_sink (
    gr_vector_int insig,
    int n_threads,
    int sample_history_in_kilosamples=64,
    enum eventstream_queue_early_behaviors = DISCARD,
    enum eventstream_search_behaviors = SEARCH_BINARY,
    enum eventstream_congestion_behaviors = DROP);  // private constructor
  void handler(pmt_t msg, gr_vector_void_star buf);

 public:
  ~eventstream_sink ();	// public destructor

  int work (int noutput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);
  int num_events();
  uint64_t num_discarded();
  uint64_t num_asap();
  uint64_t num_soon();
  uint64_t num_events_added();
  uint64_t num_events_removed();
  uint64_t buffer_min_time();
  uint64_t buffer_max_time();
  uint64_t buffer_window_size();
  uint64_t event_time();
  uint64_t num_running_handlers();
  uint64_t event_queue_size();
  double event_run_ratio();
  double event_thread_utilization();

  unsigned long long d_time;
  unsigned int d_history;
  int n_threads;
  int sample_history_in_kilosamples;

  boost::atomic<int> d_nevents;
  void wait_events();

  boost::condition qq_cond;

  boost::lockfree::queue<eventstream_eh_pair*> qq;
  boost::lockfree::queue<unsigned long long> dq;

  std::vector<boost::shared_ptr<eventstream_event_loop_thread> > threadpool;
  std::vector<uint64_t> live_event_times;

  bool state_done_prevent_exit() { return (d_nevents + event_queue->length())!=0; }
  bool state_done_call_empty() { return (d_nevents + event_queue->length())!=0; }
  void setup_rpc();
  bool start();
  bool stop();


  private:
    uint64_t d_buffer_window_size;
    boost::atomic<uint64_t> d_num_running_handlers;
    acc_avg_t d_avg_ratio;
    acc_avg_t d_avg_thread_utilization;

    /**
     * @brief Configuration variable for selecting an insertion sort algorithm.
     */
    eventstream_search_behaviors d_search_behavior;
    int find_index(const uint64_t& evt_time);
    size_t find_forward(const uint64_t& evt_time);
    size_t find_reverse(const uint64_t& evt_time);
    size_t find_binary(const uint64_t& evt_time);
    /**
     * @brief Configuration variable for defining behavior when queue is full.
     */
    eventstream_congestion_behaviors d_congestion_behavior;



};

}
}
#endif /* INCLUDED_EVENTSTREAM_SQUARE2_FF_H */

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

#ifndef EVENTSTREAM_EVENTLOOP_THREAD_H
#define EVENTSTREAM_EVENTLOOP_THREAD_H

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>
#include <pmt/pmt.h>
#include <eventstream/queue.h>
#include <eventstream/common.h>
#include <eventstream/eh_pair.hh>
#include <semaphore.h>

using namespace pmt;
namespace gr {
namespace eventstream {

class eventstream_event_loop_thread {

    public:

        //eventstream_event_loop_thread();
        eventstream_event_loop_thread(
            pmt_t _arb,
            eventstream_queue_sptr _queue,
            boost::lockfree::queue<eventstream_eh_pair*> *qq,
            boost::lockfree::queue<unsigned long long> *dq,
            boost::condition *qq_cond,
            boost::atomic<int> *nevents,
            boost::atomic<uint64_t> *num_running_handlers);
        void start();
        void stop();
        void do_work();
        boost::atomic<int> *d_nevents;
        boost::atomic<uint64_t> *d_num_running_handlers;

    private:
        pmt_t arb;
        eventstream_queue_sptr queue;

        bool finished;
        boost::shared_ptr<boost::thread> d_thread;

        //boost::lockfree::queue<pmt_t*> *qq;

        boost::condition *qq_cond;

        boost::lockfree::queue<eventstream_eh_pair*> *qq;
        boost::lockfree::queue<unsigned long long> *dq;

        void eh_run(pmt_t eh);
        sem_t* thread_notify_sem;

};
}
}
#endif

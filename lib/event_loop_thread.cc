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

#include <stdio.h>
#include <eventstream/common.h>
#include <eventstream/event_loop_thread.hh>

namespace gr {
namespace eventstream {
    
/*
 * Constructor function, sets up parameters
 */
eventstream_event_loop_thread::eventstream_event_loop_thread(pmt_t _arb, eventstream_queue_sptr _queue, boost::lockfree::queue<eventstream_eh_pair*> *_qq, boost::lockfree::queue<unsigned long long> *_dq, boost::condition *_qq_cond, boost::atomic<int> *nevents, boost::atomic<uint64_t> *num_running_handlers) :
    arb(_arb),
    queue(_queue),
    qq(_qq),
    dq(_dq),
    qq_cond(_qq_cond),
    finished(false),
    d_nevents(nevents),
    d_num_running_handlers(num_running_handlers)
{
    start();
}

/*
 * kick off a thread running the do_work() main loop function
 */
void eventstream_event_loop_thread::start(){
    d_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&eventstream_event_loop_thread::do_work, this)));
}

/*
 * Shut down all the running threads and join them.
 *   Called by eventstream_sink destructor
 */
void eventstream_event_loop_thread::stop(){
    finished = true;
    qq_cond->notify_all();
    d_thread->interrupt();
    d_thread->join();
}


/*
 *  Main event loop thread work function,
 *    constantly receives and services event/handler pairs
 *    then queues the live_times for deletion.
 */
void eventstream_event_loop_thread::do_work(){

//    // used by boost::condition, has no scope outside of this thread, unneccisary
    boost::mutex access;
    boost::mutex::scoped_lock lock(access);

    // run the thread until we are told to shut down
    while(!finished){
        eventstream_eh_pair* eh = NULL;

        // wait for a signal to start looking in the queue
        qq_cond->wait(lock);
        (*d_num_running_handlers)++;

        // get events to handle as long as they are available
        while( (*qq).pop(eh) ){

            //printf("dequeue returned.\n");

            // run the event/handler pair
            eh->run();

            // enqueue the time marker for deletion
            (*dq).push( eh->time() );

            // decrement number of events
            int a = *d_nevents;
            (*d_nevents)--;

            // delete the reference
            delete eh;
        }
        (*d_num_running_handlers)--;
    }
}
}
}

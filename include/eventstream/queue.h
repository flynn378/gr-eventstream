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

#ifndef EVENTSTREAM_QUEUE_H
#define EVENTSTREAM_QUEUE_H

#include <gnuradio/block.h>
#include <boost/thread/mutex.hpp>
#include <boost/bimap.hpp>
#include <boost/function.hpp>

#include <eventstream/eh_pair.hh>
#include <eventstream/event.h>
#include <eventstream/handler.h>
#include <eventstream/common.h>
    
namespace gr {
namespace eventstream {
    
class eventstream_queue;
typedef boost::shared_ptr<eventstream_queue> eventstream_queue_sptr;



enum eventstream_queue_early_behaviors {
            DISCARD,
            BALK,
            ASAP,
            RNDF
};

eventstream_queue_sptr eventstream_make_queue(
    enum eventstream_queue_early_behaviors = DISCARD,
    enum eventstream_search_behaviors sb = SEARCH_BINARY);

class eventstream_eh_queue;

class eventstream_queue {

    public:

        std::vector<gr::basic_block_sptr> d_hvec;
        eventstream_queue(
            enum eventstream_queue_early_behaviors = DISCARD,
            enum eventstream_search_behaviors = SEARCH_BINARY);
        int add_event(pmt_t evt);
        void print_queue(bool already_locked = false);
        int fetch_next_event(unsigned long long min, unsigned long long max, eventstream_eh_pair **eh);
        int fetch_next_event2(unsigned long long min, unsigned long long max, eventstream_eh_pair **eh);

        void bind_handler(std::string type, gr::basic_block_sptr handler);
        void bind_handler(std::string type, eventstream_handler* handler);
        void bind_handler(pmt_t type, gr::basic_block_sptr handler);

        void protect_handler(eventstream_handler_sptr h){ protected_handler.push_back(h); }

        int register_event_type(std::string type);
        int register_event_type(pmt_t type);

        int d_early_behavior;
        uint64_t d_num_asap, d_num_discarded, d_num_events_added, d_num_events_removed;
        uint64_t d_event_time, d_num_soon;
        int length();

        // set behavior when an item exists before the requested region (BALK or ASAP)
        void set_early_behavior(enum eventstream_queue_early_behaviors);

        // set a callback to be called when an eh pair is added
        void set_append_callback( boost::function<bool (eventstream_eh_pair**)> _cb){
            cb_list.push_back(_cb);
            }


        bool empty(){ return event_queue.empty(); }
        uint64_t min_time(){ return empty()?0: gr::eventstream::event_time(event_queue[0]->event); }

    private:
        std::vector<eventstream_eh_pair*> event_queue;
        pmt_t bindings;
        boost::mutex queue_lock;

        std::vector< eventstream_handler_sptr > protected_handler;
        std::vector< boost::function< bool (eventstream_eh_pair**) > > cb_list;

        /**
         * @brief Configuration variable for selecting an insertion sort algorithm.
         */
        eventstream_search_behaviors d_search_behavior;
        int find_index(uint64_t evt_time);
        size_t find_forward(const uint64_t evt_time);
        size_t find_reverse(const uint64_t evt_time);
        size_t find_binary(const uint64_t evt_time);
};

}
}


#endif

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
#ifndef EVENTSTREAM_HANDLER_H
#define EVENTSTREAM_HANDLER_H

#include <pmt/pmt.h>
#include <gnuradio/msg_accepter.h>
#include <gnuradio/sync_block.h>

using namespace pmt;

namespace gr {
namespace eventstream {

class eventstream_handler;

typedef boost::shared_ptr<eventstream_handler> eventstream_handler_sptr;

class eventstream_handler : public virtual gr::sync_block
{
    public:
        eventstream_handler();
        gr_vector_void_star get_buffer_ptr(pmt_t buffer_pmt);
        void handler_helper( pmt_t msg );
        virtual void handler(pmt_t msg, gr_vector_void_star buf);
        ~eventstream_handler();
        virtual int work (int noutput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);

};
}
}
#endif



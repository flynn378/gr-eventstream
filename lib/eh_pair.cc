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

#include <eventstream/eh_pair.hh>
#include <eventstream/common.h>
#include <eventstream/handler.h>
#include <stdio.h>

namespace gr {
namespace eventstream {
    
eventstream_eh_pair::eventstream_eh_pair(pmt_t _event, pmt_t _handler) :
    handler(_handler), 
    event(_event)
    {

}

void eventstream_eh_pair::run(){

    // new style handler call
    eventstream_handler* h = boost::any_cast< eventstream_handler* >(pmt::any_ref(handler));
    h->handler_helper( event );

}


unsigned long long eventstream_eh_pair::time(){
    return event_time( event );
}

unsigned long long eventstream_eh_pair::length(){
    return event_length( event );
}

eventstream_eh_pair::~eventstream_eh_pair(){
//    printf("eventstream_eh_pair::destructor running.\n");
}

}
}

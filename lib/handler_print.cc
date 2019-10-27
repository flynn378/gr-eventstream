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

#include <eventstream/api.h>
//#include <eventstream/eventstream_handler_print.h>
#include <stdio.h>

namespace gr {
namespace eventstream {

eventstream_handler_sptr eventstream_make_handler_print(eventstream_handler_print::DATATYPE type){
    return eventstream_handler_sptr(new eventstream_handler_print(type));
}

eventstream_handler_print::eventstream_handler_print( DATATYPE type )
 :  gr::sync_block("eventstream_handler_file",
        gr::io_signature::make(0,0,0),
        gr::io_signature::make(0,0,0))
{
    d_type = type;
}

//void eventstream_handler_print::handler( pmt_t msg, void* buf ){
void eventstream_handler_print::handler( pmt_t msg, gr_vector_void_star buf ){
    event_print(msg);
    switch(d_type){
        case TYPE_F32:
            {
            printf(" vector_contents = [");
            float* fbuf = (float*) buf[0];
            for(int i=0; i<event_length(msg); i++){
                printf("%f, ", fbuf[i]);
                }
            printf("]\n");
            break;
            }
        case TYPE_C32:
            {
            printf(" vector_contents = [");
            gr_complex* fbuf = (gr_complex*) buf[0];
            for(int i=0; i<event_length(msg); i++){
                printf("%f+%fj, ", fbuf[i].real(), fbuf[i].imag());
                }
            printf("]\n");
            break;
            }
        default:
            printf("unknown vector content type.\n");
        }

}

}
}



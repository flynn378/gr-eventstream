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
#include <eventstream/gen_vector.h>
#include <gnuradio/io_signature.h>

namespace gr {
namespace eventstream {

pmt_t event_create_gen_vector_f ( unsigned long long time, pmt_t float_list ){
    assert(pmt::is_f32vector(float_list));
    int len = pmt::length(float_list);
    pmt_t evt = event_create( eventstream::event_type_gen_vector_f, time, (uint64_t)len);
    return event_args_add( evt, pmt::intern("vector"), float_list );
}

pmt_t event_create_gen_vector_c ( unsigned long long time, pmt_t cpx_list ){
    assert(pmt::is_c32vector(cpx_list));
    int len = pmt::length(cpx_list);
    pmt_t evt = event_create( eventstream::event_type_gen_vector_c, time, (uint64_t)len);
    return event_args_add( evt, pmt::intern("vector"), cpx_list );
}

pmt_t event_create_gen_vector_b ( unsigned long long time, pmt_t u8_list, int itemsize ){
    assert(pmt::is_u8vector(u8_list));
    int len = pmt::length(u8_list)/itemsize;
    pmt_t evt = event_create( eventstream::event_type_gen_vector_b, time, (uint64_t)len);
    return event_args_add( evt, pmt::intern("vector"), u8_list );
}


pmt_t event_create_gen_vector( unsigned long long time, pmt_t vectors, gr::io_signature::sptr _sig ){
    
    pmt_t buf0 = pmt::nth( 0, vectors );
    assert(pmt::is_u8vector(buf0));

    gr::io_signature* sig = &(*_sig);
    int len = pmt::length(buf0)/((_sig)->sizeof_stream_item(0));
    
    pmt_t evt = event_create( eventstream::event_type_gen_vector, time, (uint64_t)len);
    //return event_args_add( evt, pmt_intern("vectors"), vectors );
    return event_args_add( evt, pmt::intern("vector"), vectors );
    
}
}
}

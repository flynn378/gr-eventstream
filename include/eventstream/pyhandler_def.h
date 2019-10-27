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
#ifndef ES_PYHANDLER_DEF
#define ES_PYHANDLER_DEF

#include <gnuradio/top_block.h>
#include <pmt/pmt.h>
#include <eventstream/vector_source.hh>
#include <eventstream/vector_sink.hh>
#include <map>


#include <Python.h>

//typedef boost::shared_ptr<eventstream_pyhandler> eventstream_pyhandler_sptr;

// return values for factory function execution
// returns a descriptor for the flow graph
// contains a top block to run(), as well as 
// a list of sources, and sinks to be accessed
namespace gr {
namespace eventstream {
class eventstream_pyhandler {
    public:
        eventstream_pyhandler();
        ~eventstream_pyhandler();
        gr::top_block_sptr tb;
        eventstream_vector_source_sptr source;
        eventstream_vector_sink_sptr sink;
        std::map <std::string, gr::basic_block_sptr> blocks;
        PyObject* b2;
        void set_b2(PyObject* _b2);
        PyObject* vars;
        void set_vars(PyObject* _vars);
};



// return values from hook execution
// returns a map of str=>str
struct eventstream_hook_rval {
    std::map<std::string, std::string> map;
};

class eventstream_hook_args {
  private:
    eventstream_hook_args() {};
  public:
    eventstream_hook_args(gr_vector_void_star *bufs, const pmt::pmt_t msg, eventstream_pyhandler* handler);
    gr_vector_void_star *bufs;
    const pmt::pmt_t msg;
    eventstream_pyhandler* handler;
};



eventstream_pyhandler* default_factory_cb( int index, void* _cb_data );

typedef eventstream_pyhandler* (*FACTORYCBTYPE)(int index, void* _cb_data);

eventstream_hook_rval* default_hook_cb( struct eventstream_hook_args*, void* _cb_data );

typedef eventstream_hook_rval* (*HOOKCBTYPE)( struct eventstream_hook_args*, void* _cb_data );


class eventstream_pyhandler_def {

    public:

        eventstream_pyhandler_def();
        
        
        FACTORYCBTYPE factory_callback;
        void* factory_cb_data;
        
        
        HOOKCBTYPE pre_hook_cb;
        void* pre_hook_data;


        HOOKCBTYPE post_hook_cb;
        void* post_hook_data;

        
        void set_factory_cb(FACTORYCBTYPE fp, void* _cb_data);
        void set_pre_hook_cb(HOOKCBTYPE fp, void* _cb_data);
        void set_post_hook_cb(HOOKCBTYPE fp, void* _cb_data);
        
        int d_index;
        eventstream_pyhandler*   run_factory();
        eventstream_hook_rval*    run_pre_hook(gr_vector_void_star &bufs, const pmt::pmt_t &msg, eventstream_pyhandler* handler);
        eventstream_hook_rval*    run_post_hook(gr_vector_void_star &bufs, const pmt::pmt_t &msg, eventstream_pyhandler* handler);

};

}
}
#endif

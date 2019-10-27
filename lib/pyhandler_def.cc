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

#include <Python.h>
#include <stdio.h>
#include <eventstream/pyhandler_def.h>

#define DEBUG(X) 
//#define DEBUG(X)  X
namespace gr {
namespace eventstream {
    
const gr_vector_int emptyvec(0);


eventstream_hook_args::eventstream_hook_args( gr_vector_void_star *_bufs, const pmt::pmt_t _msg, eventstream_pyhandler* _handler)
    : bufs(_bufs), msg(_msg), handler(_handler)
{
}


// default constructor for pyhandler
// setup pointers to not point to nowhere
//
eventstream_pyhandler::eventstream_pyhandler() :
    source( eventstream_make_vector_source(emptyvec) ),
    sink( eventstream_make_vector_sink( emptyvec ) ),
    tb( gr::make_top_block("default pyhandler top block") ),
    b2(NULL)
{
    DEBUG(printf("eventstream_pyhandler constructor running (this=%x)\n", this);)

    // make sure python is ready for threading
    if( Py_IsInitialized() ){
        if(PyEval_ThreadsInitialized() != 1 ){
            PyEval_InitThreads();
        }
    } else {
        throw std::runtime_error("dont use eventstream_pyhandler without python!");
    }


//    printf("source = %x\n", source.get() );
}

eventstream_pyhandler::~eventstream_pyhandler(){
    DEBUG(printf("eventstream_pyhandler destructor running (this=%x)\n", this);)
    if(b2!=NULL){
        Py_DECREF(b2);
    }
}

void eventstream_pyhandler::set_b2(PyObject* _b2){
    b2 = _b2;
    Py_INCREF(b2);
}

void eventstream_pyhandler::set_vars(PyObject* _vars){
    vars = _vars;
    Py_INCREF(vars);
}


//
// default factory function handler
//
eventstream_pyhandler* default_factory_cb( int index, void* _cb_data ){
    throw std::runtime_error("default_factory_cb called, please define one...");
    return NULL;
}

//
// default hook function handler
//
eventstream_hook_rval* default_hook_cb( gr_vector_void_star bufs, const pmt::pmt_t &msg, void* _cb_data){
    DEBUG(printf("default_hook_cb called, noop\n");)
    return NULL;
}

//
// constructor
//
eventstream_pyhandler_def::eventstream_pyhandler_def() :
    d_index(0),
    pre_hook_cb( NULL ),
    pre_hook_data( NULL ),
    post_hook_cb( NULL ),
    post_hook_data( NULL )
{
    set_factory_cb(default_factory_cb, 0);
}


//
// setters for default handler callback functions 
// c++ versions which are proxied to python via swig
//
void eventstream_pyhandler_def::set_factory_cb(FACTORYCBTYPE fp, void* _cb_data){
    DEBUG(printf("eventstream_pyhandler_def::set_factory_cb(%x, %x)\n", fp, _cb_data);)
    factory_callback = fp;
    factory_cb_data = _cb_data;
}
void eventstream_pyhandler_def::set_pre_hook_cb(HOOKCBTYPE fp, void* _cb_data){
    DEBUG(printf("eventstream_pyhandler_def::set_pre_hook_cb(%x, %x)\n", fp, _cb_data);)
    pre_hook_cb = fp;
    pre_hook_data = _cb_data;
}
void eventstream_pyhandler_def::set_post_hook_cb(HOOKCBTYPE fp, void* _cb_data){
    DEBUG(printf("eventstream_pyhandler_def::set_post_hook_cb(%x, %x)\n", fp, _cb_data);)
    post_hook_cb = fp;
    post_hook_data = _cb_data;
}

eventstream_pyhandler* eventstream_pyhandler_def::run_factory(){
    return factory_callback( d_index++, factory_cb_data );
}

eventstream_hook_rval* eventstream_pyhandler_def::run_pre_hook(gr_vector_void_star &bufs, const pmt::pmt_t &msg, eventstream_pyhandler* handler){
    struct eventstream_hook_args hargs(&bufs, msg, handler);
    if(pre_hook_cb == NULL){ 
        return NULL;
    } else {
        return pre_hook_cb( &hargs, pre_hook_data );
    }
}

eventstream_hook_rval* eventstream_pyhandler_def::run_post_hook(gr_vector_void_star &bufs, const pmt::pmt_t &msg, eventstream_pyhandler* handler){
    struct eventstream_hook_args hargs(&bufs, msg, handler);
    if(post_hook_cb == NULL){ 
        return NULL;
    } else {
        return post_hook_cb( &hargs, post_hook_data );
    }
}
}
}



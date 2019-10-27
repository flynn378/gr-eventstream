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

#ifndef EVENTSTREAM_API_H
#define EVENTSTREAM_API_H



#ifdef gnuradio_eventstream_EXPORTS
#  define EVENTSTREAM __GR_ATTR_EXPORT
#else
#  define EVENTSTREAM __GR_ATTR_IMPORT
#endif



#include <gnuradio/attributes.h>
#include <gnuradio/io_signature.h>
#include <eventstream/common.h>
//#include <eventstream/eventstream_event.h>
#include <eventstream/source.h>
#include <eventstream/queue.h>
//#include <eventstream/eventstream_handler.h>
#include <eventstream/sink.h>

#include <eventstream/handler.h>
#include <eventstream/handler_print.h>
//#include <eventstream/eventstream_handler_insert_vector_f.h>
//#include <eventstream/eventstream_handler_extract_vector_f.h>

#include <eventstream/gen_vector.h>
#include <eventstream/handler_insert_vector.h>

#include <eventstream/trigger_edge_f.h>

#endif

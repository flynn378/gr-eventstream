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

%include "runtime_swig.i"			// the common stuff
%include "pmt_swig.i"

namespace std {
   %template(StrVector) vector<std::string>;
};



%{
#include "eventstream/event.h"
#include "eventstream/queue.h"
#include "eventstream/source.h"
#include "eventstream/sink.h"
#include "eventstream/common.h"
#include "eventstream/gen_vector.h"
#include "eventstream/handler.h"
#include "eventstream/eh_pair.hh"
#include "eventstream/handler_insert_vector.h"
#include "eventstream/handler_print.h"
#include "eventstream/handler_file.h"
#include "eventstream/handler_pdu.h"
#include "eventstream/handler_passthrough.h"
#include "eventstream/handler_flowgraph.h"
#include "eventstream/trigger.h"
#include "eventstream/trigger_edge_f.h"
#include "eventstream/trigger_sample_timer.h"
#include "eventstream/pyhandler_def.h"
#include "eventstream/vector_source.hh"
#include "eventstream/vector_sink.hh"
#include "eventstream/patterned_interleaver.h"
%}

//%include "eventstream/handler_pdu.h"
//%include "eventstream/handler_passthrough.h"
//%include "eventstream/handler.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_handler);
//%include "eventstream/event.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_event);
//%include "eventstream_source.i"
//%include "eventstream_sink.i"
//%include "eventstream/source.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_source);
//%include <boost/accumulators/accumulators.hpp>
//%include "eventstream/sink.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_sink);
%include "eventstream/common.h"
%include "eventstream/handler.h"
GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_handler);
//%include "eventstream/handler_print.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_handler_print);
//%include "eventstream/handler_file.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_handler_file);
//%include "eventstream/queue.h"
//%include "eventstream/event.h"
//%include "eventstream/eh_pair.hh"
//%include "eventstream/trigger.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_trigger);
//%include "eventstream/trigger_edge_f.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_trigger_edge_f);
//%include "eventstream/trigger_sample_timer.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_trigger_sample_timer);
//%include "eventstream/vector_source.hh"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_vector_source);
//%include "eventstream/vector_sink.hh"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_vector_sink);
//%include "eventstream/pyhandler_def.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_pyhandler_def);
//%include "eventstream/patterned_interleaver.h"
//GR_SWIG_BLOCK_MAGIC2(eventstream, eventstream_patterned_interleaver);

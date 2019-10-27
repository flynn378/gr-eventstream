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

/*
 * This class gathers together all the test cases for the example
 * directory into a single test suite.  As you create new test cases,
 * add them here.
 */

#include <qa_eventstream.h>
#include <qa_eventstream_common.h>
#include <qa_eventstream_source.h>
#include <qa_eventstream_sink.h>
#include <qa_eventstream_trigger.h>
//#include <qa_eventstream_handler.h>

namespace gr {
namespace eventstream {
    
CppUnit::TestSuite *
qa_eventstream::suite()
{
  CppUnit::TestSuite *s = new CppUnit::TestSuite("eventstream");

  s->addTest(qa_eventstream_source::suite()); 
  s->addTest(qa_eventstream_sink::suite()); 
  s->addTest(qa_eventstream_common::suite()); 
  s->addTest(qa_eventstream_trigger::suite()); 
  return s;

}
}
}

#ifndef ES_EVENT_ACCEPTOR_H
#define ES_EVENT_ACCEPTOR_H

#include <gnuradio/sync_block.h>
#include <eventstream/queue.h>

namespace gr {
  namespace eventstream {
class eventstream_event_acceptor : public virtual gr::sync_block {
    public:
        gr::eventstream::eventstream_queue_sptr event_queue;
        eventstream_event_acceptor(enum eventstream_queue_early_behaviors eb= DISCARD,
                          enum eventstream_search_behaviors sb = SEARCH_BINARY)
            {
            event_acceptor_setup(eb, sb);
            }

        void event_acceptor_setup(enum eventstream_queue_early_behaviors eb= DISCARD,
                                  enum eventstream_search_behaviors sb = SEARCH_BINARY)
        {
            // set up event queue
            event_queue = eventstream_make_queue(eb, sb);

            // listen for events
            message_port_register_in(pmt::mp("schedule_event"));
            set_msg_handler(pmt::mp("schedule_event"),
                boost::bind(&eventstream_event_acceptor::schedule_event, this, _1));
        }

        // handle pmt msgs in...
        void schedule_event(pmt::pmt_t m);

        // register a new event handler based on a recieved registration message
        void add_handlers(pmt::pmt_t h);
};
  } // eventstream namespace
} //gr namespace

#endif

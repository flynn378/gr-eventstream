#ifndef EVENTSTREAM_EXCEPTIONS_H
#define EVENTSTREAM_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace gr {
namespace eventstream {

class EarlyEventException {
    public:
        EarlyEventException(const std::string m = "early event exception!");
        ~EarlyEventException();
        const char* what(){ return msg.c_str();}
    private:
        std::string msg;
    };

}
}


#endif

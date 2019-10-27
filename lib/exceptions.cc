#include <eventstream/exceptions.h>

gr::eventstream::EarlyEventException::EarlyEventException(const std::string m) : msg(m) {}
gr::eventstream::EarlyEventException::~EarlyEventException(){}

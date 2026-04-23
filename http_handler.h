#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include <string>
#include "parser.h"
std::string handle_http_request(const ParsedHTTP& request);

#endif
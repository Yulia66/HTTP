#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

using StringVector = std::vector<std::string>;
using StringPair = std::pair<std::string, std::string>;


struct ParsedHTTP {
    std::string method;
    std::string path;
    std::string version;
    std::string body;
    bool is_valid = false;
    std::string error;
    std::map<std::string, std::string> headers;
};

// Объявления всех функций (просто копируй заголовки)
StringVector split_by_spaces(const std::string& str);
bool is_valid_method(std::string& str);
std::string to_uppercase(std::string& str);
void parse_first_line(ParsedHTTP& result, const std::string& line);
StringVector split_by_crlf(const std::string& old_str);
StringVector split_by_spaces_for_headers(const std::string& str);
StringPair parse_header_line(std::string& line);
void parse_header(ParsedHTTP& result, const std::string& str);
StringVector divide_HTTP(const std::string& str);  // убрать static
ParsedHTTP parse(const std::string& raw_request);              // убрать static
json parser_body(const std::string& st);
#endif
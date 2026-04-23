#include "parser.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;


StringVector split_by_spaces(const std::string& str) {
    std::istringstream iss(str);
    StringVector output;
    std::string token;
    while (iss >> token) {
        output.push_back(token);
    }
    return output;
}

 bool is_valid_method(std::string& str) {
    StringVector method = { "GET","POST","PUT","DELETE","HEAD" };
    for (int i = 0; i < method.size(); i++) {
        if (str == method[i]) {
            return true;
        }
    }
    return false;
}

std::string to_uppercase(std::string& str) {
    for (auto& x : str) {
        x = toupper(x);
    }
    return str;
}

void parse_first_line(ParsedHTTP& result, const std::string& line) {
    auto vec = split_by_spaces(line);
    if (vec.empty()) {
        result.error = "Empty request line";
    }

    if (vec.size() < 3) {
        result.error = "Expected 3 parts, got " + std::to_string(vec.size());
    }

    result.method = to_uppercase(vec[0]);
    result.path = vec[1];
    result.version = vec[2];

    if (result.path[0] != '/') {
        result.error = "Path must start with '/' ";
    }

    if (!is_valid_method(result.method)) {
        result.error = "Invald method";
    }

    result.is_valid = true;
}

StringVector split_by_crlf(const std::string& old_str) {
    StringVector vec;
    auto str = old_str;
    auto simbl = "\r\n";
    int start = 0;
    int end = 0;
    if (str.find(simbl, 0) == 0) {
        str = str.substr(2, str.length() - 2);
    }
    while (str.find("\r\n", start) != std::string::npos) {
        end = str.find("\r\n", start);
        auto element = str.substr(start, end - start);
        vec.push_back(element);
        start = end + 2;
    }
    return vec;
}

StringVector split_by_spaces_for_headers(const std::string& str) {
    size_t pos = str.find(':');
    if (pos == std::string::npos) {
        throw std::logic_error("Invald HTTP where : ");
    }
    StringVector output;
    auto token_1 = str.substr(0, pos);
    for (auto& ch : token_1) {
        ch = tolower(ch);
    }
    auto str_copy = str.substr(pos + 1, str.length());
    auto i = str_copy.find_first_not_of(" \t\n\r\f\v");
    auto j = str_copy.find_last_not_of(" \t\n\r\f\v");

    std::string token_2;
    if (i == std::string::npos || j == std::string::npos) {
        token_2 = "";
    } else {
        token_2 = str_copy.substr(i, j - i + 1);
    }
    output.push_back(token_1);
    output.push_back(token_2);
    return output;
}

StringPair parse_header_line(std::string& line) {
    auto vec = split_by_spaces_for_headers(line);
    StringPair headers;
    
    if (vec.empty()) {
        throw std::logic_error("Empty request line");
    }

    if (vec.size() != 2) {
        throw std::logic_error("Expected 2 parts, got " + std::to_string(vec.size()));
    }
    headers = { vec[0], vec[1] };
    return headers;
}

void parse_header(ParsedHTTP& result, const std::string& str) {
    auto vec = split_by_crlf(str);
    for ( auto& line:vec) {
        result.headers.insert(parse_header_line(line));
    }
}

StringVector divide_HTTP(const std::string& str) {
    StringVector vec;
    auto pos = str.find("\r\n");
    auto token_1 = str.substr(0, pos);
    vec.push_back(token_1);
    auto pos_last = str.find("\r\n\r\n");

    auto token_2 = str.substr(pos, pos_last - pos + 1);
    vec.push_back(token_2);
    auto token_3 = str.substr(pos_last + 4, str.length() - pos + 1);
    vec.push_back(token_3);
    return vec;
}

ParsedHTTP parse(const std::string& raw_request) {
    ParsedHTTP result;
    auto vec = divide_HTTP(raw_request);
    parse_first_line(result, vec[0]);
    parse_header(result, vec[1]);
    result.body = vec[2];
    return result;
}



// парсер JSON 


/*
void backtick_delete(std::string& str){
    for(auto it = str.begin(); it!=str.end();){
        if(*it == '"') str.erase(it);
        else ++it;
    }
}

bool is_number(std::string& str){
    try{
    size_t pos = 0;
    int  num = std::stoi(str, &pos);
    return pos == str.size();
    }
    catch(...){
        return false;
    }
}


json parser_body(const std::string& st){
    std::string str = st;
    json data;
    backtick_delete(str);
    // Удаляем открывающую скобку если есть
    if (str.front() == '{') str = str.substr(1);
    if (str.back() == ';')str.pop_back();
    if (str.back() == '}')str.pop_back();
    
    int pos_d;
    int pos_s;
    while(( pos_d = str.find(':'))!=std::string::npos){
        pos_s = str.find(',');
        if(pos_s ==-1){
            pos_s = str.length();
        }
        std::string token_1 = str.substr(0, pos_d);
        std::string token_2 = str.substr(pos_d+1, pos_s-pos_d-1);
        if(is_number(token_2)){
            data[token_1] = std::stoi(token_2);
        }
        else{
            data[token_1] = token_2;
        }
        if (pos_s + 1 <= str.length()) {
            str = str.substr(pos_s + 1);
        } else {
            str = "";
            break;
        }
    }
    std:: cout << data.dump(4) << std::endl;
    return data;
}

*/

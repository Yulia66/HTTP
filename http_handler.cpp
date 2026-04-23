#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include "parser.h"
#include "models.h"
#include "http_handler.h"
#include "task_manager.hpp"
#include "json.hpp"

using json = nlohmann::json;


 TaskManager task(6);
std::string handle_http_request(const ParsedHTTP& request) {
    // ПОКА ТОЛЬКО ЭТО! Просто ответ на /
    if (request.method == "GET" && request.path == "/") {
        return "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/plain\r\n"
               "Content-Length: 12\r\n"
               "\r\n"
               "Hello World!";
    }


    //NMAP
    if(request.method == "POST" && request.path == "/tools/nmap"){

        json data = json::parse(request.body);
        if(!data.contains("target")){
            throw std::logic_error("Missing target field");
        }

        NmapUtil nmap;
        nmap.target = data["target"];

        if(data.contains("ports")){
            nmap.ports = data["ports"];
        }
        if(data.contains("port_range")){
            nmap.port_range = data["port_range"];
        }
        if(data.contains("script")){
            nmap.script = data["script"];
        }
        if(data.contains("subnet")){
            nmap.subnet = data["subnet"];
        }
        if(data.contains("protocol")){
            nmap.protocol = data["protocol"];
        }

 
        // Булевы поля (с проверкой типа)
        if(data.contains("service_version") && data["service_version"].is_boolean()) {
            nmap.service_version = data["service_version"];
        }
        
        if(data.contains("os_detection") && data["os_detection"].is_boolean()) {
            nmap.os_detection = data["os_detection"];
        }
        
        if(data.contains("silent") && data["silent"].is_boolean()) {
            nmap.silent = data["silent"];
        }
        std::vector<std::string> com = build_command(nmap);
        std::string task_id = std::to_string(task.submit_task(com));
       


       return "HTTP/1.1 202 Accepted\r\n"
               "Content-Type: application/json\r\n"
               "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
               "\r\n"
               "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }



    if(request.method == "POST" && request.path == "/tools/puredns"){
        json data = json::parse(request.body);

        if(!data.contains("target")){
            throw std::logic_error("Missing target field");
        }
        PurednsUtil puredns;
        puredns.target = data["target"];



         // Числовые поля (optional)
        if(data.contains("rate_limit") && data["rate_limit"].is_number()) {
            puredns.rate_limit = data["rate_limit"];
        }
        
        // Строковые поля (optional)
        if(data.contains("resolvers")) {
            puredns.resolvers = data["resolvers"];
        }
        
        if(data.contains("record_type")) {
            puredns.record_type = data["record_type"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            puredns.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            puredns.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            puredns.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            puredns.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(puredns);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";


    }

    // AMASS
    if(request.method == "POST" && request.path == "/tools/amass") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        AmassUtil amass;
        amass.target = data["target"];
        
        // Булевы поля (с проверкой типа)
        if(data.contains("passive") && data["passive"].is_boolean()) {
            amass.passive = data["passive"];
        }
        
        if(data.contains("active") && data["active"].is_boolean()) {
            amass.active = data["active"];
        }
        
        if(data.contains("brute") && data["brute"].is_boolean()) {
            amass.brute = data["brute"];
        }
        
        if(data.contains("recursive") && data["recursive"].is_boolean()) {
            amass.recursive = data["recursive"];
        }
        
        // Строковые поля (optional)
        if(data.contains("wordlist")) {
            amass.wordlist = data["wordlist"];
        }
        
        if(data.contains("sources")) {
            amass.sources = data["sources"];
        }
        
        if(data.contains("exclude")) {
            amass.exclude = data["exclude"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            amass.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            amass.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            amass.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            amass.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(amass);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }



        // DNSX
    if(request.method == "POST" && request.path == "/tools/dnsx") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        DnsxUtil dnsx;
        dnsx.target = data["target"];
        
        // Строковые поля (optional)
        if(data.contains("dns_query")) {
            dnsx.dns_query = data["dns_query"];
        }
        
        if(data.contains("dns_servers")) {
            dnsx.dns_servers = data["dns_servers"];
        }
        
        // Булевы поля (с проверкой типа)
        if(data.contains("resp_only") && data["resp_only"].is_boolean()) {
            dnsx.resp_only = data["resp_only"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            dnsx.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            dnsx.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            dnsx.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            dnsx.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(dnsx);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }



        // NAABU
    if(request.method == "POST" && request.path == "/tools/naabu") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        NaabuUtil naabu;
        naabu.target = data["target"];
        
        // Строковые поля (optional)
        if(data.contains("ports")) {
            naabu.ports = data["ports"];
        }
        
        if(data.contains("exclude_ports")) {
            naabu.exclude_ports = data["exclude_ports"];
        }
        
        if(data.contains("proxy")) {
            naabu.proxy = data["proxy"];
        }
        
        // Числовые поля (optional)
        if(data.contains("top_ports") && data["top_ports"].is_number()) {
            naabu.top_ports = data["top_ports"];
        }
        
        // Булевы поля (с проверкой типа)
        if(data.contains("service_version") && data["service_version"].is_boolean()) {
            naabu.service_version = data["service_version"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            naabu.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            naabu.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            naabu.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            naabu.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(naabu);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }






        // NUCLEI
    if(request.method == "POST" && request.path == "/tools/nuclei") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        NucleiUtil nuclei;
        nuclei.target = data["target"];
        
        // Строковые поля (optional)
        if(data.contains("templates")) {
            nuclei.templates = data["templates"];
        }
        
        if(data.contains("severity")) {
            nuclei.severity = data["severity"];
        }
        
        if(data.contains("tags")) {
            nuclei.tags = data["tags"];
        }
        
        if(data.contains("exclude_tags")) {
            nuclei.exclude_tags = data["exclude_tags"];
        }
        
        if(data.contains("headers")) {
            nuclei.headers = data["headers"];
        }
        
        // Булевы поля (с проверкой типа)
        if(data.contains("json_output") && data["json_output"].is_boolean()) {
            nuclei.json_output = data["json_output"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            nuclei.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            nuclei.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            nuclei.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            nuclei.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(nuclei);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }


        // HTTPX
    if(request.method == "POST" && request.path == "/tools/httpx") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        HttpxUtil httpx;
        httpx.target = data["target"];
        
        // Булевы поля
        if(data.contains("tech_detect") && data["tech_detect"].is_boolean()) {
            httpx.tech_detect = data["tech_detect"];
        }
        
        if(data.contains("status_code") && data["status_code"].is_boolean()) {
            httpx.status_code = data["status_code"];
        }
        
        if(data.contains("follow_redirects") && data["follow_redirects"].is_boolean()) {
            httpx.follow_redirects = data["follow_redirects"];
        }
        
        if(data.contains("https_only") && data["https_only"].is_boolean()) {
            httpx.https_only = data["https_only"];
        }
        
        // Строковые поля (optional)
        if(data.contains("match_string")) {
            httpx.match_string = data["match_string"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            httpx.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            httpx.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            httpx.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            httpx.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(httpx);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }





        // SUBFINDER
    if(request.method == "POST" && request.path == "/tools/subfinder") {
        
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        SubfinderUtil subfinder;
        subfinder.target = data["target"];
        
        // Булевы поля
        if(data.contains("active") && data["active"].is_boolean()) {
            subfinder.active = data["active"];
        }
        
        if(data.contains("recursive_search") && data["recursive_search"].is_boolean()) {
            subfinder.recursive_search = data["recursive_search"];
        }
        
        // Строковые поля (optional)
        if(data.contains("sources")) {
            subfinder.sources = data["sources"];
        }
        
        if(data.contains("exclude")) {
            subfinder.exclude = data["exclude"];
        }
        
        // Общие поля из BaseUtil
        if(data.contains("silent") && data["silent"].is_boolean()) {
            subfinder.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            subfinder.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            subfinder.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            subfinder.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(subfinder);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }

        // DNSGEN
    if(request.method == "POST" && request.path == "/tools/dnsgen") {
        json data = json::parse(request.body);
        
        if(!data.contains("target")) {
            throw std::logic_error("Missing target field");
        }
        
        DnsgenUtil dnsgen;
        dnsgen.target = data["target"];
        
        // Строковые поля
        if(data.contains("wordlist_file")) {
            dnsgen.wordlist_file = data["wordlist_file"];
        }
        
        if(data.contains("output_format")) {
            dnsgen.output_format = data["output_format"];
        }
        
        // Общие поля
        if(data.contains("silent") && data["silent"].is_boolean()) {
            dnsgen.silent = data["silent"];
        }
        
        if(data.contains("timeout") && data["timeout"].is_number()) {
            dnsgen.timeout = data["timeout"];
        }
        
        if(data.contains("threads") && data["threads"].is_number()) {
            dnsgen.threads = data["threads"];
        }
        
        if(data.contains("output_file")) {
            dnsgen.output_file = data["output_file"];
        }
        
        std::vector<std::string> com = build_command(dnsgen);
        std::string task_id = std::to_string(task.submit_task(com));
        
        return "HTTP/1.1 202 Accepted\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(27 + task_id.length()) + "\r\n"
            "\r\n"
            "{\"task_id\":\"" + task_id + "\",\"status\":\"pending\"}";
    }


    if (request.method == "GET" && request.path.find("/tools/") == 0) {
        std::string s = request.path.substr(7);
        if(s.empty()){
            return "HTTP/1.1 400 Bad Request\r\n"
                "Content-Length: 0\r\n\r\n";
        }
        
        int id = std::stoi(s);
        json response = {
            {"status", task.get_status(id)},
            {"result", task.get_result(id)}
        };
        std::string body = response.dump();
        
        return "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "\r\n" + body;
    }
    
    
    // Все остальное - 404
    return "HTTP/1.1 404 Not Found\r\n"
           "Content-Length: 0\r\n\r\n";
}

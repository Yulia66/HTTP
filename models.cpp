
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include "models.h"
std::vector<std::string> build_command(const BaseUtil& util){
    std::vector <std::string> command;

    command.push_back(util.get_tool());
    if(util.silent){
        command.push_back("-silent");
    }

    if(util.threads.has_value()) {
        command.push_back("-t");
        command.push_back(std::to_string(util.threads.value()));
    }

    if(util.output_file.has_value()) {
        command.push_back("-o");
        command.push_back(util.output_file.value());
    }
    

    if(util.get_tool()=="nmap"){ // NMAP
        const NmapUtil* nmap = dynamic_cast<const NmapUtil*>(&util);
        if(nmap->ports.has_value()){
            command.push_back("-p");
            command.push_back(nmap->ports.value());
        }
        if(nmap->port_range.has_value()){
            command.push_back("-p-");
        }
        if(nmap->service_version){
            command.push_back("-sV");
        }
        if(nmap->os_detection){
            command.push_back("-O");
        }
        if(nmap->script.has_value()){
            command.push_back("--script");
            command.push_back(nmap->script.value());
        }
        if(nmap->subnet.has_value()){
            command.push_back("-sn");
            command.push_back(nmap->subnet.value());
        }
        if(nmap->protocol=="tcp"){
            command.push_back("-sT");
        }
        else if (nmap->protocol=="udp")
        {
            command.push_back("-sU");
        }
        if(nmap->timeout){
            command.push_back("--host-timeout");
            command.push_back(std::to_string(nmap->timeout));
        }



        command.push_back(nmap->target);
        return command;
    }

    




     if(util.get_tool()=="amass"){ // AMASS
        const AmassUtil* amass = dynamic_cast<const AmassUtil*>(&util);
        command.push_back("enum");
        command.push_back("-d");
        command.push_back(amass->target);
        if(amass->passive){
            command.push_back("-passive");
        }
        if(amass->active){
            command.push_back("-active");
        }
        if(amass->brute && amass->wordlist){
            command.push_back("-brute");
            command.push_back("-w");
            command.push_back(amass->wordlist.value());
        }
        if(amass->sources){
            command.push_back("-src");
            command.push_back(amass->sources.value());
        }
        if(amass->recursive){
            command.push_back("-rf");
        }
        if(amass->exclude){
            command.push_back("-exclude");
            command.push_back(amass->exclude.value());
        }
        return command;
     }



    if(util.get_tool() == "subfinder") {
    const SubfinderUtil* sub = dynamic_cast<const SubfinderUtil*>(&util);
    
    if(sub->sources.has_value()) {
        command.push_back("-s");
        command.push_back(sub->sources.value());
    }
    
    if(sub->active) {
        command.push_back("-active");
    }
    
    if(sub->recursive_search) {
        command.push_back("-recursive");
    }
    
    if(sub->exclude.has_value()) {
        command.push_back("-e");
        command.push_back(sub->exclude.value());
    }
    
    if(util.timeout != 300) {
        command.push_back("-timeout");
        command.push_back(std::to_string(util.timeout));
    }


    command.push_back(sub->target);
    return command;
}


if(util.get_tool() == "naabu") {
    const NaabuUtil* naabu = dynamic_cast<const NaabuUtil*>(&util);
    
    if(naabu->ports.has_value()) {
        command.push_back("-p");
        command.push_back(naabu->ports.value());
    }
    
    if(naabu->top_ports.has_value()) {
        command.push_back("-top-ports");
        command.push_back(std::to_string(naabu->top_ports.value()));
    }
    
    if(naabu->service_version) {
        command.push_back("-sV");
    }
    
    if(naabu->exclude_ports.has_value()) {
        command.push_back("-exclude-ports");
        command.push_back(naabu->exclude_ports.value());
    }
    
    if(naabu->proxy.has_value()) {
        command.push_back("-proxy");
        command.push_back(naabu->proxy.value());
    }
    
    if(util.timeout != 300) {
        command.push_back("-timeout");
        command.push_back(std::to_string(util.timeout));
    }

    command.push_back(naabu->target);
    return command;
}



if(util.get_tool() == "httpx") {
    const HttpxUtil* httpx = dynamic_cast<const HttpxUtil*>(&util);
    
    if(httpx->tech_detect) {
        command.push_back("-tech-detect");
    }
    
    if(httpx->status_code) {
        command.push_back("-status-code");
    }
    
    if(httpx->follow_redirects) {
        command.push_back("-follow-redirects");
    }
    
    if(httpx->match_string.has_value()) {
        command.push_back("-match-string");
        command.push_back(httpx->match_string.value());
    }
    
    if(httpx->https_only) {
        command.push_back("-https-only");
    }
    
    if(util.timeout != 300) {
        command.push_back("-timeout");
        command.push_back(std::to_string(util.timeout));
    }
    command.push_back(httpx->target);
    return command;
}

if(util.get_tool() == "nuclei") {
    const NucleiUtil* nuclei = dynamic_cast<const NucleiUtil*>(&util);
    
    if(nuclei->templates.has_value()) {
        command.push_back("-t");
        command.push_back(nuclei->templates.value());
    }
    
    if(nuclei->severity.has_value()) {
        command.push_back("-severity");
        command.push_back(nuclei->severity.value());
    }
    
    if(nuclei->tags.has_value()) {
        command.push_back("-tags");
        command.push_back(nuclei->tags.value());
    }
    
    if(nuclei->exclude_tags.has_value()) {
        command.push_back("-etags");
        command.push_back(nuclei->exclude_tags.value());
    }
    
    if(nuclei->json_output) {
        command.push_back("-j");
    }
    
    if(nuclei->headers.has_value()) {
        command.push_back("-H");
        command.push_back(nuclei->headers.value());
    }
    
    if(util.timeout != 300) {
        command.push_back("-timeout");
        command.push_back(std::to_string(util.timeout));
    }

    command.push_back(nuclei->target);
    return command;
}



if(util.get_tool() == "dnsx") {
    const DnsxUtil* dnsx = dynamic_cast<const DnsxUtil*>(&util);
    
    if(dnsx->dns_query.has_value()) {
        command.push_back("-query");
        command.push_back(dnsx->dns_query.value());
    }
    
    if(dnsx->dns_servers.has_value()) {
        command.push_back("-r");
        command.push_back(dnsx->dns_servers.value());
    }
    
    if(dnsx->resp_only) {
        command.push_back("-resp");
    }
    
    if(util.timeout != 300) {
        command.push_back("-timeout");
        command.push_back(std::to_string(util.timeout));
    }

    command.push_back(dnsx->target);
    return command;
}


if(util.get_tool() == "puredns") {
    const PurednsUtil* puredns = dynamic_cast<const PurednsUtil*>(&util);
    
    command.push_back("resolve");
    
    if(puredns->rate_limit.has_value()) {
        command.push_back("-r");
        command.push_back(std::to_string(puredns->rate_limit.value()));
    }
    
    if(puredns->record_type.has_value()) {
        if(puredns->record_type.value() == "A") {
            command.push_back("-a");
        } else if(puredns->record_type.value() == "CNAME") {
            command.push_back("-c");
        }
    }
    
    if(puredns->resolvers.has_value()) {
        command.push_back("-resolvers");
        command.push_back(puredns->resolvers.value());
    }

    command.push_back(puredns->target);
    return command;
}



if(util.get_tool() == "dnsgen") {
    const DnsgenUtil* dnsgen = dynamic_cast<const DnsgenUtil*>(&util);
    
    if(dnsgen->wordlist_file.has_value()) {
        command.push_back("-w");
        command.push_back(dnsgen->wordlist_file.value());
    }
    
    if(dnsgen->output_format.has_value()) {
        command.push_back("-f");
        command.push_back(dnsgen->output_format.value());
    }

    command.push_back(dnsgen->target);
    return command;
}

}


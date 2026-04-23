
#include <string>
#include <vector>
#include <optional>
#include <iostream>

struct BaseUtil {
    virtual std::string get_tool() const {
        return "unknown";
    }
    
    std::string target;           // обязательное поле
    int timeout = 300;            // дефолтное значение
    bool silent = false;          // общий флаг для всех
    std::optional<int> threads;   // опциональное поле
    std::optional<std::string> output_file;
    
    virtual ~BaseUtil() = default;
};

struct NmapUtil : BaseUtil {
    std::string get_tool() const override {
        return "nmap";
    }
    std::optional<std::string> ports;
    std::optional<std::string> port_range;  // "-p-" для всех портов
    bool service_version = false;
    bool os_detection = false;
    std::optional<std::string> script;
    std::optional<std::string> subnet;
    std::string protocol;
};



struct AmassUtil : BaseUtil{
    std::string get_tool() const override {
        return "amass";
    }
    bool passive = false;
    bool active = false;
    bool brute = false;
    std::optional<std::string> wordlist;
    std::optional<std::string> sources;   // Optional[str]
    bool recursive = false;         // Optional[bool] → bool с false
    std::optional<std::string> exclude; 
};


struct PurednsUtil : BaseUtil{
    std::string get_tool() const override {
        return "puredns";
    }
    std::optional<int> rate_limit;
    std::optional<std::string> resolvers;   
    std::optional<std::string> record_type;
};

struct DnsxUtil : BaseUtil{
    std::string get_tool() const override {
        return "dnsx";
    } 
    std::optional<std::string> dns_query;
    std::optional<std::string> dns_servers;
    bool resp_only = false;

};



struct NaabuUtil : BaseUtil {
    std::string get_tool() const override {
        return "naabu";
    }
    
    std::optional<std::string> ports;          // Optional[str]
    std::optional<int> top_ports;              // Optional[int]
    bool service_version = false;               // Optional[bool] → bool
    std::optional<std::string> exclude_ports;  // Optional[str]
    std::optional<std::string> proxy;          // Optional[str]
};



struct NucleiUtil : BaseUtil {
    std::string get_tool() const override {
        return "nuclei";
    }
    
    std::optional<std::string> templates;      // Optional[str]
    std::optional<std::string> severity;       // Optional[str]
    std::optional<std::string> tags;           // Optional[str]
    std::optional<std::string> exclude_tags;   // Optional[str]
    bool json_output = false;                   // Optional[bool] → bool
    std::optional<std::string> headers;        // Optional[str]
};




struct HttpxUtil : BaseUtil {
    std::string get_tool() const override {
        return "httpx";
    }
    
    bool tech_detect = false;            // Optional[bool] → bool
    bool status_code = false;            // Optional[bool] → bool
    bool follow_redirects = false;       // Optional[bool] → bool
    std::optional<std::string> match_string; // Optional[str]
    bool https_only = false;             // Optional[bool] → bool
};



struct SubfinderUtil : BaseUtil {
    std::string get_tool() const override {
        return "subfinder";
    }
    
    std::optional<std::string> sources;      // Optional[str]
    bool active = false;                      // Optional[bool] → bool
    bool recursive_search = false;            // Optional[bool] → bool
    std::optional<std::string> exclude;       // Optional[str]
};




struct DnsgenUtil : BaseUtil {
    std::string get_tool() const override {
        return "dnsgen";
    }
    
    std::optional<std::string> wordlist_file;  // Optional[str]
    std::optional<std::string> output_format;  // Optional[str]
};





std::vector<std::string> build_command(const BaseUtil& util);
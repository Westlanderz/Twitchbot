#include "../includes/paramparser.hpp"
#include <cstring>
#include <iostream>
#include <sstream>

ParamParser::ParamParser() {
    params.push_back("sender");
    params.push_back("user");
    params.push_back("count");
}

std::string ParamParser::parse_command(std::string result, std::string sender) { //result -> sdsddsf sdasdsdf ${asasd} asdsad ${sdasasdas}
    std::string new_result{""};
    std::vector<std::string> parameters;
    char delimiter{' '};
    std::size_t find_param_result{0}, find_param_end{0};
    std::string token{""};
    std::stringstream results{result};
    while(getline(results, token, delimiter)) {
        find_param_result = token.find("${");
        find_param_end = token.find("}");
        if(find_param_result != std::string::npos && find_param_end != std::string::npos) {
            std::string param_to_find = token.substr(find_param_result + 2, find_param_end - find_param_result - 2);
            if(check_good_param(param_to_find))
                parameters.push_back(param_to_find);
        }
    }
    
    for(auto &param : parameters) {
        std::cout << param << std::endl;
    }
    return "Hello there " + sender;
}

bool ParamParser::check_good_param(std::string param) {
    for(auto &_param : params) {
        if(!strcmp(_param.c_str(), param.c_str()))
            return true;
    }
    return false;
}

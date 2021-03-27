#ifndef _paramparser_h
#define _paramparser_h

#include <vector>
#include <string>

class ParamParser {
    public:
        ParamParser();
        virtual ~ParamParser() = default;

        std::string parse_command(std::string, std::string);
        bool check_good_param(std::string);

    private:
        std::vector<std::string> params;
};

#endif //_paramparser_h


/**
 *  ${sender} -> the sender of the message
 *  ${user} -> the user of the command
 *  ${count} -> the amount of times the command was run since it was added to the channel
 */
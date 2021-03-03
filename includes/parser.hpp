#ifndef _parser_h
#define _parser_h

#include "bot.hpp"
#include "../includes/commandhandler.hpp"

class Parser {
    public:
        Parser(Bot *);
        virtual ~Parser();

        bool is_command();
        bool is_ping_message();
        void parse_server_message(std::string, std::string);
        std::string is_sender();
        std::string server_command();

    private:
        std::string sender;
        bool mod;
        bool sub;
        std::string message;
        std::string command;
        Bot *bot;
        CommandHandler *ch;
};

#endif //_parser_h

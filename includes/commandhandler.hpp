#ifndef _chandler_h
#define _chandler_h

#include <vector>
#include <string>

class Bot;
class Command;

class CommandHandler {
    public:
        CommandHandler(Bot *, std::string);
        virtual ~CommandHandler();

        void init_command_list();
        void search_command(std::string, bool, bool, std::string, std::string, std::string);

    private:
        std::vector<Command *> available_commands;
        std::vector<std::string> added_commands;
        Bot *bot;
        std::string file_location;
};

#endif //_chandler_h

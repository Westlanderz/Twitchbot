#ifndef help_h
#define help_h

#include "../command.hpp"
#include <string>
#include <vector>

class CommandHandler;

class HelpCommand : public Command {
    public:
        HelpCommand(std::vector<Command *>, std::vector<std::string>, CommandHandler *);

        void execute(std::string, std::string, bool, bool, std::string) override;
        bool has_perms_to_run(bool, bool, std::string) override;
        bool find_name(std::string) override;
        std::string list_command() override;
        std::string generate_help_message(const std::string &) override;
        void add_new_command(std::string, std::string);
        void remove_command(std::string, std::string);

    private:
        std::vector<std::string> names;
        std::vector<Command *> commands;
        std::vector<std::string> added_commands;
        CommandHandler *handler;
};

#endif //help_h

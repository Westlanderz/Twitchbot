#ifndef addtimer_h
#define addtimer_h

#include "../command.hpp"
#include <string>
#include <vector>

class CommandHandler;

class AddTimerCommand : public Command {
    public:
        AddTimerCommand(CommandHandler *);

        void execute(std::string, std::string, bool, bool, std::string) override;
        bool has_perms_to_run(bool, bool, std::string) override;
        bool find_name(std::string) override;
        std::string list_command() override;
        std::string generate_help_message(const std::string &) override;

    private:
        std::vector<std::string> names;
        CommandHandler *handler;
};

#endif //addtimer_h

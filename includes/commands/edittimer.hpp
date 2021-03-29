#ifndef edittimer_h
#define edittimer_h

#include "../command.hpp"

class EditTimerCommand : public Command {
    public:
        EditTimerCommand(Bot *);

        void execute(std::string, std::string, bool, bool, std::string) override;
        bool has_perms_to_run(bool, bool, std::string) override;
        bool find_name(std::string) override;
        std::string list_command() override;
        std::string generate_help_message(const std::string &) override;

    private:
        std::vector<std::string> names;
        Bot *bot;
};

#endif //edittimer_h
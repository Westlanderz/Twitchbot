// ! This function is depricated from now on

#ifndef editresult_h
#define editresult_h

#include "../command.hpp"

class EditresultCommand : public Command {
    public:
        EditresultCommand(std::vector<Command *>, Bot *);

        void execute(std::string, std::string, bool, bool, std::string) override;
        bool has_perms_to_run(bool, bool, std::string) override;
        bool find_name(std::string) override;
        std::string list_command() override;
        std::string generate_help_message(const std::string &) override;

    private:
        std::vector<std::string> names;
        std::vector<Command *> commands;
        Bot *bot;
};

#endif //editresult_h

#include "../../includes/commands/helpcommand.hpp"

HelpCommand::HelpCommand(std::vector<Command *> _commands, Bot *_bot) : Command(), commands{_commands}, bot{_bot} {
    names.push_back("commands");
    names.push_back("help");
}

void HelpCommand::execute(std::string sender, std::string original_msg, bool mod, bool sub, std::string channel) {
    std::vector<Command *> allowed_commands;
    for(auto &command : commands) {
        if(command->has_perms_to_run(mod, sub, sender))
            allowed_commands.push_back(command);
    }
    std::size_t find_args = original_msg.find(" ");
    std::size_t find_command = original_msg.find(" ", find_args + 1);
    std::string command_name = "";
    if(find_args != std::string::npos) {
        if(find_command != std::string::npos) {
            command_name = original_msg.substr(find_args + 1, find_command - find_args);
        } else {
            command_name = original_msg.substr(find_args + 1);
        }
        bool found{false};
        for(auto &command : allowed_commands) {;
            if(!strcmp(command->list_command().c_str(), command_name.c_str())) {
                bot->send_chat_message(command->generate_help_message(channel), channel);
                found = true;
                break;
            }
        }
        if(!found) {
            bot->send_chat_message("Could not find the command you were looking for.", channel);
        }
    } else {
        std::string help_msg = "here is a list of commands you can run: ";
        for(auto &command : allowed_commands) {
            help_msg.append(command->list_command());
            if(!strcmp(allowed_commands.at(allowed_commands.size() - 1)->list_command().c_str(), command->list_command().c_str())) {
                help_msg.append(". ");
            } else {
                help_msg.append(", ");
            }
        }
        help_msg.append("Try " + bot->is_prefix(channel) +  "help " + names[0] + " to learn more about one of them. Version: 1.3.0-dev https://github.com/Westlanderz/TwitchBot");
        bot->send_chat_message(help_msg, channel);
    }
}

bool HelpCommand::has_perms_to_run(bool, bool, std::string) {
    return true;
}

bool HelpCommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string HelpCommand::list_command() {
    return names[0];
}

std::string HelpCommand::generate_help_message(const std::string &) {
    return "I think you know how to use this command.....";
}

void HelpCommand::new_output(std::string) {}
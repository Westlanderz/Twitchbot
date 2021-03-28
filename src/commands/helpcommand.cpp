#include "../../includes/commands/helpcommand.hpp"

HelpCommand::HelpCommand(std::vector<Command *> _commands, std::vector<std::string> __commands, Bot *_bot) : commands{_commands}, added_commands{__commands}, bot{_bot} {
    names.push_back("commands");
    names.push_back("help");
}

void HelpCommand::execute(std::string sender, std::string original_msg, bool mod, bool sub, std::string channel) {
    std::vector<Command *> allowed_commands;
    std::vector<std::string> allowed_command;
    for(auto &command : commands) {
        if(command->has_perms_to_run(mod, sub, sender))
            allowed_commands.push_back(command);
    }
    for(auto &command : added_commands) {
        if(!strcmp(command.substr(command.find("Rights:") + 7, 3).c_str(), "all") || (!strcmp(command.substr(command.find("Rights:") + 7, 3).c_str(), "sub") && sub) || (!strcmp(command.substr(command.find("Rights:") + 7, 3).c_str(), "mod") && mod) || bot->is_channel(sender) || bot->is_owner(sender))
            allowed_command.push_back(command);
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
        for(auto &command : allowed_commands) {
            if(!strcmp(command->list_command().c_str(), command_name.c_str())) {
                bot->send_chat_message(command->generate_help_message(channel), channel);
                found = true;
                break;
            }
        }
        for(auto &command : allowed_command) {
            std::size_t name_start = command.find("Name:");
            std::string name = command.substr(name_start + 5, command.find("Rights:", name_start) - name_start - 7);
            if(!strcmp(name.c_str(), command_name.c_str())) {
                std::size_t help_start = command.find("Help:");
                std::string help_msg = "Use " + bot->is_prefix(channel);
                help_msg.append(name);
                help_msg.append(" ");
                help_msg.append(command.substr(help_start + 5, command.find("Result:", help_start) - help_start - 7));
                bot->send_chat_message(help_msg, channel);
                found = true;
                break;
            }
        }
        if(!found) {
            bot->send_chat_message("Could not find the command you were looking for.", channel);
        }
    } else {
        std::string help_msg = "Here is a list of commands you can run: ";
        for(auto &command : allowed_commands) {
            help_msg.append(command->list_command());
            if(!strcmp(allowed_commands.at(allowed_commands.size() - 1)->list_command().c_str(), command->list_command().c_str()) && allowed_command.size() == 0) {
                help_msg.append(". ");
            } else {
                help_msg.append(", ");
            }
        }
        for(auto &command : allowed_command) {
            std::size_t name_starts = command.find("Name:");
            std::string named = command.substr(name_starts + 5, command.find("Rights:", name_starts) - name_starts - 7);
            help_msg.append(named);
            std::size_t named_start = allowed_command.at(allowed_command.size() - 1).find("Name:");
            if(!strcmp(allowed_command.at(allowed_command.size() - 1).substr(named_start + 5, command.find("Rights:", named_start) - named_start - 7).c_str(), named.c_str())) {
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

void HelpCommand::add_new_command(std::string command, std::string channel) {
    added_commands.push_back(command);
    bot->send_chat_message("Added the command to the list of commands", channel);
}

void HelpCommand::remove_command(std::string command, std::string channel) {
    std::vector<std::string>::iterator rm = added_commands.end();
    for(auto it = added_commands.begin(); it != added_commands.end(); it++) {
        if(!strcmp(it->data(), command.c_str()))
            rm = it;
    }
    if(rm != added_commands.end())
        added_commands.erase(rm);
    else
        bot->send_chat_message("Cant remove this command", channel);
}

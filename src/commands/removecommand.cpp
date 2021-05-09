#include "../../includes/commands/removecommand.hpp"
#include "../../includes/commandhandler.hpp"
#include "../../includes/bot.hpp"
#include <fstream>

RemovecommandCommand::RemovecommandCommand(CommandHandler *_handler) : handler{_handler} {
    names.push_back("removecommand");
    names.push_back("rmcommand");
    names.push_back("removecmd");
    names.push_back("rmcmd");
}

void RemovecommandCommand::execute(std::string, std::string original_msg, bool, bool, std::string channel) {
    std::string file = handler->uses_bot()->is_command_file(channel);
    std::fstream commands;
    std::string tmp_result{""};
    std::vector<std::string> commands_string;
    commands.open(file, std::fstream::in);
    if(!commands) {
        std::cout << "No commands file for this channel" << std::endl;
    } else {
        std::string command{""}, line{""};
        while(std::getline(commands, line)) {
            if(line.empty()) {
                commands_string.push_back(command);
                command.clear();
            } else {
                command.append(line);
            }
        }
        commands.close();
        std::size_t find_command = original_msg.find(" ");
        if(find_command != std::string::npos) {
            std::string timer_to_edit = original_msg.substr(find_command + 1);
            std::vector<std::string>::iterator rmcommand;
            for(auto it = commands_string.begin(); it != commands_string.end(); ++it) {
                std::string _command = it->data();
                std::size_t find_name = _command.find(":");
                std::size_t end_name = _command.find(" ");
                if(find_name != std::string::npos) {
                    std::string command_name = _command.substr(find_name + 1, end_name - find_name - 1);
                    if(!strcmp(timer_to_edit.c_str(), command_name.c_str())) {
                        handler->uses_bot()->send_chat_message("Removed the timer with name " + command_name, channel);
                        handler->uses_bot()->is_commandhandler(channel)->remove_command(_command, channel);
                        rmcommand = it;
                    }
                }
            }
            commands_string.erase(rmcommand);
        }
    }
    std::fstream output;
    output.open(file, std::fstream::out);
    if(!output) {
        std::cerr << "No file excists" << std::endl;
    } else {
        for(auto &_command : commands_string) {
            _command.append("\n\n");
            output << _command;
        }   
    }
    output.close();
}

bool RemovecommandCommand::has_perms_to_run(bool mod, bool, std::string sender) {
    if(mod || handler->uses_bot()->is_channel(sender) || handler->uses_bot()->is_owner(sender))
        return true;
    return false;
}

bool RemovecommandCommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string RemovecommandCommand::list_command() {
    return names[0];
}

std::string RemovecommandCommand::generate_help_message(const std::string &channel) {
    return "Use " + handler->uses_bot()->is_prefix(channel) + names[0] + " [name] to remove a custom command from this channel.";
}


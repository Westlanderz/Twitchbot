#include "../../includes/commands/listcommands.hpp"
#include <fstream>

ListcommandsCommand::ListcommandsCommand(Bot *_bot) : bot{_bot} {
    names.push_back("listcommands");
    names.push_back("listcmd");
    names.push_back("listcommand");
}

void ListcommandsCommand::execute(std::string sender, std::string original_msg, bool mod, bool sub, std::string channel) {
    std::string file = bot->is_command_file(channel);
    std::fstream commands;
    std::vector<std::string> command_list, output_list;
    commands.open(file, std::ios::in);
    if(!commands) {
        std::cerr << "Can not find the file for commands " + file << std::endl;
    } else {
        std::string command;
        std::string line;
        while(std::getline(commands, line)) {
            if(line.empty()) {
                command_list.push_back(command);
                command.clear();
            } else {
                command.append(line);
            }
        }
        commands.close();
        for(auto it = command_list.begin(); it != command_list.end(); ++it) {
            std::string _command = it->data();
            std::size_t find_name = _command.find(":");
            std::size_t end_name = _command.find(" ");
            if(find_name != std::string::npos) {
                std::string command_name = _command.substr(find_name + 1, end_name - find_name - 1);
                output_list.push_back(command_name);
            }
        }
        std::string help_msg = "Here you can find the current active commands: ";
        for(auto &command_to_list : output_list) {
            help_msg.append(command_to_list);
            if(!strcmp(output_list.at(output_list.size() - 1).c_str(), command_to_list.c_str())) {
                help_msg.append(".");
            } else {
                help_msg.append(", ");
            }
        }
        bot->send_chat_message(help_msg, channel);
    }
}

bool ListcommandsCommand::has_perms_to_run(bool mod, bool, std::string sender) {
    if(mod || bot->is_channel(sender) || bot->is_owner(sender))
        return true;
    return false;
}

bool ListcommandsCommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string ListcommandsCommand::list_command() {
    return names[0];
}

std::string ListcommandsCommand::generate_help_message(const std::string &channel) {
    return "Use " + bot->is_prefix(channel) + names[0] + " to list all the added commands of this channel.";
}

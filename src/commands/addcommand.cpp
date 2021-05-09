#include "../../includes/commands/addcommand.hpp"
#include <fstream>
#include "../../includes/commandhandler.hpp"
#include "../../includes/bot.hpp"

Addcommand::Addcommand(CommandHandler *_handler) : handler{_handler} {
    names.push_back("addcommand");
    names.push_back("add-command");
    names.push_back("addcmd");
}

void Addcommand::execute(std::string, std::string original_msg, bool, bool, std::string channel) {
    std::string file = handler->uses_bot()->is_command_file(channel);
    std::fstream command_file;
    std::string new_command{""};
    command_file.open(file, std::ios::app);
    if(!command_file) {
        std::cerr << "No such file excists" << std::endl;
    } else {
        std::string name{"Name:"}, rights{" Rights:"}, help{" Help:"}, message{" Result:"};
        std::size_t find_name, find_rights, find_help, find_message;
        find_name = original_msg.find(" ");
        if(find_name != std::string::npos) {
            find_rights = original_msg.find(" ", find_name + 1);
            if(find_rights != std::string::npos) {
                find_help = original_msg.find("h:", find_rights + 1);
                if(find_help != std::string::npos) {
                    find_message = original_msg.find("m:", find_help + 1);
                    if(find_message != std::string::npos) {
                        message.append(original_msg.substr(find_message + 2));
                        help.append(original_msg.substr(find_help + 2, find_message - find_help - 2));
                        rights.append(original_msg.substr(find_rights + 1, find_help - find_rights - 2));
                        name.append(original_msg.substr(find_name + 1, find_rights - find_name - 1));
                        new_command = name.append(rights).append(" Count:0").append(help).append(message).append("\n\n");
                        command_file << new_command;
                        command_file.close();
                        handler->uses_bot()->is_commandhandler(channel)->add_command(new_command, channel);
                        handler->uses_bot()->send_chat_message("Added the command to the listed commands", channel);
                        return;
                    }
                }      
            }
        }
    }
    handler->uses_bot()->send_chat_message("Please provide all the arguments to the command adder. For more info use !help addcommand", channel);
}

bool Addcommand::has_perms_to_run(bool mod, bool, std::string sender) {
    if(mod || handler->uses_bot()->is_channel(sender) || handler->uses_bot()->is_owner(sender))
        return true;
    return false;
}

bool Addcommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string Addcommand::list_command() {
    return names[0];
}

std::string Addcommand::generate_help_message(const std::string &channel) {
    return "Use " + handler->uses_bot()->is_prefix(channel) + names[0] + " [name] [rights {all | sub | mod}] [helpmessage <h:>] [message <m:>] to add a new command to this channel.";
}
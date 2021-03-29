#include "../includes/commandhandler.hpp"
#include <fstream>
#include "../includes/bot.hpp"
#include "../includes/command.hpp"
#include "../includes/commands/changeprefix.hpp"
#include "../includes/commands/lurkcommand.hpp"
#include "../includes/commands/helpcommand.hpp"
#include "../includes/commands/editresult.hpp"
#include "../includes/commands/addtimer.hpp"
#include "../includes/commands/edittimer.hpp"
#include "../includes/commands/removetimer.hpp"
#include "../includes/commands/listtimerscommand.hpp"
#include "../includes/commands/listcommands.hpp"

/**
 * @brief Construct a new Command Handler:: Command Handler object
 * 
 * @param _bot a bot instance to be able to send chat messages
 */
CommandHandler::CommandHandler(Bot *_bot, std::string channel) : bot{_bot}, file_location{"../files/commands/" + channel + "_commands.txt"} {
    init_command_list();
}

/**
 * @brief Destroy the Command Handler:: Command Handler object
 * 
 */
CommandHandler::~CommandHandler() {
    for(auto it = available_commands.begin(); it != available_commands.end(); it++)
        available_commands.erase(it);
}

/**
 * @brief Initialise all of the commands for a channel
 * 
 */
void CommandHandler::init_command_list() {
    //TODO: add timeout and ban commands for mod only
    //TODO: addcommands to file, edit commands and removecommands (List manually added commands)
    std::fstream commandfile;
    commandfile.open(file_location, std::ios::app);
    commandfile.close();
    commandfile.open(file_location, std::ios::in);
    if(!commandfile) {
        std::cerr << "Can not find the file " << file_location << " you are trying to open." << std::endl;
    } else {
        std::string command;
        std::string line;
        while(std::getline(commandfile, line)) {
            if(line.empty()) {
                added_commands.push_back(command);
                command.clear();
            } else {
                command.append(line);
            }
        }
        commandfile.close();
    }
    available_commands.push_back(new ChangePrefixCommand(bot));
    available_commands.push_back(new LurkCommand(bot));
    available_commands.push_back(new AddTimerCommand(bot));
    available_commands.push_back(new EditTimerCommand(bot));
    available_commands.push_back(new RemoveTimerCommand(bot));
    available_commands.push_back(new ListtimerCommand(bot));
    available_commands.push_back(new ListcommandsCommand(bot));
    available_commands.push_back(new HelpCommand(available_commands, added_commands, bot));
}

/**
 * @brief This checks if the given command is a known command and if the user has enough perms to run the command
 * 
 * @param command the command that its searching for
 * @param mod if the user is mod in the channel
 * @param sub if the user is a sub in the channel
 * @param sender the username of the sender of the message
 * @param original_message the full message send by the user
 * @param channel the channel the message was send in
 */
void CommandHandler::search_command(std::string command, bool mod, bool sub, std::string sender, std::string original_message, std::string channel) {
    for(auto &_command : available_commands) {
        if(_command->find_name(command)) {
            if(_command->has_perms_to_run(mod, sub, sender))
                _command->execute(sender, original_message, mod, sub, channel);
            else
                bot->send_chat_message(sender + " you dont have the permissions to run this command.", channel);
            return;
        }
    }
    for(auto &_command : added_commands) {
        std::size_t names_start = _command.find("Name:");
        std::size_t rights_start = _command.find("Rights:");
        std::string command_to_find = _command.substr(names_start + 5, rights_start - names_start - 7);
        if(!strcmp(command.c_str(), command_to_find.c_str())) {
            std::string msg = _command.substr(_command.find("Result:") + 7);
            bot->send_chat_message(msg, channel);
            return;
        }
    }
    bot->send_chat_message(sender + " I do not recognise this command. Try !help to see a list of the commands.", channel);
}

/**
 * @brief Add a command to the custom command list
 * 
 * @param command the command in full format to add
 * @param channel the channel to send the response to
 */
void CommandHandler::add_command(std::string command, std::string channel) {
    added_commands.push_back(command);
    dynamic_cast<HelpCommand *>(available_commands.at(available_commands.size() - 1))->add_new_command(command, channel);
}

/**
 * @brief Remove a command to the custom command list
 * 
 * @param command the command in full format to remove
 * @param channel the channel to send the response to
 */
void CommandHandler::remove_command(std::string command, std::string channel) {
    std::vector<std::string>::iterator rm = added_commands.end();
    for(auto it = added_commands.begin(); it != added_commands.end(); it++) {
        if(!strcmp(it->data(), command.c_str()))
            rm = it;
    }
    if(rm != added_commands.end()) {
        added_commands.erase(rm);
        dynamic_cast<HelpCommand *>(available_commands.at(available_commands.size() - 1))->remove_command(command, channel);
    } else
        bot->send_chat_message("Cant remove this command", channel);
}

std::string CommandHandler::is_command_file() {
    return file_location;
}

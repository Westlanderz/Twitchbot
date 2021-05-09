#include "../../includes/commands/lurkcommand.hpp"
#include "../../includes/commandhandler.hpp"
#include "../../includes/bot.hpp"

LurkCommand::LurkCommand(CommandHandler *_handler) : handler{_handler} {
    names.push_back("lurk");
}

void LurkCommand::execute(std::string, std::string, bool, bool, std::string channel) {
    handler->uses_bot()->send_chat_message("A lurk a day will keep twitch at bay.", channel);
}

bool LurkCommand::has_perms_to_run(bool, bool, std::string) {
    return true;
}

bool LurkCommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string LurkCommand::list_command() {
    return names[0];
}

std::string LurkCommand::generate_help_message(const std::string &channel) {
    return "Use " + handler->uses_bot()->is_prefix(channel) + names[0] + " let the streamer know that you are lurking.";
}

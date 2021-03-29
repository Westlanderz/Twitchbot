#include "../../includes/commands/listtimerscommand.hpp"
#include <fstream>
#include <vector>

ListtimerCommand::ListtimerCommand(Bot *_bot) : bot{_bot} {
    names.push_back("listtimers");
}

void ListtimerCommand::execute(std::string, std::string, bool, bool, std::string channel) {
    std::string file = bot->is_timer_file(channel);
    std::fstream timers;
    std::vector<std::string> timers_list, output_list;
    timers.open(file, std::ios::in);
    if(!timers) {
        std::cerr << "Can not find the file for timers " + file << std::endl;
    } else {
        std::string timer;
        std::string line;
        while(std::getline(timers, line)) {
            if(line.empty()) {
                timers_list.push_back(timer);
                timer.clear();
            } else {
                timer.append(line);
            }
        }
        timers.close();
        for(auto it = timers_list.begin(); it != timers_list.end(); ++it) {
            std::string _timer = it->data();
            std::size_t find_name = _timer.find(":");
            std::size_t end_name = _timer.find(" ");
            if(find_name != std::string::npos) {
                std::string timer_name = _timer.substr(find_name + 1, end_name - find_name - 1);
                output_list.push_back(timer_name);
            }
        }
        std::string help_msg = "Here you can find the current active timers: ";
        for(auto &timer_to_list : output_list) {
            help_msg.append(timer_to_list);
            if(!strcmp(output_list.at(output_list.size() - 1).c_str(), timer_to_list.c_str())) {
                help_msg.append(".");
            } else {
                help_msg.append(", ");
            }
        }
        bot->send_chat_message(help_msg, channel);
    }
}

bool ListtimerCommand::has_perms_to_run(bool mod, bool, std::string sender) {
    if(mod || bot->is_channel(sender) || bot->is_owner(sender))
        return true;
    return false;
}

bool ListtimerCommand::find_name(std::string command_name) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if(!strcmp(it->data(), command_name.c_str()))
            return true;
    }
    return false;
}

std::string ListtimerCommand::list_command() {
    return names[0];
}

std::string ListtimerCommand::generate_help_message(const std::string &channel) {
    return "Use " + bot->is_prefix(channel) + names[0] + " to get a list of all the timers on this channel.";
}

#include <exception>
#include <iostream>
#include <string>
#include <sockpp/tcp_connector.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include "../includes/bot.hpp"

/**
 * @brief Main program cycle where the socket and bot are created
 * 
 * @return int
 */

int main(void) {
    std::string host = "irc.chat.twitch.tv";
    in_port_t port = 6667;
    sockpp::tcp_connector *conn = new sockpp::tcp_connector(sockpp::inet_address(host, port));
    
    std::cout << "connected to " << sockpp::inet_address(host, port) << std::endl;

    std::fstream config_file, channel_file;
    std::string oauthcode;
    std::vector<std::string> channels;

    std::filesystem::create_directory("../files");
    std::filesystem::create_directory("../files/config");
    std::filesystem::create_directory("../files/timers");
    config_file.open("../files/config/config.txt", std::ios::in);
	if (!config_file) {
		std::cerr << "Can not find or open ../files/config/config.txt" << std::endl;
        exit(1);
	} else {
		char ch;
		while (1) {
			config_file >> ch;
			if (config_file.eof())
				break;
            oauthcode.push_back(ch);
		}
	}
	config_file.close();

    channel_file.open("../files/config/channels.txt", std::ios::in);
    if(!channel_file) {
        std::cerr << "Can not find or open ../files/config/channels.txt" << std::endl;
        exit(1);
    } else {
        std::string line;
        while(std::getline(channel_file, line)) {
            channels.push_back(line);
        }
    }
    channel_file.close();

    Bot *bot = new Bot("Westlanderz", channels, "!", conn);

    try{
        bot->log_in(oauthcode);
        bot->run();
    } catch(std::exception &e) {
        std::cerr << "Exception thrown in main\r\n" << e.what() << std::endl;
        for(auto &channel : channels) {
            bot->send_chat_message("Leaving channel", channel);
        }
        bot->log_out();
        exit(1);
    }
}

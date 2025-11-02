#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <sstream>
#include <functional>
#include <map>
#include <iostream>

namespace io
{
	using CommandCallback = std::function<void(std::istringstream&)>;

	class CommandHandler
	{
	public:
		CommandHandler() = default;

		void addCommand(const std::string& cmd, const CommandCallback& callback);
		void executeCommands(const std::string& cmdLine);

	private:
		std::map<std::string, CommandCallback> _commands;
	};
}

#endif
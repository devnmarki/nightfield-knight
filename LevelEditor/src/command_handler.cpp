#include "command_handler.hpp"

namespace io
{
	void CommandHandler::addCommand(const std::string& cmd, const CommandCallback& callback)
	{
		_commands[cmd] = callback;
	}

	void CommandHandler::executeCommands(const std::string& cmdLine)
	{
		std::istringstream iss(cmdLine);
		std::string cmd;
		iss >> cmd;

		auto it = _commands.find(cmd);
		if (it != _commands.end())
		{
			it->second(iss);
		}
		else if (!cmd.empty())
		{
			std::cout << "Unknown command: " << cmd << ". Type 'help' for available commands." << std::endl;
		}
	}
}
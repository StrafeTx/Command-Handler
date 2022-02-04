#include "CommandHandler.hpp"

void cmds(const std::vector<std::string>& args)
{
	std::cout << "hi" << std::endl;
}

int main()
{
	SetConsoleTitleA("Demos");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);

	auto commandHandler = std::make_unique<CommandHandler>();

	commandHandler->RegisterCommand("cmds", "Prints a list of commands to the console.", 0, cmds);

	while (true)
	{
		std::cout << "> ";
		std::string cmdtemp{};
		std::getline(std::cin, cmdtemp);
		std::vector<std::string> cmd{};
		commandHandler->SplitCommand(cmdtemp, cmd);
		if (!commandHandler->ExecuteCommand(cmd))
		{
			std::cout << "Command doesn't exist! Enter 'cmds' for a list of commands." << std::endl;
		}
	}
	return 0;
}
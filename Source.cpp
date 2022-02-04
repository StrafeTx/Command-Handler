#include "CommandHandler.hpp"

auto g_pCommandHandler = std::make_unique<CommandHandler>();

void cmds(const std::vector<std::string>& args)
{
	std::vector<Command> commandList{};
	g_pCommandHandler->GetCommandList(commandList);
	for (auto cmd : commandList)
	{
		std::cout << cmd.GetName() << " : " << cmd.GetDescription() << std::endl;
	}
}

int main()
{
	SetConsoleTitleA("Demos");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);

	g_pCommandHandler->RegisterCommand("cmds", "Prints a list of commands to the console.", 0, cmds);

	while (true)
	{
		std::cout << "> ";
		std::string cmdtemp{};
		std::getline(std::cin, cmdtemp);
		std::vector<std::string> cmd{};
		g_pCommandHandler->SplitCommand(cmdtemp, cmd);
		if (!g_pCommandHandler->ExecuteCommand(cmd))
		{
			std::cout << "Command doesn't exist! Enter 'cmds' for a list of commands." << std::endl;
		}
	}
	return 0;
}
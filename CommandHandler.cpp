#include "CommandHandler.hpp"

Command::Command(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function)
{
	m_name = name;
	m_description = description;
	m_argCount = argCount;
	m_function = function;
}

const std::string Command::GetName()
{
	return m_name;
}

const std::string Command::GetDescription()
{
	return m_description;
}

const int Command::GetArgCount()
{
	return m_argCount;
}

const void* Command::GetFunction()
{
	return std::addressof(m_function);
}

void Command::Execute(const std::vector<std::string>& args)
{
	m_function(args);
}

void CommandHandler::RegisterCommand(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function)
{
	Command command{ name, description, argCount, function };
	m_CommandList.push_back(command);
}

bool CommandHandler::ExecuteCommand(const std::vector<std::string>& args)
{
	for (auto cmd : m_CommandList)
	{
		try
		{
			if (cmd.GetName() == args[0] && args.size() == (cmd.GetArgCount() + 1))
			{
				cmd.Execute(args);
				return true;
			}
		}
		catch (std::exception e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return false;
}

void CommandHandler::SplitCommand(const std::string rawcmd, std::vector<std::string>& placeholder)
{
	std::stringstream ss(rawcmd);
	std::istream_iterator<std::string> IteratorStart(ss);
	std::istream_iterator<std::string> IteratorStop{};

	placeholder.assign(IteratorStart, IteratorStop);
}

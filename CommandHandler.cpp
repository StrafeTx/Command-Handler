#include "CommandHandler.hpp"

Toggle::Toggle()
{
	m_name = "Unset";
	m_description = "Unset";
	m_toggled = false;
}

Toggle::Toggle(const std::string name, const std::string description, bool initialState)
{
	m_name = name;
	m_description = description;
	m_toggled = initialState;
}

const std::string Toggle::GetName()
{
	return m_name;
}

const std::string Toggle::GetDescription()
{
	return m_description;
}

const bool Toggle::GetState()
{
	return m_toggled;
}

void Toggle::SetState(const bool newState)
{
	m_toggled = newState;
}

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
	m_commandList.push_back(std::make_shared<Command>(command));
}

void CommandHandler::RegisterToggle(const std::string name, const std::string description, const bool initialValue)
{
	Toggle toggle{ name, description, initialValue };
	m_toggleList.push_back(std::make_shared<Toggle>(toggle));
}

const bool CommandHandler::ExecuteCommand(const std::vector<std::string>& args)
{
	for (auto cmd : m_commandList)
	{
		try
		{
			if (args.size() == (cmd->GetArgCount() + 1) && cmd->GetName() == args[0])
			{
				cmd->Execute(args);
				return true;
			}
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return false;
}

void CommandHandler::GetCommandList(std::vector<std::shared_ptr<Command>>& buffer)
{
	buffer = m_commandList;
}

void CommandHandler::GetToggleList(std::vector<std::shared_ptr<Toggle>>& buffer)
{
	buffer = m_toggleList;
}

std::shared_ptr<Toggle> CommandHandler::GetToggle(const std::string search)
{
	std::vector<std::shared_ptr<Toggle>> toggles{};
	GetToggleList(toggles);
	for (auto toggle : toggles)
	{
		if (toggle->GetName() == search)
		{
			return toggle;
		}
	}
	return nullptr;
}

void CommandHandler::SplitCommand(const std::string rawcmd, std::vector<std::string>& placeholder)
{
	std::stringstream ss(rawcmd);
	std::istream_iterator<std::string> IteratorStart(ss);
	std::istream_iterator<std::string> IteratorStop{};

	placeholder.assign(IteratorStart, IteratorStop);
}

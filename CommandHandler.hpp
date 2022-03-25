#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <memory>
#include <map>

class Toggle {
private:
	std::string m_name{};
	std::string m_description{};
	bool m_toggled{};
public:
	Toggle();
	Toggle(const std::string name, const std::string description, const bool initialState);
	const std::string GetName();
	const std::string GetDescription();
	const bool GetState();
	void SetState(const bool newState);
};

class Command {
private:
	std::string m_name{};
	std::string m_description{};
	int m_argCount{};
	std::function<void(const std::vector<std::string>&)> m_function{};
public:
	Command();
	Command(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function);
	const std::string GetName();
	const std::string GetDescription();
	const int GetArgCount();
	const void* GetFunction();
	void Execute(const std::vector<std::string>& args);
};

class CommandHandler {
private:
	std::vector<std::string> m_listList{};
	std::vector<std::shared_ptr<Command>> m_commandList{};
	std::vector<std::shared_ptr<Toggle>> m_toggleList{};
public:
	void RegisterCommand(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function);
	void RegisterToggle(const std::string name, const std::string description, bool initialValue);
	const bool ExecuteCommand(const std::vector<std::string>& args);
	void GetCommandList(std::vector<std::shared_ptr<Command>>& buffer);
	void GetToggleList(std::vector<std::shared_ptr<Toggle>>& buffer);
	std::shared_ptr<Toggle> GetToggle(const std::string toggle);
	void SplitCommand(const std::string rawcmd, std::vector<std::string>& placeholder);
};
#endif


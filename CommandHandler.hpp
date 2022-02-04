#pragma once
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

class Command {
private:
	std::string m_name{};
	std::string m_description{};
	int m_argCount{};
	std::function<void(const std::vector<std::string>&)> m_function{};
public:
	Command(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function);
	const std::string GetName();
	const std::string GetDescription();
	const int GetArgCount();
	const void* GetFunction();
	void Execute(const std::vector<std::string>& args);
};

class CommandHandler {
private:
	std::vector<Command> m_CommandList{};
public:
    void RegisterCommand(const std::string name, const std::string description, const int argCount, const std::function<void(const std::vector<std::string>&)> function);
	bool ExecuteCommand(const std::vector<std::string>& args);
	void GetCommandList(std::vector<Command>& buffer);
	void SplitCommand(const std::string rawcmd, std::vector<std::string>& buffer);
};


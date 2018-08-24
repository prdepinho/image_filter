#pragma once

#include <string>

class FilterView{
public:
	FilterView(std::string flag = "") : flag(flag) {}
	std::string GetFlag() { return flag; }
	virtual void ProcessArgs(std::vector<std::string> arguments) = 0;
	virtual int ProcessInput() = 0;
	virtual void Output() = 0;
protected:
	std::string flag;
};

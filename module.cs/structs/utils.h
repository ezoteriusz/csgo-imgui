#pragma once
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>

class CUtils {
public:
	class Console {
	public:
		void attach();
		void detach();
		void setcolor(WORD color);
	private:
		FILE* pFile;
	};
	CUtils::Console sysConsole;
	std::uint8_t* PatternScan(const char* module_name, const char* signature);
};
extern CUtils gUtils;
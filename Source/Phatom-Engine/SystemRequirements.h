#pragma once

#include <Windows.h>

#include <stdio.h>
#include <iostream>
#include <direct.h>
//#include <locale>  
//#include <iomanip>  
#include <intrin.h>

#include <conio.h>	// _getch()

// Use to convert bytes to KB
#define BYTE_TO_KBBYTE 1024
// Use to convert bytes to MB
#define BYTE_TO_MBBYTE 1048576

struct myseps : std::numpunct<char>
{
	char do_thousands_sep() const { return ','; }

	/*digits are grouped by 3 digits each */
	std::string do_grouping() const { return "\3"; }
};

class SystemRequirements
{
	public:
		static bool IsOnlyInstance(const HANDLE handle, const LPCTSTR gameTitle);
		static bool CheckStorage(const DWORDLONG diskSpaceNeeded);
		static bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
		static void CpuArchitecture();
		static bool CheckResources(LPCTSTR gameTitle);
};
#include "SystemRequirements.h"

bool SystemRequirements::IsOnlyInstance(const HANDLE handle, const LPCTSTR gameTitle)
{
	bool alreadyExist;

	alreadyExist = (GetLastError() == ERROR_ALREADY_EXISTS);

	return !alreadyExist;
}

bool SystemRequirements::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	bool enoughSpace = true;

	// Check for enough free disk space on the current disk. 
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters =
		diskSpaceNeeded / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	_int64 availInMB = (diskfree.avail_clusters / BYTE_TO_MBBYTE)  * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;

	std::cout.imbue(std::locale(std::locale(), new myseps));

	std::cout << "Checking required space : " << (diskSpaceNeeded / BYTE_TO_MBBYTE) << " MB." << std::endl;
	char disk = (char)(65 + drive - 1); // 65 is 'A'
	std::cout << "Free space in disk " << disk << ": " << availInMB << " MB." << std::endl;

	if (diskfree.avail_clusters < neededClusters)
	{
		// if you get here you don’t have enough disk space! 
		std::cout << "CheckStorage Failure : Not enough physical storage." << std::endl;
		enoughSpace = false;
	}
	std::cout << std::endl;

	return enoughSpace;
}

bool SystemRequirements::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	bool enoughMem = true;

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	std::cout << "There is  " << statex.dwMemoryLoad << " percent of memory in use." << std::endl;
	std::cout << "There are " << (statex.ullTotalPhys / BYTE_TO_KBBYTE) << " total KB of physical memory." << std::endl;
	std::cout << "There are " << (statex.ullAvailPhys / BYTE_TO_KBBYTE) << " free  KB of physical memory." << std::endl;
	std::cout << "There are " << (statex.ullTotalPageFile / BYTE_TO_KBBYTE) << " total KB of paging file." << std::endl;
	std::cout << "There are " << (statex.ullAvailPageFile / BYTE_TO_KBBYTE) << " free  KB of paging file." << std::endl;
	std::cout << "There are " << (statex.ullTotalVirtual / BYTE_TO_KBBYTE) << " total KB of virtual memory." << std::endl;
	std::cout << "There are " << (statex.ullAvailVirtual / BYTE_TO_KBBYTE) << " free  KB of virtual memory." << std::endl;

	// Show the amount of extended memory available.
	std::cout << "There are " << (statex.ullAvailExtendedVirtual / BYTE_TO_KBBYTE) << " free  KB of extended memory." << std::endl;

	if (statex.ullTotalPhys < physicalRAMNeeded)
	{
		// you don’t have enough physical memory. Tell the player to go get a real computer and give this one to his mother.
		std::cout << "CheckMemory Failure : Not enough physical memory." << std::endl;
		enoughMem = false;
	}

	// Check for enough free memory.
	if (statex.ullAvailVirtual < virtualRAMNeeded)
	{
		// you don’t have enough virtual memory available. Tell the player to shut down the copy of Visual Studio running in the background.
		std::cout << "CheckMemory Failure : Not enough virtual memory." << std::endl;
		enoughMem = false;
	}

	std::cout << std::endl;

	return enoughMem;
}

void SystemRequirements::CpuArchitecture()
{
	int CPUInfo[4] = { -1 };
	unsigned   nExIds, i = 0;
	char CPUBrandString[0x40];
	// Get the information associated with each extended ID.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	//string includes manufacturer, model and clockspeed
	std::cout << "CPU Type: " << CPUBrandString << std::endl;


	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	std::cout << "Number of Cores: " << sysInfo.dwNumberOfProcessors << std::endl;
}

bool SystemRequirements::CheckResources(LPCTSTR gameTitle)
{
	bool passed = true;

	// Singleton
	static HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (!SystemRequirements::IsOnlyInstance(handle, gameTitle))
		passed = false;

	// Disk space
	if (passed)
		passed = SystemRequirements::CheckStorage(536870912000); // approx. 500 GB

	if (passed)
		passed = SystemRequirements::CheckMemory(25000000000, 2500000000);

	SystemRequirements::CpuArchitecture();

	CloseHandle(handle);
	handle = NULL;

	char ch = _getch();

	return passed;
}
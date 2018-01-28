#pragma once
#include <Windows.h>
#include <string>

class Hardware
{
public:
	Hardware();
	~Hardware();

	void PrintHardwareInformation();
	std::string GetAllHardwareInfo();

private:

	void GetMemorySize();
	void GetDriveSer();
	void GetSoftwareInfo();
	void GetCpuInfo();
	void GetMacInfo();
	void GetAllInformation();

	uint64_t	MemorySize = 0;

	uint64_t	SysDriveSer = 0;

	TCHAR		ComputerName[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
	TCHAR		UserName[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
	TCHAR		WindowsVersion[30] = { 0 };

	uint32_t	CpuType = 0;
	uint16_t	CpuLevel = 0; 
	uint16_t	CpuRevision = 0;

	TCHAR		MacAddresse[20] = { 0 };

	TCHAR		HardInfoAll[MAX_PATH] = { 0 };
};
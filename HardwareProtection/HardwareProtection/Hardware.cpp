#include "Include.h"
#include "Hardware.h"

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

Hardware::Hardware()
{
	// Initialize
	this->GetMemorySize();
	this->GetDriveSer();
	this->GetSoftwareInfo();
	this->GetCpuInfo();
	this->GetMacInfo();
	this->GetAllInformation();
}

Hardware::~Hardware() { }


void Hardware::GetMemorySize()
{
	MEMORYSTATUSEX MemInfo;
	MemInfo.dwLength = sizeof(MemInfo);
	GlobalMemoryStatusEx(&MemInfo);

	this->MemorySize = MemInfo.ullTotalPhys;
}

void Hardware::GetDriveSer()
{
	Disk tempdrive;
	tempdrive.setSystemDrive();
	this->SysDriveSer = tempdrive.GetSerialNumber();
}

void Hardware::GetSoftwareInfo()
{

	DWORD		ComputerNameSize = ARRAYSIZE(this->ComputerName);
	GetComputerName(this->ComputerName, &ComputerNameSize);

	DWORD		UserNameSize = ARRAYSIZE(this->UserName);
	GetUserName(this->UserName, &UserNameSize);

	if (IsWindows7OrGreater())
	{
		StringCbCopy(this->WindowsVersion, sizeof(this->WindowsVersion), _T("Windows7orGreater"));
	}
	else
	{
		StringCbCopy(this->WindowsVersion, sizeof(this->WindowsVersion), _T("Windows7Lower"));
	}
}

void Hardware::GetCpuInfo()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	this->CpuType = sysinfo.dwProcessorType;
	this->CpuLevel = sysinfo.wProcessorLevel;
	this->CpuRevision = sysinfo.wProcessorLevel;
}

void Hardware::GetMacInfo()
{
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	DWORD ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	DWORD dwRetVal = 0;

	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(sizeof(IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) {
		return;
	}

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);
		if (pAdapterInfo == NULL) {
			return;
		}
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {

		_stprintf_s(MacAddresse, _T("%02X:%02X:%02X:%02X:%02X:%02X"),
			int(pAdapterInfo->Address[0]),
			int(pAdapterInfo->Address[1]),
			int(pAdapterInfo->Address[2]),
			int(pAdapterInfo->Address[3]),
			int(pAdapterInfo->Address[4]),
			int(pAdapterInfo->Address[5]));
	}

	if (pAdapterInfo)
		FREE(pAdapterInfo);
}

void Hardware::GetAllInformation()
{
	//_stprintf_s(HardInfoAll, _T("%" PRIu64 ",%" PRIu64 ",%s,%s,%s,%i,%i,%i,%s"),
	_stprintf_s(HardInfoAll, _T(",%" PRIu64 ",%" PRIu64 ",%s,%i,%i,%i,%s,"),
		this->MemorySize,
		this->SysDriveSer,
		this->ComputerName,
		//this->UserName,
		//this->WindowsVersion,
		this->CpuType,
		this->CpuLevel,
		this->CpuRevision,
		this->MacAddresse);

}

void Hardware::PrintHardwareInformation()
{
	float InGB = 1024 * 1024 * 1024;
	_tprintf(_T("Physical Memory Size:  \t %.2f GB \n"),			this->MemorySize / InGB);
	_tprintf(_T("Physical Memory Size:  \t %" PRIu64 " Byte\n\n"),	this->MemorySize);

	_tprintf(_T("Volumen Serial Number: \t %" PRIu64 "\n\n"),		this->SysDriveSer);

	_tprintf(_T("Computername:          \t %s \n"),					this->ComputerName);
	_tprintf(_T("Username:              \t %s \n"),					this->UserName);
	_tprintf(_T("Windows Version:       \t %s \n\n"),				this->WindowsVersion);

	_tprintf(_T("CPU Type:              \t %i \n"),					this->CpuType);
	_tprintf(_T("CPU Level:             \t %i \n"),					this->CpuLevel);
	_tprintf(_T("CPU Revision:          \t %i \n\n"),				this->CpuRevision);

	_tprintf(_T("MAC Address:           \t %s \n\n"),				this->MacAddresse);

	_tprintf(_T("Selected Information:  \t %s \n\n"),				this->HardInfoAll);
}

std::string Hardware::GetAllHardwareInfo()
{
	// Unicode or MBCS
#ifdef UNICODE
	std::wstring wstr(HardInfoAll);
	std::string  astr(wstr.begin(), wstr.end());
#else
	std::string  astr(HardInfoAll);
#endif

	return astr;
}
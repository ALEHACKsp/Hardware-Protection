#include "Include.h"
#include "Disk.h"

Disk::Disk()  { }

Disk::~Disk() { }

void Disk::setHomeDrive()
{
	GetEnvironmentVariable(_T("HOMEDRIVE"), this->DriverLetter, ARRAYSIZE(this->DriverLetter));
	StringCbCat(this->DriverLetter, sizeof(this->DriverLetter), _T("\\"));

	StringCbCopy(this->DriveSelect, sizeof(this->DriveSelect), _T("Home Drive"));
	this->LoadVolumenTyp();
	this->LoadVolumenInformation();
}

void Disk::setSystemDrive()
{
	TCHAR rootdrive[MAX_PATH] = { 0 };
	GetSystemWindowsDirectory(rootdrive, ARRAYSIZE(rootdrive));
	StringCbCopy(this->DriverLetter, sizeof(this->DriverLetter), rootdrive);

	StringCbCopy(this->DriveSelect, sizeof(this->DriveSelect), _T("System Drive"));
	this->LoadVolumenTyp();
	this->LoadVolumenInformation();
}

void Disk::setCurrentDrive()
{
	TCHAR rootdrive[MAX_PATH] = { 0 };
	GetCurrentDirectory(ARRAYSIZE(rootdrive), rootdrive);
	StringCbCopy(this->DriverLetter, sizeof(this->DriverLetter), rootdrive);

	StringCbCopy(this->DriveSelect, sizeof(this->DriveSelect), _T("Current Drive"));
	this->LoadVolumenTyp();
	this->LoadVolumenInformation();
}

bool Disk::CheckStickFat32()
{
	// Check if DriverLetter is load
	if (_tcscmp(this->DriverLetter, _T("")) == 0)
	{
		return 1;
	}

	// Check Drive is FAT32 formated
	if (!(_tcscmp(this->DriveFormat, _T("FAT32")) == 0))
	{
		return 1;
	}

	// Check Drive ist Removable Disk
	if (!(this->DriveTyp == 2))
	{
		return 1;
	}

	// Check if Serialnumber is available
	if (this->DriveSerialNumber == 0)
	{
		return 1;
	}

	return 0;
}

void Disk::PrintDriveInformation()
{
	// Print: Volumen Information
	_tprintf(_T("Volumen Select: \t %s \n"), this->DriveSelect);
	_tprintf(_T("Volumen Letter: \t %s \n"), this->DriverLetter);
	_tprintf(_T("Volumen Format: \t %s \n"), this->DriveFormat);
	_tprintf(_T("Volumen Typ:    \t %i \n"), this->DriveTyp);
	_tprintf(_T("Volumen Serial: \t %" PRIu64 "\n\n"), this->DriveSerialNumber);

}

void Disk::LoadVolumenTyp()
{
	this->DriveTyp = GetDriveType(this->DriverLetter);
}

void Disk::LoadVolumenInformation()
{
	// Declare: Variablen
	BOOL			VolumeInformation = false;
	//const TCHAR *	RootPathName = _T("L:\\");
	TCHAR 			VolumeNameBuffer[MAX_PATH + 1] = { 0 };
	DWORD			VolumeSerialNumber = 0;
	DWORD			MaximumComponentLength = 0;
	DWORD			FileSystemFlags = 0;
	TCHAR 			FileSystemNameBuffer[MAX_PATH + 1] = { 0 };

	// Get: Information
	VolumeInformation = ::GetVolumeInformation(
		this->DriverLetter,
		VolumeNameBuffer,
		ARRAYSIZE(VolumeNameBuffer),
		&VolumeSerialNumber,
		&MaximumComponentLength,
		&FileSystemFlags,
		FileSystemNameBuffer,
		ARRAYSIZE(FileSystemNameBuffer)
	);

	// Print: Check Drive Format
	//_tprintf(_T("Volume Information: %i \n"), VolumeInformation);
	//_tprintf(_T("Root Path Name : %s \n"), this->DriverLetter);
	//_tprintf(_T("Volumen Name : %s \n"), VolumeNameBuffer);
	//_tprintf(_T("Serial Number: %lu \n"), VolumeSerialNumber);
	//_tprintf(_T("Maximum Component: %lu \n"), MaximumComponentLength);
	//_tprintf(_T("File System Flags: %lu \n"), FileSystemFlags);
	//_tprintf(_T("File System Name: %s\n"), FileSystemNameBuffer);

	this->DriveSerialNumber = VolumeSerialNumber;
	StringCbCopy(this->DriveFormat, sizeof(this->DriveFormat), FileSystemNameBuffer);
}
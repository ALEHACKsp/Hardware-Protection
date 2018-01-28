#pragma once

class Disk
{
public:
	Disk();
	~Disk();

	void setHomeDrive();
	void setSystemDrive();
	void setCurrentDrive();

	bool CheckStickFat32();
	void PrintDriveInformation();

	uint64_t GetSerialNumber() { return this->DriveSerialNumber; };

private:
	TCHAR		DriveSelect[20] = { 0 };
	TCHAR		DriverLetter[4] = { 0 };
	TCHAR		DriveFormat[10] = { 0 };
	uint8_t		DriveTyp = 0;
	uint64_t	DriveSerialNumber = 0;

	void LoadVolumenTyp();
	void LoadVolumenInformation();
};
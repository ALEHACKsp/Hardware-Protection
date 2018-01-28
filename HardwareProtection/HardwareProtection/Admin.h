#pragma once

class Admin
{
public:
	Admin();
	~Admin();

	void Show();

private:
	void PrintAdminMenu();
	void ConvertAccessKey();
	void getHardwareHash();
	void ShowUserList();
	void PrintDiskInformation();
	void PrintHardwareInformation();
	void PrintHashInformation();
	void PrintDeveloperInformation();
};
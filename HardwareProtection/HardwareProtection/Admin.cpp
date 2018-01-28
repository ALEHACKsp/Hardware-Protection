#include "Include.h"
#include "Admin.h"

Admin::Admin()  { }

Admin::~Admin() { }

void Admin::Show()
{
	char input = 0;

	while (input != '1')
	{
		this->PrintAdminMenu();

		input = getchar();
		fflush(stdin);
		while ((getchar()) != '\n');

		switch (input) {
		case '1':
			// Go back to main programm
			break;
		case '2':
			this->ConvertAccessKey();
			break;
		case '3':
			this->getHardwareHash();
			break;
		case '4':
			this->ShowUserList();
			break;
		case '5':
			this->PrintDiskInformation();
			break;
		case '6':
			this->PrintHardwareInformation();
			break;
		case '7':
			this->PrintHashInformation();
			break;
		case '8':
			this->PrintDeveloperInformation();
			break;
		default:
			break;
		}
	}
	system("cls");
}

void Admin::PrintAdminMenu()
{
	system("cls");

	printf(">> Admin Panel <<\n\n");

	printf("1. Continue to main programm\n");
	printf("2. Convert: Personal Code to Access Key\n");
	printf("3. Convert: Personal Code to Hwid Hash\n\n");

	printf("4. Show: User List\n");
	printf("5. Show: Disk Information\n");
	printf("6. Show: Hardware Information\n");
	printf("7. Show: Hash Converting Prozess\n");
	printf("8. Show: Developer Information\n\n");

	printf("Enter your selection: ");
}

void Admin::ConvertAccessKey()
{
	system("cls");

	Hash Server;
	Server.setServer();

	printf("Input the Client Code: \n");
	char Input[256];
	std::cin.getline(Input, 256);
	Server.DecryptAccessHexTokenToHwid(Input);

	if ((Server.CheckKeyMatch()) == false)
	{
		printf("- KEY NOT MATCH \n");
	}
	else
	{
		Server.EncryptHwidToHash(Server.DecryptHwid());
		std::cout << "\nClear Hwid\n" << Server.DecryptHwid();
		std::cout << "\n\nAccess Token (copied to clipboard)\n" << Server.EncryptAccessHexToken() << std::endl;
		Server.toClipboard(Server.EncryptAccessHexToken());
	}

	system("PAUSE");
}
void Admin::getHardwareHash()
{
	system("cls");

	Hash Server;
	Server.setServer();

	printf("Input the Client Code: \n");
	char Input[256];
	std::cin.getline(Input, 256);
	Server.DecryptAccessHexTokenToHwid(Input);

	if ((Server.CheckKeyMatch()) == false)
	{
		printf("- KEY NOT MATCH \n");
	}
	else
	{
		Server.EncryptHwidToHash(Server.DecryptHwid());
		std::cout << "\nClear Hwid\n" << Server.DecryptHwid();
		std::cout << "\n\nHash Code (copied to clipboard)\n" << Server.EncryptHash() << std::endl;

		Server.toClipboard(Server.EncryptHash());
	}

	system("PAUSE");
}

void Admin::ShowUserList()
{
	system("cls");

	for (int i = 1; i < userCount; i++)
	{
		userList[i].PrintUserInformation();
	}
	
	system("PAUSE");
}

void Admin::PrintDiskInformation()
{
	system("cls");

	Disk Stick;
	Stick.setCurrentDrive();
	Stick.PrintDriveInformation();

	Stick.setSystemDrive();
	Stick.PrintDriveInformation();

	Stick.setHomeDrive();
	Stick.PrintDriveInformation();

	system("PAUSE");
}

void Admin::PrintHardwareInformation()
{
	system("cls");

	Hardware Hw;
	Hw.PrintHardwareInformation();

	system("PAUSE");
}

void Admin::PrintHashInformation()
{
	system("cls");

	Hardware Hw;
	Hash Client, Server;
	Server.setServer();

	// Step 1: Encrypt Hash on Client
	Client.EncryptHwidToClear(Hw.GetAllHardwareInfo());

	// Step 2: Decrypt Hash on Server
	std::string strtemp = Client.EncryptAccessHexToken();
	const char* c = strtemp.c_str();
	Server.DecryptAccessHexTokenToHwid(c);

	// Step 3: Encrypt Hash on Server
	Server.EncryptHwidToHash(Server.DecryptHwid());

	// Step 4: Decrypt Hash on Client
	std::string strtemp2 = Server.EncryptAccessHexToken();
	const char* c2 = strtemp2.c_str();
	Client.DecryptAccessHexTokenToHash(c2);

	// Print Information in the right order
	Client.PrintEncryptInformation();
	Server.PrintDecryptInformation();
	Server.PrintEncryptInformation();
	Client.PrintDecryptInformation();

	system("PAUSE");
}

void Admin::PrintDeveloperInformation()
{
	system("cls");

	printf("Software:  Your protected product\n");
	printf("Version:   Your product version\n");
	printf("Developer: Your name\n");
	printf("Website:   Your website link\n\n");

	printf("Software:  Hardware Protection\n");
	printf("Version:   v1.0\n");
	printf("Developer: Kage\n");
	printf("Website:   www.auxilium.cc\n\n");

	system("PAUSE");
}
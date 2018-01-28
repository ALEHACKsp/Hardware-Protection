#include "Include.h"

User userList[]{
// Active	User				Startdate	Enddate		Hwid Hash
	{ 0,	"Invalid User",		01, 01, 17, 01, 01, 17, "0000000000000000000000000000000000000000000000000000000000000000" }, // Let me here
	{ 0,	"Inactive User",	01, 01, 17, 01, 01, 99, "0000000000000000000000000000000000000000000000000000000000000000" }, // 0 = User have currently no rights
	{ 1,	"Registred User",	01, 01, 17, 01, 01, 99, "1111111111111111111111111111111111111111111111111111111111111111" }, // 1 = User can access to main program
	{ 2,	"Admin",			01, 01, 17, 01, 01, 99, "2222222222222222222222222222222222222222222222222222222222222222" }, // 2 = User can access to admin panel

	{ 2,	"Kage",				01, 01, 01, 01, 01, 99, "f8e5c207dc698c582291372f5f9c8f49385b53e53784a01c1e13fee3bf03e022" }, // Developer of the product
	{ 2,	"Your Name",		01, 01, 01, 01, 01, 99, "9999999999999999999999999999999999999999999999999999999999999999" }, // <-- Insert here your Hwid
};
int userCount = (sizeof(userList) / sizeof(*userList));
unsigned int RandomSeedKey = 12345678;					// This should be change on update to generate new access token (Maximum 8 digit)


int mainHardwareProtection()
{
	Admin		MeAdmin;
	Disk		Stick;
	Hardware	Hw;
	Hash		Client;

	Stick.setHomeDrive();
	Client.EncryptHwidToClear(Hw.GetAllHardwareInfo());

	// This show your hwid (need only for first start)
	if (true)
	{
		std::cout << "Your Hwid Hash (copied to clipboard)" << std::endl << Client.EncryptHash() << std::endl << std::endl;
		Client.toClipboard(Client.EncryptHash());
		return 1;		
	}
	
	// Check if user is admin
	if (userList[getActiveUser()].IsUserOk() == 2)
	{
		MeAdmin.Show();
	}

	// Check if active user is valid
	if (userList[getActiveUser()].IsUserOk() >= 1)
	{
		std::cout << "Welcome back " << userList[getActiveUser()].getUsername() << std::endl << std::endl;
	}
	// Else generate access token
	else
	{
		printf("- Your personal code is generated and copied to clipboard.\n");
		printf("- Please send it to the developer.\n\n");
		printf("- Input the access key: ");

		Client.toClipboard(Client.EncryptAccessHexToken());

		try // additional security because of user input
		{
			char Input[256];
			std::cin.getline(Input, 256);
			Client.DecryptAccessHexTokenToHash(Input);

			if ((Client.CheckHashMatch() == false) || ((Client.CheckKeyMatch()) == false))
			{
				throw 1;
			}
		}
		catch (...)
		{
			printf("- INVALIDE ACCESS KEY \n");
			return 1;
		}			

		printf("\n- Successfull Access \n\n");
	}

	if (Stick.CheckStickFat32())
	{
		printf("Warning: Drive is not REMOVABLE or FAT32 formated\n\n");
		//return 1;
	}

    return 0;
}


int getActiveUser()
{
	Hardware	myHardware;
	Hash		myHash;
	myHash.EncryptHwidToHash(myHardware.GetAllHardwareInfo());

	for (int i = 0; i < userCount; i++)
	{
		if (userList[i].getHwidnr() == myHash.EncryptHash())
			return i;
	}
	return 0;
}
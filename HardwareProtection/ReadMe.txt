

//////////////////////////////////////////
//
//	Project Name:	Hardware Protection
//	Version Nr.:	v1.0
//	Developer:		Kage
//	Webseite:		www.auxilium.cc
//
//////////////////////////////////////////


Description:
This tool is designed to provide a simple hardware protection.
Hardware information such as memory size, hard disk serial number, computer name, Windows 7 check,
user name, CPU type, CPU level, CPU revision and Mac address are read out.
This information is hashed with a SHA2 method and used as a unique HWID.
The program is accessed via the Hardcoded HWID or an Access Token System.
Furthermore, it can be checked if the file has been started from a removable stick with a FAT32 format


Annotations:
- The tool supports a character set of MBCS and UNICODE.
- It also supports x86 and x64 platforms.
- The protection for the user-defined time-of-use is based on the system time. 
  By a simple time conversion this can be bypassed and is therefore not safe!
- The encryption and decryption process is based on a simple xor encryption and can be reversed.
  Better would be a ciphertext encryption with base64 and a separation from admin and user client.


Access Token System:
1. user start programm and send developer personal code
2. developer convert personal code to access token
3. developer send access token to user
4. user input access token and run the programm


Import instruction:
1. Include the folder "HardwareProtection" to your project. (with all .h and .cpp files)
2. Include the content from "main.cpp" to your project "main.cpp"
3. Start the programm and copy your Hwid to clipboard
4. Go to "HardwareProtection/NewMain.cpp" and insert your Hwid in the userList
5. Then change the "RandomSeedKey" to a random 8 digit number
6. At least you need to change the first if in the "int mainHardwareProtection()"
	From: "if(true)" ->	To: "if(false)"
7. Done and give credits 
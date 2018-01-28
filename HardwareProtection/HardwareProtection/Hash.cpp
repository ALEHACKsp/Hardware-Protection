#include "Include.h"
#include "Hash.h"

Hash::Hash()  { 

	unsigned int tempSeed = RandomSeedKey;										// Input a random number here (Max. 8 character)
	srand(tempSeed);															// Initiliaze the Random Seed

	static const char possibleChar[] = "!#$%&'()*+-./:;<=>?@][]^_`{|}~";		// This are the possible Character for XOR encrypton
	uint8_t possibleCharLength = sizeof(possibleChar) - 1;						// This is the Length of the possible XOR Character

	std::string tempValue = std::to_string(tempSeed);							// Get the random number to a string	
	std::string tempCode1 = "";
	std::string tempCode2 = "";
	std::string tempKey1 = "";
	std::string tempKey2 = "";

	for (unsigned int i = 0; i <= 50; ++i)
	{
		tempCode1 += possibleChar[rand() % possibleCharLength];					// Get the random Charactor for XOR Encryption
		tempCode2 += possibleChar[rand() % possibleCharLength];					// Get the random Charactor for XOR Decryption
	}

	picosha2::hash256_hex_string(tempCode1, tempKey1);							// Generate random Number for Client Key Encryption
	picosha2::hash256_hex_string(tempCode2, tempKey2);							// Generate random Number for Server Key Encryption

	tempKey1 = tempKey1.substr(0, 16);											// Take the first Character for Client Key Encryption
	tempKey2 = tempKey2.substr(0, 16);											// Take the first Character for Server Key Encryption
	
	this->dCompareKey = tempKey1;												// Set Client Configuration
	this->eKey = tempKey2;
	this->dCode = tempCode1;
	this->eCode = tempCode2;

	this->hexToStrIsGood = false;
}

Hash::~Hash() { }

void Hash::EncryptHwidToClear(std::string clearHwid)
{
	// Set the clear Hwid
	this->eHwid = clearHwid;

	// Set the hashed Hwid
	picosha2::hash256_hex_string(clearHwid, this->eHash);

	// Set the key and clear Hwid
	this->eKeyAndHash = this->eKey + this->eHwid;

	// Set the access token
	this->eAccessToken = crypt(this->eKeyAndHash, this->eCode);

	// Set hex format to access token
	this->eAccessHexToken = strToHex(this->eAccessToken, true);
}

void Hash::EncryptHwidToHash(std::string clearHwid)
{
	// Set the hashed Hwid
	this->eHwid = clearHwid;

	// Set the hashed Hwid
	picosha2::hash256_hex_string(clearHwid, this->eHash);

	// Set the key and hashed Hwid
	this->eKeyAndHash = this->eKey + this->eHash;

	// Set the access token
	this->eAccessToken = crypt(this->eKeyAndHash, this->eCode);

	// Set hex format to access token
	this->eAccessHexToken = strToHex(this->eAccessToken, true);
}

void Hash::DecryptAccessHexTokenToHwid(const char *srcToHwid)
{
	// Set the access hex token
	this->dAccessHexToken = srcToHwid;

	// Set the acces token
	this->dAccessToken = hexToStr(srcToHwid);
	if (this->hexToStrIsGood == false) { return; }

	// Set the key and clear Hwid
	this->dKeyAndHash = this->crypt(this->dAccessToken, this->dCode);

	// Set the key
	this->dKey = this->dKeyAndHash.substr(0, this->dCompareKey.length());

	// Set the clear Hwid
	this->dHwid = this->dKeyAndHash.substr(this->dCompareKey.length(), this->dKeyAndHash.length());

	// Set the hashed Hwid
	//picosha2::hash256_hex_string(dHwid, this->dHash);
}

void Hash::DecryptAccessHexTokenToHash(const char *srcToHash)
{
	// Set the access hex token
	this->dAccessHexToken = srcToHash;

	// Set the acces token
	this->dAccessToken = hexToStr(srcToHash);
	if (this->hexToStrIsGood == false) { return; }

	// Set the key and hashed Hwid
	this->dKeyAndHash = this->crypt(this->dAccessToken, this->dCode);

	// Set the key
	this->dKey = this->dKeyAndHash.substr(0, this->dCompareKey.length());

	// Set the hashed Hwid
	this->dHash = this->dKeyAndHash.substr(this->dCompareKey.length(), this->dKeyAndHash.length());
}

void Hash::setServer()
{
	//Swap Encryption with decryption Key and Code

	std::string tempKey1	= this->dCompareKey;
	std::string tempKey2	= this->eKey;
	std::string tempCode1	= this->dCode;
	std::string tempCode2	= this->eCode;

	this->eKey				= tempKey1;
	this->dCompareKey		= tempKey2;
	this->eCode				= tempCode1;
	this->dCode				= tempCode2;
	
}

void Hash::toClipboard(const std::string &s) {
	HWND hwnd = GetDesktopWindow();
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

bool Hash::CheckHashMatch()
{
	if (this->eHash == this->dHash)
	{
		return true;
	}
	return false;
}

bool Hash::CheckKeyMatch()
{
	if (this->dKey == this->dCompareKey)
	{
		return true;
	}
	return false;
}

void Hash::PrintEncryptInformation() {

	std::cout << "\n________________________________ENCRYPT_PROZESS_________________________________\n";
	std::cout << "\n[1] Encrypt Hwid\n\t" << this->eHwid;
	std::cout << "\n[2] Encrypt Hash\n\t" << this->eHash;
	std::cout << "\n[3] Encrypt Key\n\t" << this->eKey;
	std::cout << "\n[4] \n\t";
	std::cout << "\n[5] Encrypt Key and (Hash or Hwid)\n\t" << this->eKeyAndHash;
	std::cout << "\n[6] Encrypt Code\n\t" << this->eCode;
	std::cout << "\n[7] Encrypt Access Token\n\t" << this->eAccessToken;
	std::cout << "\n[8] Encrypt Access Hex Token\n\t" << this->eAccessHexToken;
	std::cout << "\n________________________________________________________________________________\n";
}

void Hash::PrintDecryptInformation() {

	std::cout << "\n________________________________DECRYPT_PROZESS_________________________________\n";
	std::cout << "\n[8] Decrypt Access Hex Token\n\t" << this->dAccessHexToken;
	std::cout << "\n[7] Decrypt Access Token\n\t" << this->dAccessToken;
	std::cout << "\n[6] Decrypt Code\n\t" << this->dCode;
	std::cout << "\n[5] Decrypt Key and (Hash or Hwid)\n\t" << this->dKeyAndHash;
	std::cout << "\n[4] Decrypt Compare Key\n\t" << this->dCompareKey;
	std::cout << "\n[3] Decrypt Key\n\t" << this->dKey;
	std::cout << "\n[2] Decrypt Hash\n\t" << this->dHash;
	std::cout << "\n[1] Decrypt Hwid\n\t" << this->dHwid;
	std::cout << "\n________________________________________________________________________________\n";
}

std::string Hash::crypt(std::string cmsg, std::string ckey)
{

	//std::cout << cmsg.size() std::endl;
	// Make sure the key is at least as long as the message
	std::string tmp(ckey);
	while (ckey.size() < cmsg.size())
		ckey += tmp;

	// And now for the encryption part
	for (std::string::size_type i = 0; i < cmsg.size(); ++i)
		cmsg[i] ^= ckey[i];
	return cmsg;
}

std::string Hash::strToHex(const std::string& s, bool upper = false)
{
	std::ostringstream ret;

	unsigned int c;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		c = (unsigned int)(unsigned char)s[i];
		ret << std::hex << std::setfill('0') <<
			std::setw(2) << (upper ? std::uppercase : std::nouppercase) << c;
	}
	return ret.str();
}

std::string Hash::hexToStr(const char *src)
{
		this->hexToStrIsGood = true;
		char buffer[256];
		char *buffer2 = &buffer[0];
		size_t size = strlen(src);

		if (size % 2 == 1)										{ this->hexToStrIsGood = false; }
		if (this->eKey.length() >= this->eCode.length())		{ this->hexToStrIsGood = false; }
		if (size <= this->eCode.length() + this->eKey.length()) { this->hexToStrIsGood = false; }

		int8_t PairValue = 0;

		for (size_t i = 0; i < size; i = i + 2) {
			PairValue = 0;
			PairValue = getPairValue(src[i], src[i + 1]);
			if (PairValue == -1) { this->hexToStrIsGood = false; }

			*buffer2 = PairValue;
			buffer2++;
		}
		//this->dAccessToken = *dst;
		*buffer2 = 0;
		std::string temp = buffer;

		return temp;
}

int8_t Hash::getPairValue(char digit1, char digit2) 
{
	int8_t v1 = getDigitValue(digit1);
	int8_t v2 = getDigitValue(digit2);

	if (v1 == -1 || v2 == -1)
	{
		return -1;
	}
	else
	{
		return (v1 * 16 + v2);
	}
}

int8_t Hash::getDigitValue(char digit) 
{
	int8_t n = digit - '0';
	if (n >= 0 && n<10) { return n; }
	if (digit == 'A') { return 10; }
	if (digit == 'B') { return 11; }
	if (digit == 'C') { return 12; }
	if (digit == 'D') { return 13; }
	if (digit == 'E') { return 14; }
	if (digit == 'F') { return 15; }
	return -1;
}
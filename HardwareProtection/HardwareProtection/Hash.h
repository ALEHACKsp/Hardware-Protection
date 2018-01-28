#pragma once
#include <string>

/*
///ENCRYPT PROZESS
Clear Hardware ID						-> Hashed Hardware ID
Hashed Hardware ID						-> Hashed Hardware ID + Key
Hashed Hardware ID + Key				-> Hashed Hardware ID + Key + Encryption
Hashed Hardware ID + Key + Encryption	-> Access Token
Access Token							-> Access Token Hex Format

///DECRYPT PROZESS
Access Token Hex Format					-> Access Token
Access Token							-> Hashed Hardware ID + Key + Encryption
Hashed Hardware ID + Key + Encryption   -> Hashed Hardware ID + Key
Hashed Hardware ID + Key				-> Hashed Hardware ID
Hashed Hardware ID + Key				-> Key
*/

class Hash
{
public:
	Hash();
	~Hash();

	///ENCRYPT PROZESS
	void			EncryptHwidToClear				( std::string clearHwid );
	void			EncryptHwidToHash				( std::string clearHwid );
	//std::string	EncryptHwidGet()				{ return this->eHwid; };	
	std::string		EncryptHash()					{ return this->eHash; };
	//std::string	EncryptKey()					{ return this->eKey; };
	//std::string	EncryptKeyAndHash()				{ return this->eKeyAndHash; };
	//std::string	EncryptAccessToken()			{ return this->eAccessToken; };
	std::string		EncryptAccessHexToken()			{ return this->eAccessHexToken; };

	///DECRYPT PROZESS
	void			DecryptAccessHexTokenToHwid		(const char *srcToHwid);
	void			DecryptAccessHexTokenToHash		(const char *srcToHash);
	//std::string	DecryptAccessHexTokenGet()		{ return this->dAccessHexToken; };
	//std::string	DecryptAccessToken()			{ return this->dAccessToken; };
	//std::string	DecryptKeyAndHash()				{ return this->dKeyAndHash; };
	//std::string	DecryptHash()					{ return this->dHash; };
	//std::string	DecryptKey()					{ return this->dKey; };
	std::string		DecryptHwid()					{ return this->dHwid; };

	void setServer();
	void toClipboard(const std::string &s);

	bool CheckHashMatch();
	bool CheckKeyMatch();

	void PrintEncryptInformation();
	void PrintDecryptInformation();

private:

	std::string eHwid;
	std::string eHash;
	std::string eKey;
	std::string eKeyAndHash;
	std::string eCode;
	std::string eAccessToken;
	std::string eAccessHexToken;

	std::string dAccessHexToken;
	std::string dAccessToken;
	std::string dCode;
	std::string dKeyAndHash;
	std::string dKey;
	std::string dCompareKey;
	std::string dHash;
	std::string dHwid;

	std::string crypt(std::string cmsg, std::string key);

	std::string strToHex(const std::string& s, bool upper);

	std::string hexToStr(const char *src);
	int8_t getPairValue(char digit1, char digit2);
	int8_t getDigitValue(char digit);
	bool hexToStrIsGood;

};
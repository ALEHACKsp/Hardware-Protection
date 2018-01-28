#pragma once
#include <string>

class User {

public:

	User(int active, std::string name, int startDate, int startMonth, int startYear, int endDate, int endMonth, int endYear, std::string HwidHash);
	~User();

	int IsUserOk(void);
	void PrintUserInformation(void);

	std::string getUsername() { return this->username; }
	std::string getHwidnr() { return this->hwidnr; }

private:
	int			status;
	std::string username;
	struct tm	starttime;
	struct tm	endtime;
	std::string hwidnr;
};
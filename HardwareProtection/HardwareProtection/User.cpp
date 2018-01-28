#include "Include.h"
#include "User.h"

User::User(int active, std::string name, int startDate, int startMonth, int startYear, int endDate, int endMonth, int endYear, std::string HwidHash) {

	this->status = active;
	this->username = name;
	
	this->starttime.tm_sec = 0;
	this->starttime.tm_min = 0;
	this->starttime.tm_hour = 0;
	this->starttime.tm_mday = startDate;
	this->starttime.tm_mon = startMonth - 1;
	this->starttime.tm_year = startYear + 100;

	this->endtime.tm_sec = 0;
	this->endtime.tm_min = 0;
	this->endtime.tm_hour = 0;
	this->endtime.tm_mday = endDate;
	this->endtime.tm_mon = endMonth - 1;
	this->endtime.tm_year = endYear + 100;

	this->hwidnr = HwidHash;
}

User::~User() { }

int User::IsUserOk()
{
	time_t now = 0;
	time( &now );
	double secondsdiff = 0;

	// Check user is inactive
	if (this->status == 0) {
		return 0;
	}

	// Check Startdate smaller then today
	secondsdiff = difftime(now, mktime(&this->starttime));
	if (secondsdiff <= 0) {
		return 0;
	}

	// Check Enddate is bigger then today
	secondsdiff = difftime(now, mktime(&this->endtime));
	if (secondsdiff >= 0) {
		return 0;
	}

	// Check user is admin
	if (this->status == 2) {
		return 2;
	}

	// User is registered
	return 1;
}

void User::PrintUserInformation()
{
	// Print: User Information
	printf(		 "Status:     \t %i \n",		this->status);
	std::cout << "Username:   \t " <<			this->username << std::endl;
	printf(		 "Start Date: \t %i.%i.%i \n",	this->starttime.tm_mday, this->starttime.tm_mon + 1, this->starttime.tm_year - 100);
	printf(		 "Ende Date:  \t %i.%i.%i \n",	this->endtime.tm_mday, this->endtime.tm_mon + 1, this->endtime.tm_year - 100);
	std::cout << "Hwid Hash:  \t " <<			this->hwidnr << std::endl << std::endl;
}
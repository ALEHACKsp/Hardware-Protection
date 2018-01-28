#pragma once
#include "User.h"

extern User userList[];
extern int userCount;
extern unsigned int RandomSeedKey;

int mainHardwareProtection();
int getActiveUser();
#pragma once
#pragma comment(lib, "IPHLPAPI.lib")	// MAC Network Adapter
#pragma warning(disable: 6387)			// copy to clipboard function, value can be 0!

#include <windows.h>		// Windows API Features
#include <stdio.h>			// Basic Input Output C
#include <iostream>			// Basic Input Output C++
#include <tchar.h>			// Generik Charset Set Type (TCHAR)
//#include <stdint.h>		// Standard uint_8  Types
#include <inttypes.h>		// Extended uint_64 Types with Print Features
#include <strsafe.h>		// String Copy Function
#include <iphlpapi.h>		// MAC Network Adapter
#include <VersionHelpers.h> // Current Windows Version
#include <string>			// Datentyp String
#include <sstream>			// Spezial String Steam
#include <iomanip>			// Setfill Option for Hex Convert

#include "NewMain.h"		// Main Hardware Protection
#include "User.h"			// Class: Hard Coded Userlist
#include "Admin.h"			// Class: Admin Panel
#include "Disk.h"			// Class: Get Drive Information 
#include "Hardware.h"		// Class: Get Hardware Information
#include "Hash.h"			// Class: Convert HwId
#include "picosha2.h"		// Generate SHA2 Hash
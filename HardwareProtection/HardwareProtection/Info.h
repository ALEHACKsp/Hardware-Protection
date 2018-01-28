#pragma once

//////////////////////////////////////////
//
//	Project Name:	Hardware Protection
//	Version Nr.:	v1.0
//	Developer:		Kage
//	Webseite:		www.auxilium.cc
//
//////////////////////////////////////////


//////////////////////////////////////////
//
//	Counting all code lines in MS VS
//
//	Press:	Ctrl + Shit + F
//	Input:	\n
//	Option: Use Regular Expression
//	Search: Find All
//
//////////////////////////////////////////


//////////////////////////////////////////
//
// Reference Links
//
// Convert String to Hex 
// http://albertech.blogspot.de/2015/01/c-function-to-convert-string-to-hex.html?q=hex+to+string
//
// XOR Crypt
//http://www.cplusplus.com/forum/windows/128374/
//
// All Windows Data Types
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx#LPWSTR
//
// Little help with get hardware information
// https://www.codeproject.com/Articles/115061/Determine-Information-about-System-User-Processes#MemoryInfo
//
// Hash Function PicoSHA2
// https://github.com/okdshin/PicoSHA2
//
// Random String Generator
// http://www.cplusplus.com/forum/windows/88843/
//
// UNICODE friendly
// http://www.cplusplus.com/forum/articles/16820/
//
// Windows.h String Definition UNICODE and MBCS
// https://msdn.microsoft.com/de-de/library/windows/desktop/ff381407(v=vs.85).aspx
//
//////////////////////////////////////////


//////////////////////////////////////////
//
//	quick overview of charset
//
//	// generic with type defination
//	LPCTSTR R = L"C:\\";
//	// generic with defination
//	CONST TCHAR * Ro = L"C:\\";
//
//	// UNICODE with type defination
//	LPCWSTR Roo = L"C:\\";
//	// UNICODE with defination
//	CONST WCHAR * Root = L"C:\\";
//
//	// UNICODE with defination
//	const wchar_t *RootP = L"C:\\";
//
//
//	CHAR		char
//
//	LPSTR		char*
//	LPCSTR		const char*
//
//	LPWSTR		wchar_t*
//	LPCWSTR		const wchar_t*
//
//	LPTSTR		TCHAR*			// (can be this char* or that wchar_t*)
//	LPCTSTR		const TCHAR*
//
//////////////////////////////////////////
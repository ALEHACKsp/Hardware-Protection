#include "HardwareProtection/NewMain.h"


int main()
{
	if(mainHardwareProtection())
	{
		getchar();
		return 1;
	}
	getchar();
	// Else continue to main program
}
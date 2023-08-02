#include "Data.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Size_Test:" << endl;
	cout << "FCB_NAME_LENGTH: " << FCB_NAME_LENGTH << endl;
	cout << "sizeof(FCB): " << sizeof(FCB) << endl;
	cout << "FCB_SIZE: " << FCB_SIZE << endl;
	cout << "sizeof(FileSystem_Data): " << sizeof(FileSystem_Data) << endl;
	cout << "FILESYSTEM_DATA_SIZE: " << FILESYSTEM_DATA_SIZE << endl;
	return 0;
}

#include "Data.h"
#include "FileIO_Template.cpp"
#include "Utils_Template.cpp"
#include "vfs_macros.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Read Test" << endl;
	auto data = FileIO::read_file<FileSystem_Data>("FileSystem/test.bin");
	cout << "The result of data->fb_status.directory_list[0] is: " << data->fb_status.directory_list[0] << endl;
	return 0;
}

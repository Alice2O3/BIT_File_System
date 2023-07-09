#include "Data.h"
#include "FileIO.h"
#include "Utils_Template.cpp"
#include "vfs_macros.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Write Test" << endl;
	auto data = make_unique<FileSystem_Data>();
	data->fb_status.directory_list[0] = 48;
	FileIO::write_file(data, "FileSystem/test.bin");
	return 0;
}

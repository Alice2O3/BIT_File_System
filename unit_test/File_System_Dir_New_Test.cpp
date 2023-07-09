#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Dir New Test" << endl;
	BITVFS vfs;
	vfs.create_file_system(DIR_TEST_FILE_NAME);
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.mkdir("Alpha");
	vfs.mkdir("Beta");
	vfs.mkdir("Gamma");
	vfs.mkdir("Delta");
	vfs.exit_file_system();
	return 0;
}

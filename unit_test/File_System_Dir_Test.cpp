#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Dir Test" << endl;
	BITVFS vfs;
	if (vfs.file_system_exists(DIR_TEST_FILE_NAME) == VFS_FILE_SYSTEM_DOES_NOT_EXIST) {
		vfs.create_file_system(DIR_TEST_FILE_NAME);
	}
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.mkdir("ASK");
	vfs.exit_file_system();
	return 0;
}

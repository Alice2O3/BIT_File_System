#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Dir List Test" << endl;
	BITVFS vfs;
	if (vfs.file_system_exists(DIR_TEST_FILE_NAME) == VFS_FILE_SYSTEM_DOES_NOT_EXIST) {
		vfs.create_file_system(DIR_TEST_FILE_NAME);
	}
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.ls();
	vfs.chdir("BBB");
	vfs.chdir("KKK");
	return 0;
}

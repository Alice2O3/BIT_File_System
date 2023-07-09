#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Cd Test" << endl;
	BITVFS vfs;
	if (vfs.file_system_exists(DIR_TEST_FILE_NAME) == VFS_FILE_SYSTEM_DOES_NOT_EXIST) {
		vfs.create_file_system(DIR_TEST_FILE_NAME);
	}
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.pwd();
	vfs.cd("..");
	vfs.ls();
	vfs.cd("DDD");
	vfs.ls();
	vfs.cd("..");
	vfs.cd("..");
	vfs.cd("..");
	vfs.cd("AAA");
	return 0;
}

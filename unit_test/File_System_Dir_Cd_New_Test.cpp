#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Cd New Test" << endl;
	BITVFS vfs;
	vfs.create_file_system(DIR_TEST_FILE_NAME);
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.mkdir("AAA");
	vfs.mkdir("BBB");
	vfs.mkdir("CCC");
	vfs.mkdir("DDD");
	vfs.mkdir("EEE");
	vfs.mkdir("FFF");
	vfs.mkdir("GGG");
	vfs.cd("..");
	vfs.cd("CCC");
	vfs.mkdir("AAA");
	vfs.mkdir("BBB");
	vfs.mkdir("CCC");
	vfs.mkdir("DDD");
	vfs.mkdir("EEE");
	vfs.mkdir("FFF");
	vfs.mkdir("GGG");
	vfs.cd("AAA");
	vfs.mkdir("AAA");
	vfs.mkdir("BBB");
	vfs.mkdir("CCC");
	vfs.mkdir("DDD");
	vfs.mkdir("EEE");
	vfs.mkdir("FFF");
	vfs.mkdir("GGG");
	vfs.cd("..");
	vfs.cd("EEE");
	vfs.exit_file_system();
	return 0;
}

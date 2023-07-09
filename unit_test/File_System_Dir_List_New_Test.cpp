#include "BITVFS.h"
#include <iostream>

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "DirTest";

int main()
{
	cout << "File System Dir List New Test" << endl;
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
	vfs.ls();
	vfs.chdir("AAA");
	vfs.chdir("HHH");
	vfs.rmdir("GGG");
	vfs.ls();
	vfs.rmdir("DDD");
	vfs.ls();
	vfs.mkdir("HHH");
	vfs.mkdir("III");
	vfs.mkdir("JJJ");
	vfs.mkdir("DDD");
	//Error
	vfs.mkdir("DDD");
	vfs.ls();
	vfs.exit_file_system();
	return 0;
}

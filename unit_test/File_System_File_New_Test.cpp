#include "BITVFS.h"
#include <iostream>
#include "Utils_Template.cpp"

using namespace std;

constexpr auto DIR_TEST_FILE_NAME = "Nardack";

int main()
{
	BITVFS vfs;
	vfs.clear_file_systems();
	vfs.create_file_system(DIR_TEST_FILE_NAME);
	vfs.open_file_system(DIR_TEST_FILE_NAME);
	vfs.mkdir("AAA");
	vfs.mkdir("BBB");
	vfs.mkdir("CCC");
	vfs.mkdir("DDD");
	vfs.cd("BBB");
	vfs.create_file("ABC.txt");
	vfs.mkdir("AAA");
	vfs.create_file("DEF.txt");
	vfs.create_file("GHI.txt");
	vfs.mkdir("BBB");
	vfs.create_file("JKL.txt");
	vfs.ls();
	vfs.open_file("GHI.txt");
	vfs.write_file("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	vfs.close_file();
	vfs.open_file("DEF.txt");
	vfs.write_file("The quick brown fox jumps over the lazy dog.");
	vfs.close_file();
	vfs.open_file("DEF.txt");
	vfs.read_file();
	vfs.close_file();
	vfs.delete_file("GHI.txt");
	// Error
	vfs.delete_file("GHI.txt");
	// Error
	vfs.open_file("GHI.txt");
	vfs.ls();
	vfs.cd("..");
	vfs.exit_file_system();
	return 0;
}

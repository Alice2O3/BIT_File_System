#include "BITVFS.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "File System Open Test" << endl;
	BITVFS vfs;
	vfs.create_file_system("ABCDEFGH");
	vfs.create_file_system("Nardack");
	vfs.create_file_system("Krenz");
	vfs.list_file_systems();
	vfs.open_file_system("Nardack");
	//Error
	vfs.create_file_system("Rella");
	vfs.exit_file_system();
	//Error
	vfs.exit_file_system();
	vfs.delete_file_system("Krenz");
	vfs.delete_file_system("Rella");
	vfs.clear_file_systems();
	return 0;
}

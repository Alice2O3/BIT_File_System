#include "CMD.h"
#include "Logger_Template.cpp"
#include "BITVFS.h"
#include <stdlib.h>

using namespace std;

void show_intro() {
	Logger::log();
	Logger::log("Welcome to BIT Virtual File System! Run the \"help\" command for more instructions!");
	Logger::log();
}

int main()
{
	show_intro();
	CMD cmd(make_unique<BITVFS>());
	cmd.run();
	system("pause");
	return 0;
}

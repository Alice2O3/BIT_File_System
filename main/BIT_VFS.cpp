#include "CMD.h"
#include "Logger_Template.cpp"
#include "BITVFS.h"

using namespace std;

void show_intro() {
	Logger::log();
	Logger::log("Welcome to BIT Virtual File System! Run the \"help\" command for more instructions!");
#ifdef _WIN32
	Logger::log("Current System: Windows");
#else
	Logger::log("Current System: Linux");
#endif
	Logger::log();
}

int main()
{
	show_intro();
	CMD cmd(make_unique<BITVFS>());
	cmd.run();
#ifdef _WIN32
	#include <stdlib.h>
	system("pause");
#endif
	return 0;
}

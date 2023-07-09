#include "CMD.h"
#include "BITVFS.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "CMD Test" << endl;
	CMD cmd(make_unique<BITVFS>());
	cmd.run();
	return 0;
}

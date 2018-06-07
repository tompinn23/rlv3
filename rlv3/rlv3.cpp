// rlv3.cpp : Defines the entry point for the application.
//

#include "rlv3.h"


#include "spdlog/spdlog.h"
//#include "duktape.h"
#define SOL_CHECK_ARGUMENTS 1
#define SOL_IN_DEBUG_DETECTED 1
#include "sol.hpp"


#include <fstream>
#include <sstream>

#include "u-util.h"
#include "u-mem.h"
#include "u-file.h"
#include "data.h"


using namespace std;

std::string slurp(std::ifstream& in)
{
	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}


int main(int argc, char* argv[])
{
	init_stuff();
	auto log = spdlog::get("main");
	auto dir = rl_dir("./data");
	Data dat = Data();

	init_datafiles(dir, dat);
	dat.print_room(0);
	dat.print_room(1);
	while (1);
	return 0;
}

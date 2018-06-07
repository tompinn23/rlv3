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
	auto dir = rl_dir(".");
	auto entry = dir.list_dir();
	for (auto x : entry)
	{
		if (auto dir = std::get_if<rl_dir>(&x))
			log->info("[DIR] {}", dir->get_path());
		if (auto file = std::get_if<rl_file>(&x))
			log->info("[FILE] {}", file->get_path());
	}
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	Data dat = Data();
	lua["data"] = &dat;
	lua.new_usertype<Data>("Data", "init_rooms", &Data::init_rooms);
	//if (!result.valid()) {
	//	sol::error err = result;
	//	sol::call_status status = result.status();
	//	log->error("Something went awful:\n\t{}", err.what());
	//}
	dat.print_room(1);
	while (1);
	return 0;
}

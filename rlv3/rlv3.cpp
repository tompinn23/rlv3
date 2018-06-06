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
#include "data.h"

using namespace std;

std::string slurp(std::ifstream& in)
{
	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

bool init_room(std::pair<sol::object, sol::object> key_value_pair) {
	auto rom = key_value_pair.second;
	if (rom.get_type() != sol::type::table)
	{
		//spdlog::get("main")->error("Expected room definition");
		throw sol::error::runtime_error("Room Definition not found");
	}
	sol::table room = rom.as<sol::table>();
		 
}

bool init_rooms(sol::table table)
{
	auto log = spdlog::get("main");
	// Loop over all the rooms.
	for (auto x : table)
	{
		if (x.second.get_type() != sol::type::table)
		{
			//spdlog::get("main")->error("Expected room definition");
			throw sol::error::runtime_error("Room Definition not found");
		}
		sol::table room = x.second.as<sol::table>();
		std::string name = room["name"];
		int width = room["width"];
		int height = room["height"];
		room.
	}
	return true;
}



int main(int argc, char* argv[])
{
	std::string code = R"(
	init_rooms({
	{
		name="Room 1",
		width=6,
		height=6,
		plan={
			"######",
			"#....#",
			"#....#",
			"#....#",
			"#....#",
			"######"
		}
	},
	{
		name="Room 2",
		width=7,
		height=8,
		plan={
			"######",
			"#....#",
			"#....#",
			"#....#",
			"#....#",
			"######"
		}
	}
})
	)";
	init_stuff();
	auto log = spdlog::get("main");
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	//lua["data"] = Data();
	//lua.new_usertype<Data>("Data", "init_rooms", &Data::init_rooms);
	lua["init_rooms"] = init_rooms;
	sol::protected_function_result result = lua.safe_script(code, sol::script_pass_on_error);

	if (!result.valid()) {
		sol::error err = result;
		sol::call_status status = result.status();
		log->error("Something went awful:\n\t{}", err.what());
	}

	while (1);
	return 0;
}

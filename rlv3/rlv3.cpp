// rlv3.cpp : Defines the entry point for the application.
//

#include "rlv3.h"


#include "spdlog/spdlog.h"
//#include "duktape.h"
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"


#include <fstream>
#include <sstream>

#include "u-util.h"
#include "u-mem.h"

using namespace std;

std::string slurp(std::ifstream& in)
{
	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}


int main(int argc, char* argv[])
{
	std::string code = R"(
	aspd
	print('soop')
	)";
	init_stuff();
	auto log = spdlog::get("main");
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	sol::protected_function_result result = lua.safe_script(code, sol::script_pass_on_error);

	if (!result.valid()) {
		sol::error err = result;
		sol::call_status status = result.status();
		log->error("Something went awful:\n\t{}", err.what());
	}

	while (1);
	return 0;
}

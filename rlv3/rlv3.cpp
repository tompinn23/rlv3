// rlv3.cpp : Defines the entry point for the application.
//

#include "rlv3.hpp"


#include "console.hpp"
#include "data.hpp"
#include "u-file.hpp"
#include "u-mem.hpp"
#include "u-util.hpp"

#include "BearLibTerminal.h"
//#include "duktape.h"
#define SOL_CHECK_ARGUMENTS 1
#define SOL_IN_DEBUG_DETECTED 1
#include "sol.hpp"
#include "spdlog/spdlog.h"




#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <thread> 


using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

using namespace terminal;

std::string slurp(std::ifstream& in)
{
	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

int main(int argc, char* argv[])
{
	terminal::open();
	terminal::set("window: size=80x50; font: Taffer_10x10.png, size=10x10");
	init_stuff();
	auto log = spdlog::get("main");
	auto dir = rl_dir("./data");
	data::GameData dat = data::GameData();

	data::init_datafiles(dir, dat);
	dat.print_room(0);
	dat.print_room(1);

	terminal::put(0, 1, 'C');
	terminal::put(1, 0, 'c');

	terminal::refresh();

	/*time_point<steady_clock> start;
	time_point<steady_clock> end;
	std::vector<milliseconds> times;
	for(int a = 0; a < 100; a++)
	{
		start = steady_clock::now();
		color_t bk = color_from_argb(255, rand() % 255, rand() % 255, rand() % 255);
		color_t fg = color_from_argb(255, rand() % 255, rand() % 255, rand() % 255);
		terminal_bkcolor(bk);
		terminal_color(fg);
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 50; j++)
				terminal_put(i, j, (32 + (rand() % 93)));
		}
		terminal_refresh();
		end = steady_clock::now();
		milliseconds diff = duration_cast<milliseconds>(end - start);
		times.push_back(diff);
		log->info("Took: {}ms", diff.count());
	}
	int64_t sum = 0;
	for (auto& n : times)
	{
		sum += n.count();
	}
	log->info("Average: {}", sum / times.size());*/
	while (true);
	return 0;
}

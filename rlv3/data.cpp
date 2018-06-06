#include "data.h"

#include "spdlog/spdlog.h"

rl_room::rl_room(std::string name, int width, int height, std::vector<char> map) : 
	name(name), width(width), height(height), map(map) 
{

}

rl_room::rl_room(sol::table &room)
{
	name = room.get<std::string>("name");
	width = room.get<int>("width");
	height = room.get<int>("height");
	sol::table plan = room.get<sol::table>("plan");
	map.resize(height * width);
	for (int j = 0; j < plan.size(); j++)
	{
		std::string line = plan.get<std::string>(j);
		for (int k = 0; k < width; k++)
		{
			map[k * width + j] = line[k];
		}
	}
}

Data::Data()
{

}

Data::~Data()
{

}

bool Data::init_rooms(sol::table table)
{
	auto log = spdlog::get("main");
	// Loop over all the rooms.
	for (int i = 0; i < table.size(); i++)
	{
		rl_room* room = new rl_room(table[i]);
		log->info(room->name);
		//log->info(room->map);
	}
	return true;
}

bool Data::init_data(sol::table table)
{
	return false;
}
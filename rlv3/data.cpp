#include "data.h"

#include "spdlog/spdlog.h"

rl_room::rl_room(std::string name, int width, int height, std::vector<char> map) : 
	name(name), width(width), height(height), map(map) 
{

}

rl_room::rl_room(sol::table &room)
{
	auto log = spdlog::get("console");
	name = room.get<std::string>("name");
	width = room.get<int>("width");
	height = room.get<int>("height");
	sol::table plan = room.get<sol::table>("plan");
	map.resize(height * width);
	log->info(height * width);
	for (int j = 1; j <= plan.size(); j++)
	{
		std::string line = plan.get<std::string>(j);
		for (int k = 0; k < width; k++)
		{
			log->info(k*width + j - 1);
			map[k * width + j - 1] = line[k];
		}
	}
}

Data::Data()
{

}

Data::~Data()
{
	for (auto room : m_rooms)
	{
		delete room;
	}
}

bool Data::init_rooms(sol::table table)
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
		rl_room* rm = new rl_room(room);
		m_rooms.push_back(rm);
	}
	return true;
}

bool Data::init_data(sol::table table)
{
	return false;
}

void Data::print_room(int idx)
{
	rl_room* room = m_rooms[idx];
	for (int i = 0; i < room->width; i++)
	{
		for (int j = 0; j < room->height; j++)
			std::cout << room->map[i*room->width + j];
		std::cout << "\n";
	}
}
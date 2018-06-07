#ifndef DATA_H
#define DATA_H

#include "top-level.h"

#include "sol.hpp"
#include <vector>
#include <string>

#include "u-util.h"

struct rl_room {
	std::string name;
	int width;
	int height;
	std::vector<char> map;
	rl_room(std::string name, int width, int height, std::vector<char> map);
	rl_room(sol::table &room);
};




class Data {
public:
	Data();
	~Data();
	bool init_rooms(sol::table table);
	bool init_data(sol::table table);
	void print_room(int idx);
private:
	std::vector<rl_room*> m_rooms;
};

#endif

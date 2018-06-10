#ifndef U_FILE_H
#define U_FILE_H
#include "top-level.hpp"

#include <fstream>
#include <string>
#include <variant>
#include <vector>

class rl_file {
public:
	rl_file(std::string file);
	std::string get_path();
	bool empty();
private:
	std::string m_path;
	bool m_empty = false;
};

class rl_dir {
public:
	rl_dir(std::string dir);
	std::vector<std::variant<rl_file, rl_dir>> list_dir();
	std::string get_path();
private:
	std::vector<std::variant<rl_file, rl_dir>> m_entry;
	std::string m_path;
};

std::string convert_to_system_path(std::string);
#endif
#include "u-file.hpp"

#include <regex>

rl_dir::rl_dir(std::string dir)
{
	m_path = dir;
	m_entry.push_back(rl_file("NULL"));
}
#if !defined(HAVE_DIRENT) && !defined(HAVE_WINDOWS)
#error No Way of reading directories
#endif

#if defined(HAVE_DIRENT) && !defined(HAVE_WINDOWS)
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
std::vector<std::variant<rl_file, rl_dir>> rl_dir::list_dir()
{
	auto val = std::get_if<rl_file>(&m_entry[0]);
	if (val)
	{
		auto dir = std::get_if<rl_dir>(&m_entry[0]);
		if (dir)
			return m_entry;
		if (!val->empty())
			return m_entry;
	}
	m_entry.clear();
	DIR* dirp = opendir(m_path.c_str());
	struct dirent *dp;
	struct stat path_stat;
	while ((dp = readdir(dirp)) != NULL) {
		stat((m_path + "/" + dp->d_name).c_str(), &path_stat);
		if (S_ISREG(path_stat.st_mode))
			m_entry.push_back(rl_file(m_path + "/" + dp->d_name));
		if (S_ISDIR(path_stat.st_mode))
			m_entry.push_back(rl_dir(m_path + "/" + dp->d_name));
	}
	return m_entry;
}
#endif

#if defined(HAVE_WINDOWS)
#include <Windows.h>
std::vector<std::variant<rl_file, rl_dir>> rl_dir::list_dir()
{
	auto val = std::get_if<rl_file>(&m_entry[0]);
	if (val)
	{
		auto dir = std::get_if<rl_dir>(&m_entry[0]);
		if (dir)
			return m_entry;
		if (!val->empty())
			return m_entry;
	}
	m_entry.clear();
	WIN32_FIND_DATA data;
	std::string path = convert_to_system_path(m_path) + "\\*";

	HANDLE hFind = FindFirstFile(path.c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				m_entry.push_back(rl_dir(m_path + "/" + data.cFileName));
			}
			else
			{
				m_entry.push_back(rl_file(m_path + "/" + data.cFileName));
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	return m_entry;
}
#endif

std::string rl_dir::get_path()
{
	return m_path;
}

rl_file::rl_file(std::string file)
{
	if (file == "NULL")
		m_empty = true;
	m_path = file;
}

bool rl_file::empty()
{
	return m_empty;
}

std::string rl_file::get_path()
{
	return m_path;
}


std::string convert_to_system_path(std::string path)
{
#if defined(Windows) && !defined(Linux)
	std::replace(path.begin(), path.end(), '/', '\\');
	return path;
#elif defined(Linux) && !defined(Windows)
	return path;
#endif
}
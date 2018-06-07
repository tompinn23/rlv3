#include "u-file.h"

rl_dir::rl_dir(std::string dir)
{
	m_path = dir;
	m_entry.push_back(rl_file("NULL"));
}
#if defined(HAVE_DIRENT) && !defined(HAVE_WINDOWS)
std::vector<std::variant<rl_file, rl_dir>> rl_dir::list_dir()
{
	return std::vector<std::variant<rl_file, rl_dir>>();
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
	HANDLE hFind = FindFirstFile((m_path + "\\*").c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				m_entry.push_back(rl_dir(m_path + "\\" + data.cFileName));
			}
			if (data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
			{
				m_entry.push_back(rl_file(m_path + "\\" + data.cFileName));
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

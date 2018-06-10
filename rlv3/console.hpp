#ifndef  CONSOLE_H
#define CONSOLE_H
#include "top-level.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace terminal {

typedef uint32_t color_t;


struct char_t {
	char_t(char a_character, color_t a_bk_color, color_t a_fg_color);
	char_t();
	char character;
	color_t bk_color;
	color_t fg_color;
};

typedef std::vector<std::vector<char_t>> console_array;

class Console {
public:
	Console();
	Console(int width, int height);
	Console(int width, int height, color_t bk);
	Console(int width, int height, color_t bk, color_t fg);
	~Console();

	void blit(int destX, int destY, int destX2, int destY2);
	void put(int x, int y, char val);
	void put(int x, int y, char val, color_t bk, color_t fg);
	void put(int x, int y, char val, color_t fg);
	void print(int x, int y, std::string val);
	void bkcolor(color_t bk);
	void color(color_t fg);
	char_t get(int x, int y);
private:
	int m_width;
	int m_height;
	color_t m_bk;
	color_t m_fg;
	console_array m_console;

	void init(int width, int height, color_t bk, color_t fg);
	char_t at(int x, int y);
	bool set(int x, int y, char_t val);
};



	void open();
	int set(std::string val);
	void refresh();
	color_t get_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
	void put(int x, int y, char val);
	void print(int x, int y, std::string val);
	int has_input();
	int read();
	color_t read_str(int x, int y, std::string &buffer, int max);
	int state(int slot);
	void delay(int period);
}


#endif // ! CONSOLE_H


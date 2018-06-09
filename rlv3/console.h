#ifndef  CONSOLE_H
#define CONSOLE_H
#include "top-level.h"

#include <cstdint>

typedef uint32_t color_t;

struct char_t {
	char_t(char a_character, color_t a_bk_color, color_t a_fg_color);
	char character;
	color_t bk_color;
	color_t fg_color;
};

class Console {
public:
	Console(int width, int height);
	Console(int width, int height, color_t bk);
	void blit(int destX, int destY);
	bool put(int x, int y, char val);
private:
	int m_width;
	int m_height;
	char_t* m_console;

	char_t at(int x, int y);
	bool set(int x, int y, char_t val);
};

namespace terminal {
	void refresh();
	color_t get_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
}


#endif // ! CONSOLE_H


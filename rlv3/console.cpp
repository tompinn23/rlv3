#include "console.h"

#include "BearLibTerminal.h"

char_t::char_t(char a_character, color_t a_bk_color, color_t a_fg_color)
{
	character = a_character;
	bk_color = a_bk_color;
	fg_color = a_fg_color;
}


Console::Console(int width, int height) : m_width(width), m_height(height)
{

}

void Console::blit(int destX, int destY)
{
	for(int i = destX; i < m_width; i++)
	{
		for(int j = destY; j < m_height; j++)
		{
			char_t c = at(i, j);
			terminal_bkcolor(c.bk_color);
			terminal_color(c.fg_color);
			terminal_put(i, j, c.character);
		}
	}
	terminal_refresh();
}



inline char_t Console::at(int x, int y)
{
	if(x < 0 || y < 0)
		return char_t(' ', 0xFF000000, 0xFF000000);
	if(x >= m_width || y >= m_height)
		return char_t(' ', 0xFF000000, 0xFF000000);
	return m_console[x * m_height + y];
}

bool Console::set(int x, int y, char_t val)
{
	if(x < 0 || y < 0)
		return false;
	if(x >= m_width || y >= m_height)
		return false;
	m_console[x * m_height + y] = val;
	return true;
}

bool Console::put(int x, int y, char val)
{
	return true;
}






namespace terminal {
	inline void refresh()
	{
		terminal_refresh();
	}

	inline color_t get_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
		return color_from_argb(a, r, g, b);
	}
}


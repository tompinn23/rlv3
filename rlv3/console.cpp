#include "console.h"

#include "BearLibTerminal.h"

Console::Console(int width, int height) : m_width(width), m_height(height)
{

}


char_t Console::at(int x, int y)
{

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


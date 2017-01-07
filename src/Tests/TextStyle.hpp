#ifndef TEXTSTYLE_H
#define TEXTSTYLE_H

/*

атрибуты
0	нормальный режим
1	жирный
4	подчеркнутый
5	мигающий
7	инвертированные цвета
8	невидимый
цвет текста
30	черный
31	красный
32	зеленый
33	желтый
34	синий
35	пурпурный
36	голубой
37	белый
цвет фона
40	черный
41	красный
42	зеленый
43	желтый
44	синий
45	пурпурный
46	голубой
47	белый
 */

#include <stdint.h>

#if !defined(_WIN32) && (defined(__unix__) \
	|| defined(__unix) || (defined(__APPLE__) \
	&& defined(__MACH__)))

#include <iostream>

#	define TEXT_NULL      "\033[0m"
#	define TEXT_BOLD      "\033[1m"
#	define TEXT_MIDDLE    "\033[2m"
#	define TEXT_LIGHT     "\033[3m"
#	define TEXT_UNDERLINE "\033[4m"
#	define TEXT_BINK      "\033[5m"
#	define TEXT_INVERT    "\033[7m"
#	define TEXT_INVISIBLE "\033[8m"

#	define TEXT_BLACK  "\033[30m"
#	define TEXT_RED    "\033[31m"
#	define TEXT_GREEN  "\033[32m"
#	define TEXT_YELLOW "\033[33m"
#	define TEXT_BLUE   "\033[34m"
#	define TEXT_VIOLET "\033[35m"
#	define TEXT_CYAN   "\033[36m"
#	define TEXT_WHITE  "\033[37m"

#	define TEXT_BACKGROUND_BLACK  "\033[40m"
#	define TEXT_BACKGROUND_RED    "\033[41m"
#	define TEXT_BACKGROUND_GREEN  "\033[42m"
#	define TEXT_BACKGROUND_YELLOW "\033[43m"
#	define TEXT_BACKGROUND_BLUE   "\033[44m"
#	define TEXT_BACKGROUND_VIOLET "\033[45m"
#	define TEXT_BACKGROUND_CYAN   "\033[46m"
#	define TEXT_BACKGROUND_WHITE  "\033[47m"

inline void setConsoleText(const char *textColor, const char *backgroundColor) noexcept
{
	std::cout << textColor << backgroundColor;
}

#else

#include <windows.h>

enum class TextColor: uint8_t
{
	BLACK  = 0u,
	RED    = 12u,
	GREEN  = 10u,
	YELLOW = 14u,
	BLUE   = 1u,
	VIOLET = 13u,
	CYAN   = 11u,
	WHITE  = 15u
};

enum class BackgroundColor: uint8_t
{
	BLACK  = 0u,
	RED    = 12u,
	GREEN  = 10u,
	YELLOW = 14u,
	BLUE   = 1u,
	VIOLET = 13u,
	CYAN   = 11u,
	WHITE  = 15u

};

#	define TEXT_BLACK  TextColor::BLACK
#	define TEXT_RED    TextColor::RED
#	define TEXT_GREEN  TextColor::GREEN
#	define TEXT_YELLOW TextColor::YELLOW
#	define TEXT_BLUE   TextColor::BLUE
#	define TEXT_VIOLET TextColor::VIOLET
#	define TEXT_CYAN   TextColor::CYAN
#	define TEXT_WHITE  TextColor::WHITE

#	define TEXT_BACKGROUND_BLACK  BackgroundColor::BLACK
#	define TEXT_BACKGROUND_RED    BackgroundColor::RED
#	define TEXT_BACKGROUND_GREEN  BackgroundColor::GREEN
#	define TEXT_BACKGROUND_YELLOW BackgroundColor::YELLOW
#	define TEXT_BACKGROUND_BLUE   BackgroundColor::BLUE
#	define TEXT_BACKGROUND_VIOLET BackgroundColor::VIOLET
#	define TEXT_BACKGROUND_CYAN   BackgroundColor::CYAN
#	define TEXT_BACKGROUND_WHITE  BackgroundColor::WHITE

inline void setConsoleText(TextColor textColor, BackgroundColor backgroundColor) noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			(static_cast<uint8_t>(backgroundColor) << 8) + static_cast<uint8_t>(textColor));
}

#endif

#endif // TEXTSTYLE_H

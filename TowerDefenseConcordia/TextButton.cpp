#include "TextButton.hpp"

namespace TDC
{
	std::unique_ptr<sf::Font> TextButton::_font = nullptr;
	std::once_flag TextButton::_flag;
}
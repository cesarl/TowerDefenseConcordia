#pragma once

#include "Message.hpp"
#include "Cell.hpp"

#include <SFML/System/Vector2.hpp>

namespace TDC
{
	namespace MapMsg
	{
		struct Resize : Message<Resize>
		{
			Resize(const sf::Vector2u &_size)
				: size(_size)
			{}

			sf::Vector2u size;
		};

		struct DrawMapArray : Message<DrawMapArray>
		{
			DrawMapArray(const std::vector<Cell> *_array)
				: array(_array)
			{}

			const std::vector<Cell> *array;
		};
	}
}
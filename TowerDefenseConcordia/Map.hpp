#pragma once

#include "Cell.hpp"
#include <vector>

namespace TDC
{
	class Map
	{
		std::vector<Cell> _array;
		std::size_t _width;
		std::size_t _height;
	public:
		Map();
		~Map();
		Map(const Map &o) = delete;
		Map(Map &&o) = delete;
		Map &operator=(const Map &o) = delete;
		Map &operator=(Map &&o) = delete;

		void init(std::size_t width, std::size_t height);
		void generate();
		void fill(const CellType &type);
		void reset();
	};
}
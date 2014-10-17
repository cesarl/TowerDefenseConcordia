#include "Map.hpp"

namespace TDC
{
	Map::Map()
		: _width(INVALID)
		, _height(INVALID)
		, _start(0)
		, _end(0)
	{}

	Map::~Map()
	{}

	Cell* Map::getCell(std::size_t x, std::size_t y)
	{
		if (x >= _width || y >= _height || !_valid())
			return nullptr;
		return &_array[x + y * _width];
	}

	Cell *Map::getCell(std::size_t index)
	{
		if (index >= _array.size() || !_valid())
			return nullptr;
		return &_array[index];
	}

	void Map::init(std::size_t width, std::size_t height)
	{
		_width = width;
		_height = height;
	}

	void Map::setStart(std::size_t y)
	{
		_start = y;
	}

	void Map::setEnd(std::size_t y)
	{
		_end = y;
	}

	bool Map::generate(PathGenerationOption option)
	{
		if (!_valid())
			return false;
		_array.resize(_width * _height);
		fill(CellType::Wall);
		if (option == PathGenerationOption::Straight)
		{
			std::size_t y = _start;
			std::size_t past = _start * _width;
			for (std::size_t x = 0; x < _width; ++x)
			{
				std::size_t index = x + y * _width;
				_array[index].setType(CellType::Path);
				if (index != past)
					_array[past].setNext(index);
				past = index;
				if (y != _end)
				{
					if (y < _end)
					{
						index = x + ++y * _width;
						_array[index].setType(CellType::Path);
						if (index != past)
							_array[past].setNext(index);
						past = index;
					}
					else
					{
						index = x + --y * _width;
						_array[index].setType(CellType::Path);
						if (index != past)
							_array[past].setNext(index);
						past = index;
					}
				}
			}
		}
	}

	void Map::fill(const CellType &type)
	{
		if (_valid())
			return;
		std::size_t index = 0;
		for (auto &e : _array)
		{
			e.setType(type);
			e.setNext(INVALID);
			e.setIndex(index++);
		}
	}

	bool Map::verify()
	{
		if (!_valid())
			return false;
		if (!getCell(0, _start)->hasNext())
			return false;
		auto cell = getCell(getCell(0, _start)->getNext());
		auto end = getCell(_end);
		while (cell != end)
		{
			if (!cell->hasNext())
				return false;
			cell = getCell(cell->getNext());
		}
		return true;
	}
}
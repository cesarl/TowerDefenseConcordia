#pragma once

#include "Cell.hpp"
#include <vector>
#include <cereal/types/vector.hpp>

namespace TDC
{

	enum PathGenerationOption : bool
	{
		Straight = 0
		, None = 1
	};

	class Map
	{
		std::vector<Cell> _array;
		std::size_t _width;
		std::size_t _height;
		std::size_t _start;
		std::size_t _end;

		bool _valid() const { return (_width != INVALID && _height != INVALID && _start < _height && _end < _height); }
	public:
		Map();
		~Map();
		Map(const Map &o) = delete;
		Map(Map &&o) = delete;
		Map &operator=(const Map &o) = delete;
		Map &operator=(Map &&o) = delete;

		Cell *getCell(std::size_t x, std::size_t y);
		Cell *getCell(std::size_t index);

		void init(std::size_t width, std::size_t height);
		void setStart(std::size_t y);
		void setEnd(std::size_t y);
		bool generate(PathGenerationOption option);
		void fill(const CellType &type);
		bool verify();
		void reset();

		template < typename Archive >
		void serialize(Archive &ar)
		{
			ar(cereal::make_nvp("Width", _width)
				, cereal::make_nvp("Height", _height)
				, cereal::make_nvp("Start", _start)
				, cereal::make_nvp("End", _end)
				, cereal::make_nvp("Array", _array)
				);
		}

		// Used to debug
		bool saveToJson(const std::string &fileName) const;

		// Used at release time
		bool saveToBinary(const std::string &fileName) const;

		bool loadFromJson(const std::string &filename);
		bool loadFromBinary(const std::string &filename);
	};
}
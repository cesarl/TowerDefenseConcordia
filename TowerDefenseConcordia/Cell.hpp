#pragma once

#include <cstddef>

namespace TDC
{
	class Map;

	enum CellType : bool
	{
		Wall = 0
		, Path
	}; 

	class Cell
	{
		friend class Map;

		CellType _type;
		std::size_t _index;
		std::size_t _next;
	public:
		Cell();
		~Cell();
		Cell(const Cell &o);
		Cell(Cell &&o);
		Cell &operator=(const Cell &o);
		Cell &operator=(Cell &&o);

		inline const CellType &getType() const { return _type; }
		inline bool isType(const CellType &t) const { return t == _type; }
		inline void setType(const CellType &t) { _type = t; }

		inline std::size_t getIndex() const { return _index; }
		inline bool hasNext() const { return std::size_t(-1) != _next; }
		inline std::size_t getNext() const { return _next; }
	};
}
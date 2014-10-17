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

#define INVALID ((std::size_t)(-1))

	class Cell
	{
		friend class Map;

		CellType _type;
		std::size_t _index;
		std::size_t _next;

		inline void setNext(std::size_t n) { _next = n; }
		inline void setIndex(std::size_t i) { _index = i; }
		inline void setType(const CellType &t) { _type = t; }
	public:
		Cell();
		~Cell();
		Cell(const Cell &o);
		Cell(Cell &&o);
		Cell &operator=(const Cell &o);
		Cell &operator=(Cell &&o);

		inline const CellType &getType() const { return _type; }
		inline bool isType(const CellType &t) const { return t == _type; }

		inline std::size_t getIndex() const { return _index; }
		inline bool hasNext() const { return std::size_t(-1) != _next; }
		inline std::size_t getNext() const { return _next; }
	};
}
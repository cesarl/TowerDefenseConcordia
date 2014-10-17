#include "Map.hpp"
#include <cassert>

int main(void)
{
	TDC::Map map;

	map.init(1024, 512);
	map.setStart(123);
	map.setEnd(500);
	assert(map.generate(TDC::PathGenerationOption::Straight));
	assert(map.verify());
	assert(map.saveToBinary("testMapBinary.bin"));
	assert(map.loadFromBinary("testMapBinary.bin"));
	assert(map.verify());
	map.init(512, 1024);
	map.setStart(0);
	map.setEnd(1023);
	assert(map.generate(TDC::PathGenerationOption::None));
	assert(map.verify() == false); // should be false
	assert(map.generate(TDC::PathGenerationOption::Straight));
	assert(map.verify());
	assert(map.saveToJson("testMapBinary.json"));
	assert(map.loadFromJson("testMapBinary.json"));
	assert(map.verify());
}
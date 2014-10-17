#include "Map.hpp"

int main(void)
{
	TDC::Map map;

	map.init(1024, 512);
	auto res = map.generate(TDC::PathGenerationOption::Straight);
	auto ver = map.verify();
}
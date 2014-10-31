
#include "Game.hpp"

#include <cassert>

int main(void)
{
	//// map creation
	//TDC::Map map;

	//// map configuration
	//map.config(100, 50, 3, 40);

	//// map generation
	//assert(map.generate(TDC::PathGenerationOption::Straight));

	//// map verification to binary
	//assert(map.verify());

	//// map serialization
	//assert(map.saveToBinary("testMapBinary.bin"));

	//// map load
	//assert(map.loadFromBinary("testMapBinary.bin"));

	//// map verification
	//assert(map.verify());

	//// debug print to file
	//map.printToFile("testMapPrinted1.txt");

	////---------------------

	//// map configuration
	//map.config(50, 200, 0, 199);

	//// map generation empty
	//assert(map.generate(TDC::PathGenerationOption::None));

	//// map verification
	//assert(map.verify() == false); // should be false

	//// map generation
	//assert(map.generate(TDC::PathGenerationOption::Straight));

	//// map verification
	//assert(map.verify());

	//// map serialization to json
	//assert(map.saveToJson("testMapBinary.json"));

	//// map load
	//assert(map.loadFromJson("testMapBinary.json"));

	//// map verification
	//assert(map.verify());

	//// debug print to file
	//map.printToFile("testMapPrinted2.txt");

	//TDC::Subscriber subscriber1;
	//TDC::Subscriber subscriber2;

	//TDC::Publisher publisher;

	//subscriber1.subcribeToMessage<TDC::MessageTest>([&](const TDC::IMessage *msg)
	//{
	//	std::cout << "Subscriber 1 " << static_cast<const TDC::MessageTest*>(msg)->value << std::endl;
	//});

	//subscriber2.subcribeToMessage<TDC::MessageTest>([&](const TDC::IMessage *msg)
	//{
	//	std::cout << "Subscriber 2 " << static_cast<const TDC::MessageTest*>(msg)->value << std::endl;
	//});

	//publisher.addSubscriber(subscriber1.getHandle());
	//publisher.addSubscriber(subscriber2.getHandle());

	//for (auto i = 0; i < 20; i += 2)
	//	publisher.publish<TDC::MessageTest>(i);

	TDC::Game game;
	game.init();
	game.generate();
	game.launch();
}
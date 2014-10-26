#pragma once

#include "WindowManager.hpp"
#include "Map.hpp"
#include "Message.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace TDC
{
	class Game : public WindowManager, public PubSub
	{
	public:
		//message
		struct Event : Message<Event>
		{
			sf::Event event;
			Event(const sf::Event &e)
				: event(e)
			{}
		};


		Game()
		{}

		virtual ~Game()
		{}

		virtual void init()
		{
			WindowManager::init();
			_map.addSubscriber(getHandle());
			addSubscriber(_map.getHandle());
			_map.config(50, 50, 8, 40);
			_map.generate(TDC::PathGenerationOption::Straight);
		}

	protected:
		virtual void _updateEvents(const sf::Event &event)
		{
			publish<Event>(event);
		}

		virtual void _update(const sf::Time dt)
		{
			auto &mapArray = _map.getArray();
			auto w = _map.getWidth();
			auto h = _map.getHeight();

			auto ratio = _window.getSize().x / w;
			ratio = _window.getSize().y / h < ratio ? _window.getSize().y / h : ratio;

			sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color(150, 50, 250));
			rectangle.setSize(sf::Vector2f(ratio, ratio));


			for (std::size_t i = 0; i < mapArray.size(); ++i)
			{
				auto &e = mapArray[i];
				if (e.getType() == CellType::Wall)
				{
					rectangle.setPosition((i % w) * ratio, (i / w) * ratio);
					_window.draw(rectangle);
				}
			}
		}
	private:
		Map _map;
	};
}
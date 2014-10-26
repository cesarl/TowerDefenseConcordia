#pragma once

#include "WindowManager.hpp"
#include "Map.hpp"
#include "Message.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "MapMessages.hpp"

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

			subcribeToMessage<MapMsg::Resize>([this](const IMessage *msg)
			{
				computeCellSizeRatio();
			});

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

			sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color(150, 50, 250));
			rectangle.setSize(sf::Vector2f(_cellSizeRatio, _cellSizeRatio));


			for (std::size_t i = 0; i < mapArray.size(); ++i)
			{
				auto &e = mapArray[i];
				if (e.getType() == CellType::Wall)
				{
					rectangle.setPosition((i % w) * _cellSizeRatio, (i / w) * _cellSizeRatio);
					_window.draw(rectangle);
				}
			}
		}
	private:

		void computeCellSizeRatio()
		{
			auto w = _map.getWidth();
			auto h = _map.getHeight();

			_cellSizeRatio = _window.getSize().x / w;
			_cellSizeRatio = _window.getSize().y / h < _cellSizeRatio ? _window.getSize().y / h : _cellSizeRatio;
			_map.setCellSizeRatio(_cellSizeRatio);
		}

		Map _map;
		std::size_t _cellSizeRatio;
	};
}
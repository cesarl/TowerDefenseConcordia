#pragma once

#include "WindowManager.hpp"
#include "Map.hpp"
#include "Message.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "MapMessages.hpp"
#include "Critter.hpp"
#include "LaunchModeBehaviour.hpp"
#include <memory>

namespace TDC
{
	class Game : public WindowManager, public PubSub
	{
	public:
		Game()
		{}

		virtual ~Game()
		{}

		void setPlayMode(const std::string &mapFilePath)
		{
		}

		void setEditionMode()
		{}

		void setLaunchMode()
		{
			if (_mode)
			{
				removeSubscriber(_mode->getHandle());
				_mode->removeSubscriber(getHandle());
			}
			_mode = std::make_unique<LaunchModeBehaviour>();
			addSubscriber(_mode->getHandle());
			_mode->addSubscriber(getHandle());
			_mode->init();
		}

		virtual void init()
		{
			WindowManager::init();
			_map.addSubscriber(getHandle());
			addSubscriber(_map.getHandle());

			subcribeToMessage<Msg::Resize>([this](const IMessage *msg)
			{
				computeCellSizeRatio();
			});

			_arial.loadFromFile("../assets/arial.ttf");
		}

		void generate()
		{
			auto w = rand() % 100 + 10;
			auto h = rand() % 100 + 10;
			_map.config(w, h, rand() % (h - 1), rand() % (h - 1));
			_map.generate(TDC::PathGenerationOption::Straight);
			_critters.clear();
		}

	protected:
		virtual void _updateEvents(const sf::Event &event)
		{
			publish<Msg::Event>(event);

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					_critters.emplace_back<Critter>(Critter::CritterType::Type1);
					_critters.back().addSubscriber(_map.getHandle());
					_critters.back().init();
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					_critters.emplace_back<Critter>(Critter::CritterType::Type2);
					_critters.back().addSubscriber(_map.getHandle());
					_critters.back().init();
				}
				else if (event.key.code == sf::Keyboard::G)
				{
					generate();
				}
			}
			else if (event.type == sf::Event::Resized)
			{
				publish<Msg::Resize>(_window.getSize());
			}
		}

		virtual void _update(const sf::Time dt)
		{
//			auto &mapArray = _map.getArray();
//			auto w = _map.getWidth();
//			auto h = _map.getHeight();
//
//			sf::RectangleShape rectangle;
//			rectangle.setFillColor(sf::Color(150, 50, 250));
//			rectangle.setSize(sf::Vector2f(_cellSizeRatio, _cellSizeRatio));
//
//			sf::CircleShape circle;
//			circle.setRadius(_cellSizeRatio / 2.0f);
//
//			for (std::size_t i = 0; i < mapArray.size(); ++i)
//			{
//				auto &e = mapArray[i];
//				if (e.getType() == CellType::Wall)
//				{
//					rectangle.setPosition((i % w) * _cellSizeRatio, (i / w) * _cellSizeRatio);
//					_window.draw(rectangle);
//				}
//			}
//
//			for (std::size_t i = 0; i < _critters.size(); ++i)
//			{
//				if (!_critters[i].update(dt))
//				{
//					if (i < _critters.size() - 1)
//					{
//						std::swap(_critters.at(i), _critters.at(_critters.size() - 1));
//						_critters.pop_back();
//						--i;
//					}
//					else
//						_critters.pop_back();
//				}
//				else
//				{
//					circle.setFillColor(_critters[i].getColor());
//
//					auto &c = _critters[i];
//					auto from = c.getCurrentCell();
//					auto to = c.getDestinationCell();
//					auto ratio = c.getCellStage();
//					int dif = (int)to - (int)from;
//					float r = _cellSizeRatio * ratio;
//					if (dif < 0)
//						r *= -1.0f;
//
//					if (std::abs(dif) > 1) // vertical move
//					{
//						auto x = (from % _map.getWidth()) * 1.0f * _cellSizeRatio;
//						auto y = (from / _map.getWidth()) * 1.0f * _cellSizeRatio + r;
//						circle.setPosition({ x, y });
//					}
//					else // horizontal move
//					{
//						auto x = (from % _map.getWidth()) * 1.0f * _cellSizeRatio + r;
//						auto y = (from / _map.getWidth()) * 1.0f * _cellSizeRatio;
//						circle.setPosition({ x, y });
//					}
//
//					_window.draw(circle);
//				}
//			}
//
//			sf::Text text("Key 1 to create a critter of type 1.\n\
//Key 2 to create a critter of type 2.\n\
//Key G to generate a new map.", _arial, 20);
//			text.setColor(sf::Color::Red);
//			_window.draw(text);
			if (_mode)
			{
				_mode->update(dt, &_window);
			}
		}
	private:

		void computeCellSizeRatio()
		{
			auto w = _map.getWidth();
			auto h = _map.getHeight();

			_cellSizeRatio = _window.getSize().x / w;
			_cellSizeRatio = _window.getSize().y / h < _cellSizeRatio ? _window.getSize().y / h : _cellSizeRatio;
			_window.setView(sf::View(sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y)));
			_map.setCellSizeRatio(_cellSizeRatio);
		}

		Map _map;
		std::size_t _cellSizeRatio;
		sf::Font _arial;
		std::vector < Critter > _critters;
		std::unique_ptr < IModeBehaviour > _mode;
	};
}
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace TDC
{
	class WindowManager
	{
	public:
		WindowManager()
		{}

		~WindowManager()
		{}

		virtual void init()
		{
			_window.create(sf::VideoMode(800, 600), "Concordia Tower Defense");
			_window.setFramerateLimit(60);
		}

		void setSize(const sf::Vector2u &size)
		{
			_window.setSize(size);
		}

		const sf::Vector2u &getSize() const
		{
			return _window.getSize();
		}

		void launch()
		{
			sf::Clock clock;
			while (_window.isOpen())
			{
				sf::Time elapsed = clock.restart();
				sf::Event windowEvent;

				_window.clear(sf::Color::Black);
				_update(elapsed);

				while (_window.pollEvent(windowEvent))
				{
					_updateEvents(windowEvent);
					if (windowEvent.type == sf::Event::Closed)
					{
						_window.close();
					}
				}
				_window.display();
			}
		}

	protected:
		virtual void _updateEvents(const sf::Event &event) = 0;
		virtual void _update(const sf::Time dt) = 0;
		sf::RenderWindow _window;
	};
}
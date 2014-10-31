#pragma once

#include "IModeBehaviour.hpp"
#include "MapMessages.hpp"
#include <iostream>

namespace TDC
{
	class LaunchModeBehaviour : public IModeBehaviour
	{
	public:
		virtual void init()
		{
			_arial.loadFromFile("../assets/arial.ttf");

			subcribeToMessage<Msg::Event>([&](const IMessage *msg)
			{
				auto m = static_cast<const Msg::Event*>(msg);

				if (m->event.type == sf::Event::MouseButtonPressed && m->event.mouseButton.button == sf::Mouse::Left)
				{
					if (m->event.mouseButton.x >= _playBtn.getPosition().x
						&& m->event.mouseButton.x <= _playBtn.getPosition().x + _playBtn.getSize().x
						&& m->event.mouseButton.y >= _playBtn.getPosition().y
						&& m->event.mouseButton.y <= _playBtn.getPosition().y + _playBtn.getSize().y)
					{
						std::cout << "Play !!!!" << std::endl;
					}
					else if (m->event.mouseButton.x >= _editBtn.getPosition().x
						&& m->event.mouseButton.x <= _editBtn.getPosition().x + _playBtn.getSize().x
						&& m->event.mouseButton.y >= _editBtn.getPosition().y
						&& m->event.mouseButton.y <= _editBtn.getPosition().y + _playBtn.getSize().y)
					{
						std::cout << "Edit !!!!" << std::endl;
					}

				}
			});

			_playBtn.setSize({ 300, 200 });
			_playBtn.setFillColor(sf::Color::Green);
			_playBtn.setPosition(300, 200);
			_playTxt.setString("Play !");
			_playTxt.setFont(_arial);
			_playTxt.setCharacterSize(20);
			_playTxt.setColor(sf::Color::Black);
			_playTxt.setPosition(300, 200);

		}

		virtual void update(const sf::Time &dt, sf::RenderWindow *renderWindow)
		{
			renderWindow->draw(_playBtn);
			renderWindow->draw(_playTxt);
		}

		virtual ~LaunchModeBehaviour()
		{}
	private:
		sf::Font _arial;
		sf::RectangleShape _playBtn;
		sf::RectangleShape _editBtn;
		sf::Text _playTxt;
		sf::Text _editTxt;
	};
}
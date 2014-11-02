#pragma once

#include "IModeBehaviour.hpp"
#include "MapMessages.hpp"
#include <iostream>
#include "TextButton.hpp"

namespace TDC
{
	class LaunchModeBehaviour : public IModeBehaviour
	{
	public:
		virtual void init()
		{
			subcribeToMessage<Msg::Resize>([this](const IMessage *msg)
			{
				publish<Msg::Resize>(*static_cast<const Msg::Resize*>(msg));
			});

			subcribeToMessage<Msg::Event>([this](const IMessage *msg)
			{
				publish<Msg::Event>(*static_cast<const Msg::Event*>(msg));
			});

			_play = std::make_unique<TextButton>(
				sf::Vector2u(50, 33)
				, sf::Vector2u(50, 33)
				, "Play !"
				, sf::Color::Blue
				, sf::Color::Green
				, 20 );
			_play->init();
			addSubscriber(_play->getHandle());

			_play->setOnClickCallback([&](){
				this->publish<Msg::PlayMode>(Msg::PlayMode::Mode::Play, "");
			});


			_edit = std::make_unique<TextButton>(
				sf::Vector2u(50, 66)
				, sf::Vector2u(50, 33)
				, "Edit !"
				, sf::Color::Red
				, sf::Color::Yellow
				, 20);
			_edit->init();
			addSubscriber(_edit->getHandle());

			_edit->setOnClickCallback([&](){
				this->publish<Msg::PlayMode>(Msg::PlayMode::Mode::EditMap, "");
			});

		}

		virtual void update(const sf::Time &dt, sf::RenderWindow *renderWindow)
		{
			_play->update(dt, renderWindow);
			_edit->update(dt, renderWindow);
		}

		virtual ~LaunchModeBehaviour()
		{}
	private:
		std::unique_ptr<TextButton> _play;
		std::unique_ptr<TextButton> _edit;
	};
}
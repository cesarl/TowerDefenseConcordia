#pragma once

#include <sfml/System/Vector2.hpp>
#include "ObserverPattern.hpp"
#include <sfml/Graphics/RenderWindow.hpp>
#include "MapMessages.hpp"

namespace TDC
{
	class IButton : public PubSub
	{
	public:
		IButton(sf::Vector2u position = sf::Vector2u( 0, 0 ) /*percent*/
			, sf::Vector2u dimensions = sf::Vector2u( 0, 0 ) /*percent*/)
			: _position(position)
			, _dimensions(dimensions)
			, _active(true)
			, _dirty(true)
		{
		}

		virtual ~IButton(){}

		inline void setPosition(const sf::Vector2u &position)
		{
			_position = position;
		}

		inline void setDimension(const sf::Vector2u &dimension)
		{
			_dimensions = dimension;
		}

		inline void setActive(bool tof)
		{
			_active = tof;
		}

		void update(const sf::Time &dt, sf::RenderWindow *window)
		{
			if (!_active)
				return;
			_update(dt, window);
		}

		void init()
		{
			subcribeToMessage<Msg::Resize>([&](IMessage *msg)
			{
				auto *m = static_cast <Msg::Resize*>(msg);
				_windowSize = m->size;
				_dirty = true;
				_computeBoundingBox();
			});

			subcribeToMessage<Msg::Event>([&](IMessage *msg)
			{
				auto *m = static_cast <Msg::Event*>(msg);
				if (m->event.type == sf::Event::MouseButtonReleased
					&& isPointIn(m->event.mouseButton.x, m->event.mouseButton.y))
				{
					_onClick();
				}
			});
			_init();
		}

		inline bool isPointIn(int x, int y)
		{
			if (_dirty)
			{				
				_computeBoundingBox();
			}
			return (x >= _bbX.x && x <= _bbX.y && y >= _bbY.x && y <= _bbY.y);
		}

		inline void setOnClickCallback(const std::function<void()> &fn)
		{
			_onClickCallback = fn;
		}
	protected:
		virtual void _update(const sf::Time &dt, sf::RenderWindow *window) = 0;
		virtual void _onClick() = 0;
		virtual void _event(const sf::Event &event) = 0;
		virtual void _init() = 0;
		virtual void _resized() = 0;

		void _computeBoundingBox()
		{
			auto size = _windowSize;
			float w = size.x * (float)_dimensions.x / 100.0f;
			float h = size.y * (float)_dimensions.y / 100.0f;

			_bbX.x = (size.x * (float)_position.x / 100.0f) - (w / 2.0f);
			_bbX.y = _bbX.x + w;
			_bbY.x = (size.y * (float)_position.y / 100.0f) - (h / 2.0f);
			_bbY.y = _bbY.x + h;
			_dirty = false;
			_resized();
		}
		std::function<void()> _onClickCallback;
		sf::Vector2u _position;
		sf::Vector2u _dimensions;
		bool _active;
		bool _dirty;
		sf::Vector2u _bbX;
		sf::Vector2u _bbY;
		sf::Vector2u _windowSize;
	};
}
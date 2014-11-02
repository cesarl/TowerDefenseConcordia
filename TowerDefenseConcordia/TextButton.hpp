#pragma once

#include "IButton.hpp"
#include <sfml/Graphics/RectangleShape.hpp>
#include <sfml/Graphics/Text.hpp>
#include <sfml/Graphics/Font.hpp>
#include <mutex>
#include <assert.h>
#include <memory.h>

namespace TDC
{
	class TextButton : public IButton
	{
	public:
		TextButton(sf::Vector2u position = sf::Vector2u(0, 0) /*percent*/
			, sf::Vector2u dimensions = sf::Vector2u(0, 0) /*percent*/
			, const std::string &text = "Text"
			, const sf::Color &textColor = sf::Color(255, 255, 255, 255)
			, const sf::Color &bgColor = sf::Color(122, 122, 122, 255)
			, std::size_t fontSize = 20)
			: IButton(position, dimensions)
		{
			std::call_once(_flag, [&](){
				_font = std::make_unique<sf::Font>();
				assert(_font->loadFromFile("../assets/arial.ttf"));
			});
			_computeBoundingBox();
			_shape.setPosition(_bbX.x, _bbY.x);
			_shape.setSize(sf::Vector2f(_bbX.y - _bbX.x, _bbY.y - _bbY.x ));
			_shape.setFillColor(bgColor);
			_text.setFont(*_font);
			_text.setCharacterSize(fontSize);
			_text.setPosition(_bbX.x, _bbY.y);
			_text.setColor(textColor);
			_text.setString(text);
		}
	protected:
		virtual void _update(const sf::Time &dt, sf::RenderWindow *window)
		{
			if (window && _active)
			{
				window->draw(_shape);
				window->draw(_text);
			}
		}
		virtual void _onClick()
		{
			if (_onClickCallback)
				_onClickCallback();
		}

		virtual void _event(const sf::Event &event)
		{
		}

		virtual void _init()
		{}

		virtual void _resized()
		{
			_shape.setPosition(_bbX.x, _bbY.x);
			_shape.setSize(sf::Vector2f(_bbX.y - _bbX.x, _bbY.y - _bbY.x));
			_text.setPosition(_bbX.x + (_bbX.y - _bbX.x) / 2.0f - _text.getLocalBounds().width / 2.0f, _bbY.x + (_bbY.y - _bbY.x) / 2.0f - _text.getLocalBounds().height / 2.0f);
//			_text.getLocalBounds();
		}
	private:
		sf::RectangleShape _shape;
		sf::Text _text;
		static std::unique_ptr<sf::Font> _font;
		static std::once_flag _flag;
	};
}
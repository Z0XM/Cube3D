#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "guiEntry.hpp"

namespace gui {
	class Textbox  {
	protected:
		sf::RectangleShape box;
		sf::Text text;
		std::string defaultString;

		void InitVariables(sf::RectangleShape, sf::Text, bool);

	public:
		Textbox();
		Textbox(sf::RectangleShape, sf::Text, bool = true);
		virtual ~Textbox();

		void move(float x, float y);
		void setPosition(const sf::Vector2f&);
		void setBackgroundColor(const sf::Color&);
		void setOutlineColor(const sf::Color&);
		void setOutlineThickness(const float);
		void setTextFillColor(const sf::Color&);
		void setString(const std::string&);
		void setDefaultString(const std::string&);
		sf::Vector2f getPosition() const;
		sf::Color getBackgroundColor() const;
		sf::Color getOutlineColor() const;
		float getOutlineThickness() const;
		sf::Color getTextFillColor() const;
		std::string getString() const;
		std::string getDefaultString() const;
		sf::FloatRect getGlobalBounds() const;
		enum class TextAlign { CENTER, LEFT, RIGHT };
		void alignText(const TextAlign = TextAlign::CENTER);
		void render(sf::RenderTarget&);

		static std::map<std::string, Textbox*> Group;
	};
}
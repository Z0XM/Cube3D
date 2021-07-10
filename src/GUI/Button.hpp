#pragma once

#include "Textbox.hpp"
#include "Clickable.hpp"
#include "guiEntry.hpp"
#include <map>

namespace gui {
	class Button : public Textbox, public Clickable{
	private:
		struct {
			sf::Color backgroundColor;
			sf::Color outlineColor;
			float outlineThickness;
			sf::Color textFillColor;
		} original, highlight;

		void InitVariables();
		void updateHighlight();
	public:
		Button();
		Button(sf::RectangleShape, sf::Text);
		~Button();

		void setPosition(const sf::Vector2f&&);
		void move(float, float);
		void setHighlight(sf::Color, sf::Color, float, sf::Color);
		void changeHighlightOutline(sf::Color, float);
		void changeHighlightBackgroundAndText(sf::Color, sf::Color);
		void updateTheme();
		Clickable* isHit(sf::Vector2f& mousePos);

		static std::map<std::string, Button*> Group;
	};
}

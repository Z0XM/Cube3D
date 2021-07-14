#pragma once

#include "Textbox.hpp"
#include <functional>

namespace gui {
	class Button : public Textbox {
	public:
		Button(const sf::Vector2f& siz = sf::Vector2f(0, 0));
		~Button();

		void setHighlightFillColor(const sf::Color& color);
		void setHighightOutlineColor(const sf::Color& color);
		void setHighlightOutlineThickness(float thickness);

		bool contains(const sf::Vector2f& mousePos) const;

		void setAction(std::function<void()> func);
		void activateHighlight();
		void deactivateHighlight();

		void copyHighlightProperties(const sf::RectangleShape& rect);

		void draw(sf::RenderTarget& target) override;

		std::function<void()> action;
		static Button* mouseHoveringOn;
		static sf::Mouse::Button pressedMouseButton;
		static Button* clicked;

		static Button* create(const sf::Vector2f& size);
		static std::unordered_map<std::string, Button*> Group;

	private:
		sf::RectangleShape highlight;
		enum { HIGHLIGHT, ORIGINAL } state;
	};
}

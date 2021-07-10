#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "guiEntry.hpp"


namespace gui {
	class Clickable {
	private:
		sf::FloatRect clickField;
	protected:
		enum { HIGHLIGHT, ORIGINAL } state;
		
		virtual void updateHighlight() = 0;
		void setClickField(sf::FloatRect rect);
	public:
		Clickable(); 
		virtual ~Clickable();

		virtual void move(float x, float y) = 0;

		sf::FloatRect getClickField();
		bool contains(const sf::Vector2f&) const;
		bool contains(const sf::Vector2f&&) const;
		void setAction(std::function<void()>);
		void activateHighlight();
		void deactivateHighlight();
		virtual Clickable* isHit(sf::Vector2f& mousePos) = 0;

		std::function<void()> action;
		static Clickable* mouseHoveringOn;
		static sf::Mouse::Button pressedMouseButton;
		static Clickable* clicked;
	};
}
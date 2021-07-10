#pragma once

#include "Clickable.hpp"
#include <map>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

namespace gui {
	class Dropitem : public Clickable {
	private:
		sf::RectangleShape box, dropbox;
		sf::Text text;
		Button closeButton;
		unsigned int index;
		struct {
			sf::Color outlineColor;
			float outlineThickness;
		} original, highlight;

		bool isDropboxActive;

		void InitVariables();
		void InitHighlight();
		void InitDropbox();
		void InitCloseButton();

		void updateHighlight();
		void updateDropbox();
		void updateCloseButton();
		void dropDown();

	public:
		Dropitem();
		Dropitem(sf::RectangleShape, sf::Text);
		~Dropitem();

		void move(float x, float y);
		void setPosition(const sf::Vector2f&&);
		void setBackgroundColor(const sf::Color&);
		void setOutlineColor(const sf::Color&);
		void setOutlineThickness(const float);
		void setTextFillColor(const sf::Color&);

		sf::Vector2f getPosition() const;
		sf::Color getBackgroundColor() const;
		sf::Color getOutlineColor() const;
		float getOutlineThickness() const;
		sf::Color getTextFillColor() const;
		Clickable* isHit(sf::Vector2f&);

		void render(sf::RenderTarget&);
		static void makeDropItems(unsigned int count, std::string name, sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int characterSize);
		static void arrangeAllFrom(Dropitem*);
		static void deleteObject(Dropitem*);

		static std::map<std::string, Dropitem*> Group;
		static unsigned int objectCount;
	};
}
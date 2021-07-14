#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace gui {
	class Textbox
	{
	public:
		enum class TextAlign { LEFT, CENTER, RIGHT };

		Textbox(const sf::Vector2f& siz = sf::Vector2f(0,0));
		virtual ~Textbox();

		void setSize(const sf::Vector2f& size);
		const sf::Vector2f& getSize() const;

		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);

		const sf::Color& getFillColor() const;
		const sf::Color& getOutlineColor() const;
		float getOutlineThickness() const;

		sf::FloatRect getGlobalBounds() const;

		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& position);
		const sf::Vector2f& getPosition() const;

		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);

		void setString(const std::string& string);
		const std::string& getString() const;

		void setFont(const sf::Font& font);
		void setCharacterSize(unsigned int size);
		void setLineSpacing(float spacingFactor);
		void setLetterSpacing(float spacingFactor);

		const sf::Font* getFont() const;
		unsigned int getCharacterSize() const;
		float getLetterSpacing() const;
		float getLineSpacing() const;

		void setTextFillColor(const sf::Color& color);
		void setTextOutlineColor(const sf::Color& color);
		void setTextOutlineThickness(float thickness);

		const sf::Color& getTextFillColor() const;
		const sf::Color& getTextOutlineColor() const;
		float getTextOutlineThickness() const;

		void setStyle(sf::Uint32 style);

		void alignText(const TextAlign& = TextAlign::CENTER);

		void copyBoxProperties(const sf::RectangleShape& rect);
		void copyTextProperties(const sf::Text& text);

		void setText(bool hasText);

		virtual void draw(sf::RenderTarget&);

		static Textbox* create(const sf::Vector2f& size);
		static std::unordered_map<std::string, Textbox*> Group;

	protected:
		sf::RectangleShape box;
		sf::Text text;
		bool hasText;

		void updateText();
		TextAlign alignment;
	};
}


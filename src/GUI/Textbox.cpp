#include "Textbox.hpp"

namespace gui {

	std::unordered_map<std::string, Textbox*> Textbox::Group;

	Textbox::Textbox(const sf::Vector2f& size)
		:hasText(true), alignment(TextAlign::CENTER)
	{
		this->setSize(size);
	}

	Textbox::~Textbox()
	{

	}

	void Textbox::updateText()
	{
		text.setPosition(
			box.getPosition().x + (box.getSize().x - text.getGlobalBounds().width) * 0.5f * (int)alignment,
			box.getPosition().y + box.getSize().y * 0.5f - text.getGlobalBounds().height
		);
	}

	void Textbox::setSize(const sf::Vector2f& size)
	{
		box.setSize(size);
	}

	const sf::Vector2f& Textbox::getSize() const
	{
		return box.getSize();
	}

	void Textbox::setFillColor(const sf::Color& color)
	{
		box.setFillColor(color);
	}

	void Textbox::setOutlineColor(const sf::Color& color)
	{
		box.setOutlineColor(color);
	}

	void Textbox::setOutlineThickness(float thickness)
	{
		box.setOutlineThickness(thickness);
	}

	const sf::Color& Textbox::getFillColor() const
	{
		return box.getFillColor();
	}

	const sf::Color& Textbox::getOutlineColor() const
	{
		return box.getOutlineColor();
	}

	float Textbox::getOutlineThickness() const
	{
		return box.getOutlineThickness();
	}

	void Textbox::alignText(const TextAlign& align)
	{
		alignment = align;
		updateText();
	}

	sf::FloatRect Textbox::getGlobalBounds() const
	{
		return box.getGlobalBounds();
	}

	void Textbox::setPosition(float x, float y)
	{
		box.setPosition(x, y);
		updateText();
	}

	void Textbox::setPosition(const sf::Vector2f& position)
	{
		box.setPosition(position.x, position.y);
		updateText();
	}

	const sf::Vector2f& Textbox::getPosition() const
	{
		return box.getPosition();
	}

	void Textbox::move(float offsetX, float offsetY)
	{
		box.move(offsetX, offsetY);
		text.move(offsetX, offsetY);
	}

	void Textbox::move(const sf::Vector2f& offset)
	{
		box.move(offset);
		text.move(offset);
	}

	void Textbox::setString(const std::string& string)
	{
		text.setString(string);
		updateText();
	}

	const std::string& Textbox::getString() const
	{
		return text.getString();
	}

	void Textbox::setFont(const sf::Font& font)
	{
		text.setFont(font);
	}

	void Textbox::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
	}

	void Textbox::setLineSpacing(float spacingFactor)
	{
		text.setLineSpacing(spacingFactor);
	}

	void Textbox::setLetterSpacing(float spacingFactor)
	{
		text.setLetterSpacing(spacingFactor);
	}

	const sf::Font* Textbox::getFont() const
	{
		return text.getFont();
	}

	unsigned int Textbox::getCharacterSize() const
	{
		return text.getCharacterSize();
	}

	float Textbox::getLetterSpacing() const
	{
		return text.getLetterSpacing();
	}

	float Textbox::getLineSpacing() const
	{
		return text.getLineSpacing();
	}

	void Textbox::setTextFillColor(const sf::Color& color)
	{
		text.setFillColor(color);
	}

	void Textbox::setTextOutlineColor(const sf::Color& color)
	{
		text.setOutlineColor(color);
	}

	void Textbox::setTextOutlineThickness(float thickness)
	{
		text.setOutlineThickness(thickness);
	}

	const sf::Color& Textbox::getTextFillColor() const
	{
		return text.getFillColor();
	}

	const sf::Color& Textbox::getTextOutlineColor() const
	{
		return text.getOutlineColor();
	}

	float Textbox::getTextOutlineThickness() const
	{
		return text.getOutlineThickness();
	}

	void Textbox::setStyle(sf::Uint32 style)
	{
		text.setStyle(style);
	}

	void Textbox::copyBoxProperties(const sf::RectangleShape& rect)
	{
		box.setFillColor(rect.getFillColor());
		box.setOutlineColor(rect.getOutlineColor());
		box.setOutlineThickness(rect.getOutlineThickness());
	}

	void Textbox::copyTextProperties(const sf::Text& text)
	{
		this->text.setFillColor(text.getFillColor());
		this->text.setCharacterSize(text.getCharacterSize());
		updateText();
	}

	void Textbox::setText(bool hasText)
	{
		this->hasText = hasText;
	}

	void Textbox::draw(sf::RenderTarget& target)
	{
		target.draw(box);
		if(hasText)target.draw(text);
	}

	Textbox* Textbox::create(const sf::Vector2f& size)
	{
		return new Textbox(size);
	}
}
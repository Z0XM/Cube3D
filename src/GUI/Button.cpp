#include "Button.hpp"


namespace gui {
	std::map<std::string, Button*> Button::Group;

	void Button::InitVariables()
	{
		this->original.backgroundColor = this->getBackgroundColor();
		this->original.outlineColor = this->getOutlineColor();
		this->original.outlineThickness = this->getOutlineThickness();;
		this->original.textFillColor = this->getTextFillColor();
		this->highlight.outlineThickness = 0.f;
		this->setClickField(this->box.getGlobalBounds());
	}
	Button::Button()
	{
		this->InitVariables();
	}
	Button::Button(sf::RectangleShape box, sf::Text text) : Textbox(box, text, false)
	{
		this->InitVariables();
	}
	Button::~Button()
	{

	}
	void Button::setPosition(const sf::Vector2f&& position)
	{
		this->box.setPosition(position);
		this->alignText();
		this->setClickField(this->box.getGlobalBounds());
	}
	void Button::move(float x, float y)
	{
		this->box.setPosition(this->box.getPosition() + sf::Vector2f(x, y));
		this->alignText();
		this->setClickField(this->box.getGlobalBounds());
	}
	void Button::setHighlight(sf::Color bgColor, sf::Color outColor, float outThickness, sf::Color textColor)
	{
		this->highlight.backgroundColor = bgColor;
		this->highlight.outlineColor = outColor;
		this->highlight.outlineThickness = outThickness;
		this->highlight.textFillColor = textColor;
	}
	void Button::changeHighlightOutline(sf::Color outColor, float outThickness)
	{
		this->highlight.outlineColor = outColor;
		this->highlight.outlineThickness = outThickness;
		this->updateHighlight();
	}
	void Button::changeHighlightBackgroundAndText(sf::Color bgColor, sf::Color textColor)
	{
		this->highlight.backgroundColor = bgColor;
		this->highlight.textFillColor = textColor;
		this->updateHighlight();
	}

	void Button::updateHighlight()
	{
		auto property = this->state == ORIGINAL ? this->original : this->highlight;
		this->setBackgroundColor(property.backgroundColor);
		this->setOutlineColor(property.outlineColor);
		this->setOutlineThickness(property.outlineThickness);
		this->setTextFillColor(property.textFillColor);
	}

	Clickable* Button::isHit(sf::Vector2f& mousePos)
	{
		return this->contains(mousePos) ? this : nullptr;
	}

	void Button::updateTheme()
	{
		this->original.backgroundColor = this->getBackgroundColor();
		this->original.outlineColor = this->getOutlineColor();
		this->original.outlineThickness = this->getOutlineThickness();;
		this->original.textFillColor = this->getTextFillColor();
	}
}

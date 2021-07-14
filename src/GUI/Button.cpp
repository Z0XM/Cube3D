#include "Button.hpp"
#pragma once

gui::Button* gui::Button::mouseHoveringOn = nullptr;
sf::Mouse::Button gui::Button::pressedMouseButton;
gui::Button* gui::Button::clicked = nullptr;

std::unordered_map<std::string, gui::Button*> gui::Button::Group;

gui::Button::Button(const sf::Vector2f& size)
	:Textbox(size)
{
	state = ORIGINAL;
	action = nullptr;
}

gui::Button::~Button()
{
}

void gui::Button::setHighlightFillColor(const sf::Color& color)
{
	highlight.setFillColor(color);
}

void gui::Button::setHighightOutlineColor(const sf::Color& color)
{
	highlight.setOutlineColor(color);
}

void gui::Button::setHighlightOutlineThickness(float thickness)
{
	highlight.setOutlineThickness(thickness);
}

bool gui::Button::contains(const sf::Vector2f& mousePos) const
{
	return box.getGlobalBounds().contains(mousePos);
}

void gui::Button::setAction(std::function<void()> func)
{
	action = func;
}

void gui::Button::activateHighlight()
{
	sf::Color bgColor = highlight.getFillColor(), outColor = highlight.getOutlineColor();
	float t = highlight.getOutlineThickness();

	highlight = box;

	highlight.setFillColor(bgColor);
	highlight.setOutlineColor(outColor);
	highlight.setOutlineThickness(t);

	state = HIGHLIGHT;
}

void gui::Button::deactivateHighlight()
{
	state = ORIGINAL;
}

void gui::Button::draw(sf::RenderTarget& target)
{
	if (state == ORIGINAL)target.draw(box);
	else target.draw(highlight);

	target.draw(text);
}

void gui::Button::copyHighlightProperties(const sf::RectangleShape& rect)
{
	highlight.setFillColor(rect.getFillColor());
	highlight.setOutlineColor(rect.getOutlineColor());
	highlight.setOutlineThickness(rect.getOutlineThickness());
}

gui::Button* gui::Button::create(const sf::Vector2f& size)
{
	return new Button(size);
}

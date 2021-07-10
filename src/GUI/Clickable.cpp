#include "Clickable.hpp"

namespace gui {
	Clickable* Clickable::mouseHoveringOn = nullptr;
	sf::Mouse::Button Clickable::pressedMouseButton;
	Clickable* Clickable::clicked = nullptr;

	Clickable::Clickable()
	{
		this->state = ORIGINAL;
		this->action = nullptr;
	}

	Clickable::~Clickable()
	{
		
	}

	void Clickable::setClickField(sf::FloatRect rect)
	{
		this->clickField = rect;
	}

	sf::FloatRect Clickable::getClickField()
	{
		return this->clickField;
	}

	bool Clickable::contains(const sf::Vector2f& position) const
	{
		return this->clickField.contains(position);
	}
	bool Clickable::contains(const sf::Vector2f&& position) const
	{
		return this->clickField.contains(position);
	}

	void Clickable::setAction(std::function<void()> action)
	{
		this->action = action;
	}
	void Clickable::activateHighlight()
	{
		this->state = HIGHLIGHT;
		this->updateHighlight();
	}
	void Clickable::deactivateHighlight()
	{
		this->state = ORIGINAL;
		this->updateHighlight();
	}
}

#include <iostream>
#include "Dropitem.hpp"

namespace gui {
	std::map<std::string, Dropitem*> Dropitem::Group;
	unsigned int Dropitem::objectCount = 0;

	void Dropitem::InitVariables()
	{
		this->setBackgroundColor(sf::Color::Black);
		this->setTextFillColor(sf::Color::White);

		this->setClickField(this->box.getGlobalBounds());
		this->setAction([this] {this->dropDown(); arrangeAllFrom(this); });

		this->index = objectCount++;
	}

	void Dropitem::InitHighlight()
	{
		this->original.outlineColor = sf::Color::White;
		this->original.outlineThickness = 2;
		this->highlight.outlineColor = sf::Color::Blue;
		this->highlight.outlineThickness = 6;
		this->updateHighlight();
	}

	void Dropitem::InitDropbox()
	{
		this->dropbox = box;
		this->dropbox.setFillColor(sf::Color(21, 21, 21));
		this->dropbox.setSize(sf::Vector2f(this->dropbox.getSize().x, 100));
		this->updateDropbox();
		this->isDropboxActive = false;
	}

	void Dropitem::InitCloseButton()
	{
		this->closeButton = Button(sf::RectangleShape(sf::Vector2f(20, 20)), sf::Text("X", *(this->text.getFont()), 24));
		this->closeButton.setBackgroundColor(sf::Color::Red);
		this->closeButton.setOutlineColor(sf::Color::Transparent);
		this->closeButton.setTextFillColor(sf::Color::Black);
		this->closeButton.setHighlight(sf::Color::Red, sf::Color::Red, 3, sf::Color::Black);
		this->closeButton.setAction(
			[this] {
				deleteObject(this); Clickable::mouseHoveringOn = nullptr; 

			}
		);
		this->updateCloseButton();
	}

	Dropitem::Dropitem()
	{
		this->InitVariables();
		this->InitHighlight();
		this->InitDropbox();
		this->InitCloseButton();
	}
	Dropitem::Dropitem(sf::RectangleShape box, sf::Text text)
	{
		this->box = box;
		this->text = text;
		this->InitVariables();
		this->InitHighlight();
		this->InitDropbox();
		this->InitCloseButton();
	}
	Dropitem::~Dropitem()
	{
	}
	void Dropitem::updateHighlight()
	{
		auto property = this->state == ORIGINAL ? this->original : this->highlight;
		this->setOutlineColor(property.outlineColor);
		this->setOutlineThickness(property.outlineThickness);
	}

	void Dropitem::move(float x, float y)
	{
		this->setPosition(this->getPosition() + sf::Vector2f(x, y));
		this->updateDropbox();
		this->updateCloseButton();
		this->setClickField(this->box.getGlobalBounds());
	}

	void Dropitem::setPosition(const sf::Vector2f&& position)
	{
		this->box.setPosition(position);
		this->updateDropbox();
		this->updateCloseButton();
		this->setClickField(this->box.getGlobalBounds());
	}

	void Dropitem::updateDropbox()
	{
		this->dropbox.setPosition(this->box.getPosition().x, this->box.getPosition().y + this->box.getSize().y);
	}

	void Dropitem::updateCloseButton()
	{
		this->closeButton.setPosition(sf::Vector2f(this->box.getPosition().x + this->box.getSize().x - 30, this->box.getPosition().y + 5));
		this->closeButton.updateTheme();
	}

	sf::Vector2f Dropitem::getPosition() const
	{
		return this->box.getPosition();
	}

	sf::Color Dropitem::getBackgroundColor() const
	{
		return this->box.getFillColor();
	}

	sf::Color Dropitem::getOutlineColor() const
	{
		return this->box.getOutlineColor();
	}

	float Dropitem::getOutlineThickness() const
	{
		return this->box.getOutlineThickness();
	}

	sf::Color Dropitem::getTextFillColor() const
	{
		return this->text.getFillColor();
	}
	void Dropitem::setBackgroundColor(const sf::Color& color)
	{
		this->box.setFillColor(color);
	}

	void Dropitem::setOutlineColor(const sf::Color& color)
	{
		this->box.setOutlineColor(color);
	}

	void Dropitem::setOutlineThickness(const float thickness)
	{
		this->box.setOutlineThickness(thickness);
	}

	void Dropitem::setTextFillColor(const sf::Color& color)
	{
		this->text.setFillColor(color);
	}

	void Dropitem::render(sf::RenderTarget& renderTarget)
	{
		if (this->isDropboxActive)renderTarget.draw(this->dropbox);
		renderTarget.draw(this->box);
		renderTarget.draw(this->text);
		closeButton.render(renderTarget);
	}

	void Dropitem::makeDropItems(unsigned int count, std::string name, sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int characterSize)
	{
		for (int i = 0; i < count; i++) {
			Dropitem::Group[name + char(48 + i)] = new Dropitem(sf::RectangleShape(size), sf::Text("", font, characterSize));
			Dropitem::Group[name + char(48 + i)]->setPosition(position + sf::Vector2f(0, (10 + size.y) * (i + 1)));
		}
	}

	void Dropitem::dropDown()
	{
		this->isDropboxActive = !this->isDropboxActive;
	}

	void Dropitem::arrangeAllFrom(Dropitem* dropItem)
	{
		float moveY;
		moveY = dropItem->dropbox.getSize().y * (dropItem->isDropboxActive ? 1 : -1);
		for (unsigned int i = dropItem->index + 1; i < Group.size(); i++) {
			Dropitem::Group[std::string("infobox") + char(48 + i)]->move(0, moveY);
		}
	}

	Clickable* Dropitem::isHit(sf::Vector2f& mousePos)
	{
		Clickable* clickable;

		clickable = this->closeButton.isHit(mousePos);
		if (!this->isDropboxActive)
			if(clickable != nullptr)return clickable;
		else this->isDropboxActive = false;

		if (this->contains(mousePos))return this;
		return nullptr;
	}

	void Dropitem::deleteObject(Dropitem* dropitem)
	{
		Dropitem::Group.erase(std::string("infobox") + char(48 + dropitem->index));

		for (unsigned int i = dropitem->index + 1; i < Group.size() + 1; i++) {
			Dropitem::Group[std::string("infobox") + char(48 + i)]->index--;
			Dropitem::Group[std::string("infobox") + char(48 + i)]->move(0, -(dropitem->box.getSize().y + 10));
		}

		for (unsigned int i = dropitem->index; i < Group.size(); i++) {
			Dropitem::Group[std::string("infobox") + char(48 + i)] = Dropitem::Group[std::string("infobox") + char(48 + i + 1)];
			Dropitem::Group.erase(std::string("infobox") + char(48 + i + 1));
		}

		Dropitem::objectCount--;

		delete dropitem;
	}
}
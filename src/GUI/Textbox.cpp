#include "Textbox.hpp"

namespace gui {
	std::map<std::string, Textbox*> Textbox::Group;

	Textbox::Textbox()
	{
		this->InitVariables(sf::RectangleShape(), sf::Text(), false);
	}

	Textbox::Textbox(sf::RectangleShape box, sf::Text text, bool setStringAsDefault)
	{
		this->InitVariables(box, text, setStringAsDefault);
		this->setBackgroundColor(sf::Color::Black);
		this->setOutlineColor(sf::Color::White);
		this->setOutlineThickness(2);
		this->setTextFillColor(sf::Color::White);
	}

	Textbox::~Textbox()
	{
		
	}

	void Textbox::InitVariables(sf::RectangleShape box, sf::Text text, bool setStringAsDefault)
	{
		this->box = box;
		this->text = text;
		this->defaultString = setStringAsDefault ? text.getString() : "";
	}

	void Textbox::move(float x, float y)
	{
		this->setPosition(this->getPosition() + sf::Vector2f(x, y));
	}

	void Textbox::setPosition(const sf::Vector2f& position)
	{
		this->box.setPosition(position);
		this->alignText();
	}

	sf::Vector2f Textbox::getPosition() const
	{
		return this->box.getPosition();
	}

	sf::Color Textbox::getBackgroundColor() const
	{
		return this->box.getFillColor();
	}

	sf::Color Textbox::getOutlineColor() const
	{
		return this->box.getOutlineColor();
	}

	float Textbox::getOutlineThickness() const
	{
		return this->box.getOutlineThickness();
	}

	sf::Color Textbox::getTextFillColor() const
	{
		return this->text.getFillColor();
	}

	void Textbox::alignText(const Textbox::TextAlign alignment)
	{
		switch(alignment)
		{
		case TextAlign::CENTER :
			this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height);
			this->text.setPosition(this->box.getPosition().x + this->box.getLocalBounds().width / 2, this->box.getPosition().y + this->box.getLocalBounds().height / 2);
			break;

		case TextAlign::LEFT :
			this->text.setOrigin(this->text.getLocalBounds().left, this->text.getLocalBounds().height);
			this->text.setPosition(this->box.getPosition().x + this->box.getLocalBounds().width / 2, this->box.getPosition().y + this->box.getLocalBounds().height / 2);
			break;

		case TextAlign::RIGHT :
			this->text.setOrigin(this->text.getLocalBounds().width, this->text.getLocalBounds().height);
			this->text.setPosition(this->box.getPosition().x + this->box.getLocalBounds().width / 2, this->box.getPosition().y + this->box.getLocalBounds().height / 2);
			break;
		}
	}

	void Textbox::setBackgroundColor(const sf::Color& color)
	{
		this->box.setFillColor(color);
	}

	void Textbox::setOutlineColor(const sf::Color& color)
	{
		this->box.setOutlineColor(color);
	}

	void Textbox::setOutlineThickness(const float thickness)
	{
		this->box.setOutlineThickness(thickness);
	}

	void Textbox::setTextFillColor(const sf::Color& color)
	{
		this->text.setFillColor(color);
	}

	void Textbox::setString(const std::string& str)
	{
		this->text.setString(str);
	}

	void Textbox::setDefaultString(const std::string& str)
	{
		this->defaultString = str;
	}

	std::string Textbox::getString() const
	{
		return this->text.getString();
	}

	std::string Textbox::getDefaultString() const
	{
		return this->defaultString;
	}

	sf::FloatRect Textbox::getGlobalBounds() const
	{
		return this->box.getGlobalBounds();
	}

	void Textbox::render(sf::RenderTarget& renderTarget)
	{
		renderTarget.draw(this->box);
		renderTarget.draw(this->text);
	}
}
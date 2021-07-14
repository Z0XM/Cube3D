#include "CubeRenderer.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

#include "src/GUI.hpp"

void CubeRenderer::initWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(1200, 700), "Cube 3D", sf::Style::Default, settings);
	window.setFramerateLimit(60);
}

void CubeRenderer::initButtons()
{
	mainFont.loadFromFile("data/Amel Brush Font.ttf");
	subFont.loadFromFile("data/Consola.ttf");

	sf::RectangleShape rect, highlight;
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color(160, 32, 240));
	rect.setOutlineThickness(3);

	highlight.setFillColor(sf::Color(160, 32, 240, 126));
	highlight.setOutlineColor(sf::Color(124, 163, 251));
	highlight.setOutlineThickness(5);

	sf::Text text;
	text.setCharacterSize(56);
	text.setFillColor(sf::Color::White);

	auto constructButton = [this, &rect, &highlight, &text](const std::string& name) {
		gui::Button::Group[name]->copyBoxProperties(rect);
		gui::Button::Group[name]->copyHighlightProperties(highlight);
		gui::Button::Group[name]->copyTextProperties(text);
		gui::Button::Group[name]->setFont(mainFont);
		gui::Button::Group[name]->setString(name);
	};

	gui::Button::Group["Save"] = gui::Button::create({ 150, 60 });
	gui::Button::Group["Save"]->setPosition(getWinSize().x - 50 - 150, 50);
	constructButton("Save");

	gui::Button::Group["Load"] = gui::Button::create({ 150, 60 });
	gui::Button::Group["Load"]->setPosition(getWinSize().x - 50 - 150, 120);
	constructButton("Load");

	gui::Button::Group["Solve"] = gui::Button::create({ 150, 60 });
	gui::Button::Group["Solve"]->setPosition(getWinSize().x - 50 - 150, 190);
	constructButton("Solve");

	gui::Button::Group["Reset"] = gui::Button::create({ 150, 60 });
	gui::Button::Group["Reset"]->setPosition(getWinSize().x - 50 - 150, 260);
	constructButton("Reset");

	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(2);

	highlight.setFillColor(sf::Color(0, 255, 0, 84));
	highlight.setOutlineColor(sf::Color(63, 255, 202));
	highlight.setOutlineThickness(4);

	text.setCharacterSize(36);

	gui::Button::Group["Inside Out"] = gui::Button::create({ 200, 40 });
	gui::Button::Group["Inside Out"]->setPosition(getWinSize().x - 150 - 200, 370);
	constructButton("Inside Out");
	gui::Button::Group["Fill Colors"] = gui::Button::create({ 200, 40 });
	gui::Button::Group["Fill Colors"]->setPosition(getWinSize().x - 150 - 200, 420);
	constructButton("Fill Colors");

	gui::Textbox::Group["Speed"] = gui::Textbox::create({ 110, 40 });
	gui::Textbox::Group["Speed"]->setPosition(getWinSize().x - 150 - 200 + 45, 530);
	gui::Textbox::Group["Speed"]->setFillColor(sf::Color::Transparent);
	gui::Textbox::Group["Speed"]->copyTextProperties(text);
	gui::Textbox::Group["Speed"]->setFont(mainFont);
	gui::Textbox::Group["Speed"]->setString("Speed");

	gui::Button::Group["SpeedI"] = gui::Button::create({ 40, 40 });
	gui::Button::Group["SpeedI"]->setPosition(getWinSize().x - 150 - 40, 530);
	constructButton("SpeedI");
	gui::Button::Group["SpeedI"]->setString(">");
	gui::Button::Group["SpeedI"]->setFont(subFont);
	gui::Button::Group["SpeedI"]->setCharacterSize(23);
	gui::Button::Group["SpeedI"]->setStyle(sf::Text::Bold);

	gui::Button::Group["SpeedD"] = gui::Button::create({ 40, 40 });
	gui::Button::Group["SpeedD"]->setPosition(getWinSize().x - 150 - 40 - 120 - 40, 530);
	constructButton("SpeedD");
	gui::Button::Group["SpeedD"]->setString("<");
	gui::Button::Group["SpeedD"]->setFont(subFont);
	gui::Button::Group["SpeedD"]->setCharacterSize(23);
	gui::Button::Group["SpeedD"]->setStyle(sf::Text::Bold);

	gui::Textbox::Group["SpeedBar"] = gui::Textbox::create({ 0, 40 });
	gui::Textbox::Group["SpeedBar"]->setPosition(getWinSize().x - 150 - 200 + 45, 530);
	gui::Textbox::Group["SpeedBar"]->setFillColor(sf::Color(63, 255, 202, 178));
	gui::Textbox::Group["SpeedBar"]->setText(false);

	gui::Textbox::Group["Credit"] = gui::Textbox::create({ 100, 40 });
	gui::Textbox::Group["Credit"]->setPosition(getWinSize().x - 170, 660);
	gui::Textbox::Group["Credit"]->setTextFillColor(sf::Color(160, 32, 240));
	gui::Textbox::Group["Credit"]->setFillColor(sf::Color::Transparent);
	gui::Textbox::Group["Credit"]->setFont(subFont);
	gui::Textbox::Group["Credit"]->setCharacterSize(28);
	gui::Textbox::Group["Credit"]->setString("Mukul Singh");
}

CubeRenderer::CubeRenderer()
	:cube(700.f / 1200.f)
{
	this->initWindow();
	this->initButtons();

	this->cube.create();

	running = true;
	paused = false;
}

CubeRenderer::~CubeRenderer()
{
	gui::deleteAllGuiGroups();
}

bool CubeRenderer::isRunning()
{
	return this->running;
}

void CubeRenderer::update()
{
	this->pollEvents();

	if (!this->paused) {
		cube.update();
	}
}

void CubeRenderer::pollEvents()
{
	sf::Event event;
	sf::Vector2f mousePos = this->getMousePosition();
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->running = false;

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)this->paused = !this->paused;

		if (!this->paused) {
			if (event.type == sf::Event::MouseMoved) {
				gui::updateMousePointer(this->getMousePosition());
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				gui::registerClick(event.mouseButton.button);
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				gui::unregisterClick(event.mouseButton.button, this->getMousePosition());
			}
			else if (event.type == sf::Event::KeyPressed) {
				cube.handleKeyEvent(event.key.code);
			}
		}
	}
}

void CubeRenderer::render()
{
	this->window.clear();

	this->cube.render(window);
	gui::render(window);

	this->window.display();
}

sf::Vector2f CubeRenderer::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

sf::Vector2f CubeRenderer::getWinSize()
{
	return sf::Vector2f(this->window.getSize());
}
#pragma once
#include <SFML/Graphics.hpp>

#include "GUI/Textbox.hpp"
#include "GUI/Textbox.hpp"
#include "GUI/Button.hpp"

namespace gui {
	void render(sf::RenderTarget& renderTarget);

	void updateMousePointer(const sf::Vector2f& mousPos);

	void registerClick(sf::Mouse::Button button);

	void unregisterClick(sf::Mouse::Button button, const sf::Vector2f& mousePos);

	void deleteAllGuiGroups();
}
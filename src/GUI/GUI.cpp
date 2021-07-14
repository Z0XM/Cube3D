#include "../GUI.hpp"
#include <iostream>
#include <unordered_map>
namespace gui {

	template <typename T>
	void renderGroup(std::unordered_map<std::string, T*>& map, sf::RenderTarget& renderTarget)
	{
		for (auto it = map.begin(); it != map.end(); it++) {
			it->second->draw(renderTarget);
		}
	}

	void render(sf::RenderTarget& renderTarget)
	{
		renderGroup(Textbox::Group, renderTarget);
		renderGroup(Button::Group, renderTarget);
	}

	template <typename T>
	void deleteGroup(std::unordered_map<std::string, T*>& map)
	{
		for (auto it = map.begin(); it != map.end(); it++) {
			delete it->second;
		}
		map.clear();
	}

	void deleteAllGuiGroups()
	{
		deleteGroup(Textbox::Group);
		deleteGroup(Button::Group);
	}

	template<typename T>
	gui::Button* searchForPointedButtonIn(std::unordered_map<std::string, T*>& map, const sf::Vector2f& mousePos)
	{
		for (auto it = map.begin(); it != map.end(); it++) {
			if (it->second->contains(mousePos))
				return it->second;
		}
		return nullptr;
	}

	void updateMousePointer(const sf::Vector2f& mousePos)
	{
		if (Button::mouseHoveringOn == nullptr || !Button::mouseHoveringOn->contains(mousePos)) {

			Button* currentMouseHoveringOn = nullptr;

			currentMouseHoveringOn = searchForPointedButtonIn(Button::Group, mousePos);

			if (Button::mouseHoveringOn != currentMouseHoveringOn)
			{
				if (Button::mouseHoveringOn != nullptr)Button::mouseHoveringOn->deactivateHighlight();
				Button::mouseHoveringOn = currentMouseHoveringOn;
				if (Button::mouseHoveringOn != nullptr)Button::mouseHoveringOn->activateHighlight();
			}
		}
	}

	void registerClick(sf::Mouse::Button button)
	{
		Button::clicked = Button::mouseHoveringOn;
		Button::pressedMouseButton = button;
	}

	void unregisterClick(sf::Mouse::Button button, const sf::Vector2f& mousePos)
	{
		if (Button::clicked != nullptr && Button::clicked == Button::mouseHoveringOn && button == Button::pressedMouseButton)
		{
			if(Button::clicked->action != nullptr)Button::clicked->action();
		}
		Button::clicked = nullptr;
	}
}
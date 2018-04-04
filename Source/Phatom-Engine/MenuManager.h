#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "FadeAnimation.h"
#include "FileManager.h"
#include "InputManager.h"

class TitleScreen;

class MenuManager
{
	public:
		MenuManager();
		~MenuManager();

		void LoadContent(std::string menuId);
		void UnloadContent();

		void UpdateEvent(InputManager input);
		void Update(double deltaTime);

		void Draw(sf::RenderWindow& window);

		int GetItem();

	protected:

	private:
		std::vector<std::vector<std::string> > attr;
		std::vector<std::vector<std::string> > content;

		FileManager file;

		std::vector<std::vector<Animation*> > anim;
		std::vector<Animation*> tempAnim;

		sf::Image image;
		sf::Image null;

		std::vector<sf::Image> menuImages;
		std::vector<std::string> menuItems;

		sf::Vector2f pos;
		int axis;
		std::string align;
		std::vector<std::string> animType;

		int itemNum;

		void EqualizeMenu();
		void SetAnim();
		void SetPos();
};


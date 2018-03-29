#include "MenuManager.h"

MenuManager::MenuManager()
{
	//ctor
}

MenuManager::~MenuManager()
{
	//dtor
}

void MenuManager::EqualizeMenu()
{
	for (unsigned i = 0; i < menuItems.size(); ++i)
	{
		if (menuImages.size() == i)
		{
			menuImages.push_back(image);
		}
	}

	for (unsigned i = 0; i < menuImages.size(); ++i)
	{
		if (menuItems.size() == i)
		{
			menuItems.push_back("");
		}
	}
}

void MenuManager::SetAnim()
{
	for (unsigned i = 0; i < menuItems.size(); ++i)
	{
		for (unsigned j = 0; j < animType.size(); ++j)
		{
			if (animType[j] == "fade")
			{
				tempAnim.push_back(new FadeAnimation);
				tempAnim[tempAnim.size() - 1]->LoadContent(menuItems[i], menuImages[i], pos);
			}
		}

		anim.push_back(tempAnim);
		tempAnim.clear();
	}
}

void MenuManager::SetPos()
{
	sf::Vector2f pos = this->pos;

	for (unsigned i = 0; i < anim.size(); ++i)
	{
		for (unsigned j = 0; j < anim[i].size(); ++j)
		{
			anim[i][j]->SetValue(anim[i][j]->GetPos(), pos);
		}

		double width = menuImages[i].getSize().y + anim[i][0]->GetText().getLocalBounds().width;
		double height = menuImages[i].getSize().x + anim[i][0]->GetText().getLocalBounds().height;

		if (axis == 1)
			pos.x += 25 + width;
		else
			pos.y += 25 + height;
	}
}

void MenuManager::LoadContent(std::string menuID)
{
	null.loadFromFile("null.jpg");

	//file.LoadContent("load/menu.txt", attr, content, menuID);
	file.LoadContent("../../../Source/Phatom-Engine/load/menu.txt", attr, content, menuID);

	itemNum = 0;

	for (unsigned i = 0; i < attr.size(); ++i)
	{
		for (unsigned j = 0; j < attr[i].size(); ++j)
		{
			std::string att = attr[i][j];
			std::string con = content[i][j];

			if (att == "item")
			{
				menuItems.push_back(con);
			}
			else if (att == "image")
			{
				image.loadFromFile(con);
				menuImages.push_back(image);
			}
			else if (att == "position")
			{
				std::string position[2];
				position[0] = con.substr(0, con.find(','));
				position[1] = con.substr(con.find(',') + 1);

				this->pos.x = atof(position[0].c_str());
				this->pos.y = atof(position[1].c_str());

			}
			else if (att == "align")
			{
				align = con;
			}
			else if (att == "axis")
			{
				axis = atoi(con.c_str());
			}
			else if (att == "animation")
			{
				animType.push_back(con);
			}
		}
	}

	EqualizeMenu();
	SetAnim();
	SetPos();

}

void MenuManager::UnloadContent()
{
	menuItems.clear();
	menuImages.clear();

	for (unsigned i = 0; i < anim.size(); ++i)
	{
		for (unsigned j = 0; j < anim[i].size(); ++j)
		{
			delete anim[i][j];
		}
	}

	anim.clear();
	animType.clear();
	attr.clear();
	content.clear();
}

void MenuManager::UpdateEvent(InputManager input)
{
	if (axis == 1)
	{
		if (input.KeyPressed((sf::Keyboard::Right)) || input.KeyPressed(sf::Keyboard::D))
			itemNum++;
		else if (input.KeyPressed(sf::Keyboard::Left) || input.KeyPressed(sf::Keyboard::A))
			itemNum--;
	}
	else
	{
		if (input.KeyPressed((sf::Keyboard::Down)) || input.KeyPressed(sf::Keyboard::S))
			itemNum++;
		else if (input.KeyPressed(sf::Keyboard::Up) || input.KeyPressed(sf::Keyboard::W))
			itemNum--;
	}

	std::cout << itemNum << std::endl;
}

void MenuManager::Update(double deltaTime)
{
	if (itemNum < 0)
		itemNum = menuItems.size() - 1;
	else if (itemNum > menuItems.size() - 1)
		itemNum = 0;

	for (unsigned i = 0; i < anim.size(); ++i)
	{
		for (unsigned j = 0; j < anim[i].size(); ++j)
		{
			anim[i][j]->SetValue(anim[i][j]->GetActive(), false);
			if (i == itemNum)
				anim[i][j]->SetValue(anim[i][j]->GetActive(), true);

			anim[i][j]->Update(deltaTime);
		}
	}
}

void MenuManager::Draw(sf::RenderWindow& window)
{
	for (unsigned i = 0; i < anim.size(); ++i)
	{
		for (unsigned j = 0; j < anim[i].size(); ++j)
		{
			anim[i][j]->Draw(window);
		}
	}
}

int MenuManager::GetItem()
{
	return itemNum;
}
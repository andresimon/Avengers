#include "SpriteRender.h"

SpriteRender::SpriteRender(std::string fileName)
{
	this->fileName = fileName;

	LoadContent();
}

void SpriteRender::LoadContent()
{
	std::string assetsFolder = "../../../Assets/";
	std::string fullFileName = assetsFolder.append(this->fileName);

	sf::Image image;
	if (!image.loadFromFile(fullFileName))
	{
		std::cout << "Could not find the specified image at SpriteRender.cpp" << std::endl;
		return;
	}

	sf::Texture texture;
	texture.loadFromImage(image);

	sprite.setTexture(texture);
}

void SpriteRender::Update()
{
	//Phantom::_mainWindow.draw(sprite);
}

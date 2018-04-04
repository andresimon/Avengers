#include "Animation.h"

Animation::Animation()
{
	//ctor
}

Animation::~Animation()
{
	//dtor
}

void Animation::LoadContent(std::string inText, sf::Image& image, sf::Vector2f pos)
{
	this->preText = inText;
	//std::cout << "Loading text " << inText << std::endl;
	this->image = image;
	this->pos = pos;

	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		//if (!font.loadFromFile("Font1.ttf"))
	{
		std::cout << "Font failed to load\n";
	}

	alpha = 1.0;
	textColor = sf::Color(114, 77, 255);

	if (image.getSize().x > 0)
		texture.loadFromImage(image);

	sprite.setTexture(texture);
	text.setString(preText);
	active = false;
}

void Animation::UnloadContent()
{

}

void Animation::Update(double deltaTime)
{

}

void Animation::Draw(sf::RenderWindow& window)
{
	sprite.setColor(sf::Color(255, 255, 255, 255 * alpha));
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	//sprite.setTextureRect()

	if (text.getString() != "")
	{
		std::string s = text.getString();
		//text.setString("Hello");
		text.setFont(font);
		text.setPosition(pos);
		text.setFillColor(sf::Color(255, 255, 255, 255 * alpha));
		//text.setScale(scale, scale);
		window.draw(text);
	}

	if (sprite.getTexture() != NULL)
		window.draw(sprite);
}

double &Animation::GetAlpha()
{
	return alpha;
}

bool &Animation::GetActive()
{
	return active;
}

double &Animation::GetScale()
{
	return scale;
}

void Animation::SetAlpha(double val)
{
	alpha = val;
}

sf::Vector2f& Animation::GetPos()
{
	return pos;
}

sf::Text& Animation::GetText()
{
	return this->text;
}
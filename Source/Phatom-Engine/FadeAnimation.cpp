#include "FadeAnimation.h"

#include <iostream>

FadeAnimation::FadeAnimation()
{
	//ctor
}

FadeAnimation::~FadeAnimation()
{
	//dtor
}

void FadeAnimation::LoadContent(std::string text, sf::Image& image, sf::Vector2f pos)
{
	Animation::LoadContent(text, image, pos);
	increase = false;
	fadeSpeed = 1.0;
}

void FadeAnimation::UnloadContent()
{

}

void FadeAnimation::Update(double deltaTime)
{
	if (active)
	{
		if (!increase)
			alpha -= deltaTime * fadeSpeed;
		else
			alpha += deltaTime * fadeSpeed;

		if (alpha >= 1.0)
		{
			alpha = 1.0;
			increase = false;
		}
		else if (alpha <= 0.0)
		{
			alpha = 0.0;
			increase = true;
		}
	}
	else
	{
		alpha = 1.0;
	}

	Animation::Update(deltaTime);

}

void FadeAnimation::Draw(sf::RenderWindow& window)
{
	Animation::Draw(window);
}

void FadeAnimation::SetAlpha(double val)
{
	alpha = val;
	if (alpha == 0.0)
		increase = true;
	else
		increase = false;
}
#pragma once

#include "Animation.h"

class FadeAnimation : public Animation
{
	public:
		FadeAnimation();
		~FadeAnimation();

		void LoadContent(std::string text, sf::Image& image, sf::Vector2f pos);
		void UnloadContent();
		void Update(double deltaTime);
		void Draw(sf::RenderWindow& window);
		void SetAlpha(double val);

	protected:

	private:
		bool increase;
		double fadeSpeed;
};

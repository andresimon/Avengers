#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Animation
{
	public:
		Animation();
		~Animation();

		virtual void LoadContent(std::string text, sf::Image& image, sf::Vector2f pos);
		virtual void UnloadContent();
		virtual void Update(double deltaTime);
		virtual void Draw(sf::RenderWindow& window);

		virtual void SetAlpha(double val);

		double &GetAlpha();
		bool &GetActive();
		double &GetScale();
		sf::Vector2f& GetPos();
		sf::Text& GetText();

		template<typename T>
		void SetValue(T& variable, T value) { variable = value; }

	protected:
		double alpha;
		double scale;

		std::string preText;
		sf::Font font;
		sf::Text text;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f pos;
		sf::Color textColor;
		sf::IntRect sourceRect;

		bool active;

	private:
};

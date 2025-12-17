#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Texture.hpp>
class PlayerShape
{
private:
	sf::Sprite player_;
	sf::Texture photograph_;
public:
	PlayerShape(std::string texturepath);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f);
	void Draw(sf::RenderWindow window);
	sf::Vector2f GetPosition();
};
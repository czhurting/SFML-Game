#pragma once
#include"PlayerShape.hpp"
#include"PlayerBase.hpp"
#include"MonoBehaviour.hpp"
#include<memory>

class PlayerController:public GameSet::MonoBehaviour
{
private:
	std::unique_ptr<PlayerShape> shape_;
	std::unique_ptr<PlayerBase> base_;
public:
	PlayerController(PlayerBase, PlayerShape);
	PlayerController(std::string, std::string n, std::string id, float s, float hp);
	PlayerController(PlayerController&&);
	
};
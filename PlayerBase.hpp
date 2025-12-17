#pragma once
#include"CharacterBase.hpp"
class PlayerBase
{
private:
	GameSet::NameID name_;
	GameSet::Performance basic_;
	GameSet::MoveSpeed speed_;
public:
	PlayerBase(std::string n, std::string id, float s, float hp);
};
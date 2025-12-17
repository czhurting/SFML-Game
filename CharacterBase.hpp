#pragma once
#include<string>
namespace GameSet
{
	class NameID
	{
	private:
		std::string m_name;
		std::string m_id;
	public:
		NameID(std::string name, std::string id);
		void ChangeName(std::string name);
		std::string GetName();
	};
	class Performance
	{
	private:
		float m_current_health;
		float m_max_health;
	public:
		Performance(float);
		void TakeDamage(float damage);
	};//之后基础属性往这里塞
	class MoveSpeed
	{
		float m_speed;
	public:
		MoveSpeed(float);
		float GetSpeed();
	};//之后进阶属性往这里塞
};
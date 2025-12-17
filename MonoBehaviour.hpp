#pragma once
namespace GameSet
{
	class MonoBehaviour//³éÏóÀà
	{
	protected:
		MonoBehaviour() = default;
	public:
		virtual ~MonoBehaviour() = default;
		virtual void Start() = 0;
		virtual void Update(float) = 0;
	};
};
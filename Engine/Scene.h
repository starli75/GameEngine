#pragma once
#include <vector>


namespace nu {
	class Actor;

	class Scene
	{
	public:
		void AddActor(class Actor* actor) { m_actors.push_back(actor); }

		void Update(float dt);
		void Draw(const class Renderer& renderer);

	private:
		std::vector<class Actor*> m_actors;

	};
}
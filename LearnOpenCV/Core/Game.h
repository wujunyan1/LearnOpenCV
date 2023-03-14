#pragma once
#include "Camera.h"
#include "../event/Event.h"
#include "../event/EventDispatcher.h"
#include "../event/EventCustom.h"

namespace Core {
	class Game
	{
	public:
		static Game* GetInstance() {
			if (instance == nullptr) {
				instance = new Game();
			}

			return instance;
		}

		static void DestroyInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}

		void Tick(long time);
		void Render(long time);

		float GetCurrUpdateDelay() { return delay / 1000; }

		void LoadMainScene();

		EventDispatcher* GetEventDispatcher() { return dispatcher; };

	private:
		static Game* instance;

		Game() 
		{
			delay = 0.0f;
			dispatcher = new EventDispatcher();
			dispatcher->setEnabled(true);
		}

		~Game();

		float delay;

		EventDispatcher* dispatcher;
	};
}


#pragma once
#include "Camera.h"
#include "../event/Event.h"

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

		Camera GetMainCamera() { return mainCamera; }

		void SetMainCamera(Camera c) { mainCamera = c; }

		float GetCurrUpdateDelay() { return delay / 1000; }

		void LoadMainScene();

		Event::unsubscribe registerEvent(std::string name, Event::Callback callback)
		{
			return m_eventManager->registerEvent(name, callback);
		}
	private:
		static Game* instance;

		Game() 
		{
			delay = 0.0f;
			m_eventManager = new EventManager();
		}

		~Game();

		Camera mainCamera;
		float delay;

		EventManager* m_eventManager;
	};
}


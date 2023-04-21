#pragma once
#include "Camera.h"

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
		//void Render(long time);

		float GetCurrUpdateDelay() { return delay / 1000; }
		float GetCurrFPS() { return 1000.0f / delay; }

		void LoadMainScene();

		void InitEngine();

	private:
		static Game* instance;

		Game();

		~Game();

		float delay;
	};
}


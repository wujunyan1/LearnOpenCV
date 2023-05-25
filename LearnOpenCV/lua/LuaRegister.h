#pragma once

#include <vector>

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace Core {
	class LuaRegister
	{
	public:
		static LuaRegister* GetInstance() {
			if (instance == nullptr) {
				instance = new LuaRegister();
			}

			return instance;
		}

		static void DestroyInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}

	public:
		template<typename ...Args>
		bool call(const char* funcName, Args&&... args)
		{
			
		}


	private:
		LuaRegister();

		~LuaRegister();

	private:
		static LuaRegister* instance;

		lua_State* L;
	};


}
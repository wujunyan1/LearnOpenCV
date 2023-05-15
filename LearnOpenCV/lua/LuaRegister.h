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
			if (m_loadSuc)
				return LUA_CALL::call(m_L, 0, funcName, std::forward<Args>(args)...);
			else
				return false;
		}


	private:
		LuaRegister();

		~LuaRegister();

	private:
		static LuaRegister* instance;

		lua_State* L;
	};


}
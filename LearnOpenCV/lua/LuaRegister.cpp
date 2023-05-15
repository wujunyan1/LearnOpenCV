#include "LuaRegister.h"

using namespace Core;

LuaRegister* LuaRegister::instance = nullptr;

LuaRegister::LuaRegister()
{
    //创建一个 Lua state
    L = luaL_newstate();

    //Opens all standard Lua libraries into the given state.
    //对于一个给定的 Lua state 打开所有的Lua标准库
    luaL_openlibs(L);

    //打开Lua脚本文件
    luaL_dofile(L, "asserts/script/main.lua");
}

LuaRegister::~LuaRegister()
{
    //关闭 Lua state
    lua_close(L);
}
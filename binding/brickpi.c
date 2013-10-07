#include "lua.h"
#include "lauxlib.h"
#include "BrickPi.h"

#define BRICKPI_LUA_VERSION "v0.1"

/* functions in library namespace */
static luaL_Reg func[] = {
  {"setup", brickpi_setup},
  {"motorEnable", brickpi_motorEnable},
  {"sensorType", brickpi_sensorType},
  {"setupSensors", brickpi_setupSensors},
  {"sleep", brickpi_sleep},
  {"motorSpeed", brickpi_motorSpeed},
  {"sensorValue", brickpi_sensorValue},
  {"update", brickpi_update},
  {NULL, NULL}
};

int luaopen_brickpi_core(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, func, 0);
  /* make version string available to scripts */
  lua_pushstring(L, "_VERSION");
  lua_pushstring(L, BRICKPI_LUA_VERSION);
  lua_rawset(L, -3);
  return 1;
}

static int brickpi_setup(lua_State *L) {
  int result = BrickPiSetup();
  if (result) {
    lua_pushboolean(L, false);
    lua_pushstring(L, "Impossible to setup BrickPi");
    return 2;
  }
  BrickPi.Address[0] = 1;
  BrickPi.Address[1] = 2;
  lua_pushboolean(L, true);
  return 1;
}

static int brickpi_motorEnable(lua_State *L) {
  int n = lua_gettop(L);
  for (int i=1; i<=n; ++i) {
    int port = lua_tointeger(L, i);
    BrickPi.MotorEnable[port] = 1;
  }
  return 0;
}

static int brickpi_sensorType(lua_State *L) {
  int port = lua_tointeger(L, 1);
  int type = lua_tointeger(L, 2);
  BrickPi.SensorType[port] = type;
  return 0;
}

static int brickpi_setupSensors(lua_State *L) {
  int result = BrickPiSetupSensors();
  if (result) {
    lua_pushboolean(L,false);
    lua_pushstring(L,"Impossible to setup sensors configuration");
    return 2;
  }
  lua_pushboolean(L,true);
  return 1;
}

static int brickpi_sleep(lua_State *L) {
  // TODO:
  return 0;
}

static int brickpi_motorSpeed(lua_State *L) {
  int port  = lua_tointeger(L, 1);
  int value = lua_tointeger(L, 2);
  BrickPi.MotorSpeed[port] = value;
  return 0;
}

static int brickpi_sensorValue(lua_State *L) {
  int port  = lua_tointeger(L, 1);
  long value = BrickPi.Sensor[port];
  lua_pushnumber(L, value);
  return 1;
}

static int brickpi_update(lua_State *L) {
  int result = BrickPiUpdateValues();
  if (result) {
    lua_pushboolean(L, false);
    lua_pushstring(L, "Impossible to update BrickPi values");
    return 2;
  }
  lua_pushboolean(L, true);
  return 1;
}

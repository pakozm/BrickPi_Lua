/*
*  Francisco Zamora-Martinez
*  pakozm<at>gmail.com
*  http://cafre.dsic.upv.es:8080/~pako/
*  Initial date: October 7, 2013
*  Last updated: October 7, 2013
*
*  You may use this code as you wish, provided you give credit where it's due.
*
*  This is the binding of BrickPi C to Lua.
*/
#include <time.h>
#include <math.h>
#include "lua.h"
#include "lauxlib.h"
#include "BrickPi.h"

#define true  1
#define false 0
#define BRICKPI_LUA_VERSION "v0.1"

#define clip(v,min,max) ((v)<min?min:((v)>max?max:v))

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
  int i, port;
  for (i=1; i<=n; ++i) {
    port = lua_tointeger(L, i);
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
  double sleeptime;
  double seconds;
  struct timespec req;
  sleeptime = lua_tonumber(L,1);
  seconds   = floor(sleeptime);
  req.tv_sec  = (time_t)seconds;
  req.tv_nsec = (long)((sleeptime-seconds)*1e6);
  nanosleep(&req, 0);
  return 0;
}

static int brickpi_motorSpeed(lua_State *L) {
  int i, n = lua_gettop(L);
  if (n == 1) {
    int port = lua_tointeger(L, 1);
    lua_pushinteger(L, BrickPi.MotorSpeed[port]);
    return 1;
  }
  int port, value = lua_tointeger(L, n);
  for (i=1;i<n;++i) {
    port = lua_tointeger(L, 1);
    BrickPi.MotorSpeed[port] = value;
  }
  return 0;
}

static int brickpi_motorSteering(lua_State *L) {
  int portA = lua_tointeger(L, 1);
  int portB = lua_tointeger(L, 2);
  int speedA, speedB;
  double steering = lua_tonumber(L, 3); /* in range [-1,1] */
  double power    = lua_tonumber(L, 4); /* in range [-1,1] */
  steering = clip(steering, -1.0, 1.0);
  power    = clip(power, -1.0, 1.0);
  speedA   = ( 2.0*steering + 1.0)*255*power;
  speedB   = (-2.0*steering + 1.0)*255*power;
  BrickPi.MotorSpeed[portA] = clip(speedA,-255,255);
  BrickPi.MotorSpeed[portB] = clip(speedB,-255,255);
}

static int brickpi_sensorValue(lua_State *L) {
  int i, n = lua_gettop(L);
  int port;
  long value;
  for (i=1; i<=n; ++i) {
    port  = lua_tointeger(L, i);
    value = BrickPi.Sensor[port];
    lua_pushnumber(L, value);
  }
  return n;
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

/* functions in library namespace */
static luaL_Reg func[] = {
  {"setup", brickpi_setup},
  {"motorEnable", brickpi_motorEnable},
  {"sensorType", brickpi_sensorType},
  {"setupSensors", brickpi_setupSensors},
  {"sleep", brickpi_sleep},
  {"motorSpeed", brickpi_motorSpeed},
  {"motorSteering", brickpi_motorSteering},
  {"sensorValue", brickpi_sensorValue},
  {"update", brickpi_update},
  {NULL, NULL}
};

#define BIND_NUMBER(key) do {			\
    lua_pushstring(L, #key);			\
    lua_pushnumber(L, key);			\
    lua_rawset(L, -3);				\
  } while(0)

int luaopen_brickpi(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, func, 0);
  /* make version string available to scripts */
  lua_pushstring(L, "_VERSION");
  lua_pushstring(L, BRICKPI_LUA_VERSION);
  lua_rawset(L, -3);
  /* SETS NUMBERS FOR SENSOR, MOTOR, PORT */
  BIND_NUMBER(PORT_A);
  BIND_NUMBER(PORT_B);
  BIND_NUMBER(PORT_C);
  BIND_NUMBER(PORT_D);
  BIND_NUMBER(PORT_1);
  BIND_NUMBER(PORT_2);
  BIND_NUMBER(PORT_3);
  BIND_NUMBER(PORT_4);
  BIND_NUMBER(TYPE_MOTOR_PWM);
  BIND_NUMBER(TYPE_MOTOR_SPEED);
  BIND_NUMBER(TYPE_MOTOR_POSITION);
  BIND_NUMBER(TYPE_SENSOR_RAW);
  BIND_NUMBER(TYPE_SENSOR_LIGHT_OFF);
  BIND_NUMBER(TYPE_SENSOR_LIGHT_ON);
  BIND_NUMBER(TYPE_SENSOR_TOUCH);
  BIND_NUMBER(TYPE_SENSOR_ULTRASONIC_CONT);
  BIND_NUMBER(TYPE_SENSOR_ULTRASONIC_SS);
  BIND_NUMBER(TYPE_SENSOR_RCX_LIGHT);
  BIND_NUMBER(TYPE_SENSOR_COLOR_FULL);
  BIND_NUMBER(TYPE_SENSOR_COLOR_RED);
  BIND_NUMBER(TYPE_SENSOR_COLOR_GREEN);
  BIND_NUMBER(TYPE_SENSOR_COLOR_BLUE);
  BIND_NUMBER(TYPE_SENSOR_COLOR_NONE);
  BIND_NUMBER(TYPE_SENSOR_I2C);
  BIND_NUMBER(TYPE_SENSOR_I2C_9V);
  return 1;
}

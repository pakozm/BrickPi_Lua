brickpi = require "brickpi"

assert(brickpi.setup())

brickpi.motorEnable(brickpi.PORT_A, brickpi.PORT_B)
-- brickpi.sensorType(brickpi.PORT_1, brickpi.SENSOR_TOUCH)

assert(brickpi.setupSensors())

brickpi.sleep(0.01)

for i=1,300 do
  brickpi.motorSpeed(brickpi.PORT_A, 200)
  brickpi.motorSpeed(brickpi.PORT_B, 200)
  assert(brickpi.update())
  brickpi.sleep(0.01)
end

for i=1,300 do
  brickpi.motorSpeed(brickpi.PORT_A, -200)
  brickpi.motorSpeed(brickpi.PORT_B, -200)
  assert(brickpi.update())
  brickpi.sleep(0.01)
end

-- brickpi.sensorValue(brickpi.PORT_1)

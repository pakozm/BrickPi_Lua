brickpi = require "brickpi"

assert(brickpi.setup())

brickpi.motorEnable(brickpi.PORT_A, brickpi.PORT_B)
-- brickpi.sensorType(brickpi.PORT_1, brickpi.SENSOR_TOUCH)

assert(brickpi.setupSensors())

brickpi.sleep(0.01)

for i=1,600 do
  brickpi.motorSpeed(brickpi.PORT_A, brickpi.PORT_B, 200)
  brickpi.update() -- FIXME: assert(....) is failing
  brickpi.sleep(0.05)
end

for i=1,600 do
  brickpi.motorSpeed(brickpi.PORT_A, brickpi.PORT_B, -200)
  brickpi.update() -- FIXME: assert(....) is failing
  brickpi.sleep(0.05)
end

-- brickpi.sensorValue(brickpi.PORT_1, brickpi.PORT_2)

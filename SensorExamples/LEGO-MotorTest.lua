assert(brickpi.setup())

brickpi.motorEnable(brickpi.PORT_A, brickpi.PORT_B)
-- brickpi.sensorType(brickpi.PORT_1, brickpi.SENSOR_TOUCH)

assert(brickpi.setup_sensors())

brickpi.sleep(10000)

for i=1,300 do
  brickpi.motorSpeed(brickpi.PORT_A, 200)
  brickpi.motorSpeed(brickpi.PORT_B, 200)
  assert(brickpi.update())
  brickpi.sleep(10000)
end

for i=1,300 do
  brickpi.motorSpeed(brickpi.PORT_A, -200)
  brickpi.motorSpeed(brickpi.PORT_B, -200)
  assert(brick.update())
  brickpi.sleep(10000)
end

-- brickpi.sensorValue(brickpi.PORT_1)

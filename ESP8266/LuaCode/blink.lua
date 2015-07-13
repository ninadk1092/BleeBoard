-- Config
local pin = 1            --> GPIO2
local value = gpio.LOW
local duration = 1000    --> 1 second
local count = 10

-- Initialise the pin
gpio.mode(pin, gpio.OUTPUT)
gpio.write(pin, value)

-- Create an interval
for count=0,10,1 do
      tmr.alarm(0, duration, 1, function ()
    if value == gpio.LOW then
        value = gpio.HIGH
    else
        value = gpio.LOW
    end

    gpio.write(pin, value)
	end)
end

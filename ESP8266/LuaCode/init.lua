-- Config
local pin = 4            --> GPIO2
local value = gpio.LOW
local duration = 1000    --> 1 second


-- Function toggles LED state
function toggleLED ()
    if value == gpio.LOW then
        value = gpio.HIGH
    else
        value = gpio.LOW
    end

    gpio.write(pin, value)
end

-- Function to stop the blinking
function stopIt ()
    tmr.stop(0)
    gpio.write(pin, ~value)
end

pwm.setup(pin,500,512)
pwm.start(pin)

--Generate PWM
function pwmTest (intensity)
    pwm.setduty(pin,intensity)
end
  

-- Initialise the pin
--gpio.mode(pin, gpio.OUTPUT)
--gpio.write(pin, value)

-- Create an interval
--tmr.alarm(0, duration, 1, toggleLED)

-- Create a timeout
--tmr.alarm(0, 5000, 0, stopIt)

tmr.alarm(0, duration, 1, pwmTest(0))


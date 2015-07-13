print('Hello')    -- This bit here is a comment

wifi.sta.config("vismaya1","00000000")
wifi.sta.connect()
tmr.alarm(1, 1000, 1, function()
if wifi.sta.getip()== nil then
	print("IP unavaiable, Waiting...")
else
tmr.stop(1)

sio.send("AT+CWQAP\r\n");

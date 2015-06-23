
### Notes:

* pseudo file contains code which reads the state and generates actions on peripherals accordingly. It is not responsible for setting the state/ changing the state. That is done in another file. 
* pseudo file makes changes strictly through drivers. 
* pseudo file is the main() file that includes all other files/drivers, etc.

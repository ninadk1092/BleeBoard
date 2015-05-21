# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java
ARDMK_DIR     = ./
AVR_TOOLS_DIR = /usr/local/CrossPack-AVR/
MONITOR_PORT  = /dev/ttyACM0
BOARD_TAG    = uno
ARDUINO_LIBS = SoftwareSerial
include Arduino.mk

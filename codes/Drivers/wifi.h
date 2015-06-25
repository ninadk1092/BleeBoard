
#define OK Serial.find("OK")
#define RST "AT+RST\r\n"
#define APMODE "AT+CWMODE=2\r\n"
#define STMODE "AT+CWMODE=1\r\n"
#define DISCONNECT "AT+CWQAP\r\n"
#define APLIST "AT+CWLAP\r\n"

class LED {
public:
	static bool inUse;
	static bool isOn;

	static void open(bool);
	static void switchOn(bool);
	static void blink(int, int);
	static void toggle();
};

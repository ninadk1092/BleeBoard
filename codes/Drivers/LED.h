class LED {
public:
	static bool inUse;
	static bool isOn;

	static void open(bool);
	static void switchOn(bool);
	static void blink(int, int);
	static void toggle();
};

class motor {
public:
	static bool inUse;
	static bool isOn;
	
	static int lowerLimit = 0;
	static int motorIntensity = 0;

	static void open(bool);
	static void open(bool, int);
	static int getSpeed(void);
	static void setLowerLimit(int);
};


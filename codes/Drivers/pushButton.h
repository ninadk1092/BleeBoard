class pushButton {
public:
	static bool inUse;
	static bool isOn;
	
	static int debouncePeriod = 0;

	/*
	The following "prevPress tells the previous press type"
		s = short
		l = long
		d = double short
		n = none (may be required for maiden execution)
	*/
	static char prevPress = 'n';

	static void open(bool);
	static void setPeriod(int);
	static int getPeriod(void);
	static void setLowerLimit(int);
};

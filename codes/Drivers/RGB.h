class RGB {
public:
	static bool inUse;
	static int red = 0;
	static int green = 0;
	static int blue = 0;

	static void open(bool);
	static void setColor(int, int, int);
	static void getColor();
};

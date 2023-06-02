// Examlple of `factory method' design pattern

#include <iostream>
#include <string>

using namespace std;

class Cup {
public:
	string color;
	Cup(): color("") {}

	// This is a factory method
	static Cup* getCup(string color);
};

class RedCup: public Cup {
public:
	RedCup() { color = "red"; }
};

class BluedCup : public Cup {
public:
	BluedCup() { color = "blue"; }
};

Cup* Cup::getCup(string color) {
	if (color == "red")
		return new RedCup();
	else if (color == "blue")
		return new BluedCup();
	else
		return 0;
}

int main() {
	Cup* redCup = Cup::getCup("red");
	cout << redCup->color << endl;

	Cup* BluedCup = Cup::getCup("blue");
	cout << BluedCup->color << endl;
}

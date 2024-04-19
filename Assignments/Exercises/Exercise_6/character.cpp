#include <string>

using namespace std;

class Character{
private:
	int asciiCode;
	string character;
	int frequency;
public:
	Character(int code, string c, int f) : asciiCode(code), character(c), frequency(f){};
	int GetAsciiCode(){return asciiCode;};
	string GetCharacter(){return character;};
	int GetFrequency(){return frequency;};
};


#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Enum to represent different types of string conversions
enum ConversionType {
	CT_LowerCase,
	CT_UpperCase,
	CT_Capitalize,
	CT_SentenceCase,
	CT_ToggleCase
};

// Abstract base class for string conversions
class StringConversion {
public:
	virtual string convertString(string s) = 0;	// pure virtual class
	virtual ~StringConversion() {}
};

// Library Classes

// Converts the string to lowercase
class ClasstoLowerCase : public StringConversion {
public:
	string convertString(string s) {
		for (auto& c : s)
			if ('A' <= c && c <= 'Z')
				c = c - 'A' + 'a';
		return s;
	}
};

// Converts the string to uppercase
class ClasstoUpperCase : public StringConversion {
public:
	string convertString(string s) {
		for (auto& c : s)
			if ('a' <= c && c <= 'z')
				c = c - 'a' + 'A';
		return s;
	}
};

// Capitalizes each word in the string
class ClasscapitalizeEachWord : public StringConversion {
public:
	string convertString(string s) {
		std::istringstream iss(s);
		std::string result, word;
		while (iss >> word) {
			if (!result.empty())
				result += ' ';
			word[0] = toupper(word[0]);
			for (size_t i = 1; i < word.length(); ++i)
				word[i] = tolower(word[i]);
			result += word;
		}
		return result;
	}
};

// Converts the string to sentence case (first letter uppercase, rest lowercase)
class ClasstoSentenceCase : public StringConversion {
public:
	string convertString(string s) {
		if (!s.empty()) {
			s[0] = toupper(s[0]);
			for (size_t i = 1; i < s.length(); ++i)
				s[i] = tolower(s[i]);
		}
		return s;
	}
};

// Toggles the case of each character in the string
class ClasstoggleCase : public StringConversion {
public:
	string convertString(string s) {
		for (auto& c : s) {
			if (islower(c))
				c = toupper(c);
			else if (isupper(c))
				c = tolower(c);
		}
		return s;
	}
};

// Factory class for creating StringConversion objects based on ConversionType
class StringConversionFactory {
public:
	static StringConversion* createStringConversion(ConversionType conversionType) {
		switch (conversionType) {
		case CT_LowerCase:
			return new ClasstoLowerCase();
		case CT_UpperCase:
			return new ClasstoUpperCase();
		case CT_Capitalize:
			return new ClasscapitalizeEachWord();
		case CT_SentenceCase:
			return new ClasstoSentenceCase();
		case CT_ToggleCase:
			return new ClasstoggleCase();
		default:
			return nullptr;
		}
	}
};

// Client class to use the StringConversion objects
class Client {
public:
	Client() : pstringConversion(nullptr) {}

	void BuildStringConversion(ConversionType conversionType) {
		StringConversionFactory* scf = new StringConversionFactory();
		pstringConversion = scf->createStringConversion(conversionType);

		delete scf;
	}

	~Client() {
		if (pstringConversion) {
			delete pstringConversion;
			pstringConversion = nullptr;
		}
	}

	StringConversion* getConversionType() { return pstringConversion; }

private:
	StringConversion* pstringConversion;
};
int main() {
	
    // Create a Client object
    Client* pClient = new Client();

    // Input strings
    string input1 = "This is a sample string.";
    string input2 = "cOMpLEx StrinG with Multiple WORDS.";

    // Lower case conversion
    pClient->BuildStringConversion(CT_LowerCase);
    string lowerCase1 = pClient->getConversionType()->convertString(input1);
    string lowerCase2 = pClient->getConversionType()->convertString(input2);
    cout << "Lower Case 1: " << lowerCase1 << endl;
    cout << "Lower Case 2: " << lowerCase2 << endl;

    // Upper case conversion
    pClient->BuildStringConversion(CT_UpperCase);
    string upperCase1 = pClient->getConversionType()->convertString(input1);
    string upperCase2 = pClient->getConversionType()->convertString(input2);
    cout << "Upper Case 1: " << upperCase1 << endl;
    cout << "Upper Case 2: " << upperCase2 << endl;

    // Sentence case conversion
    pClient->BuildStringConversion(CT_SentenceCase);
    string sentenceCase1 = pClient->getConversionType()->convertString(input1);
    string sentenceCase2 = pClient->getConversionType()->convertString(input2);
    cout << "Sentence Case 1: " << sentenceCase1 << endl;
    cout << "Sentence Case 2: " << sentenceCase2 << endl;

    // Capitalize each word conversion
    pClient->BuildStringConversion(CT_Capitalize);
    string capitalize1 = pClient->getConversionType()->convertString(input1);
    string capitalize2 = pClient->getConversionType()->convertString(input2);
    cout << "Capitalize Each Word 1: " << capitalize1 << endl;
    cout << "Capitalize Each Word 2: " << capitalize2 << endl;

    // Toggle case conversion
    pClient->BuildStringConversion(CT_ToggleCase);
    string toggleCase1 = pClient->getConversionType()->convertString(input1);
    string toggleCase2 = pClient->getConversionType()->convertString(input2);
    cout << "Toggle Case 1: " << toggleCase1 << endl;
    cout << "Toggle Case 2: " << toggleCase2 << endl;

    delete pClient;
    return 0;
}

/*
Output:
	Lower Case 1: this is a sample string.
	Lower Case 2: complex string with multiple words.
	Upper Case 1: THIS IS A SAMPLE STRING.
	Upper Case 2: COMPLEX STRING WITH MULTIPLE WORDS.
	Sentence Case 1: This is a sample string.
	Sentence Case 2: Complex string with multiple words.
	Capitalize Each Word 1: This Is A Sample String.
	Capitalize Each Word 2: Complex String With Multiple Words.
	Toggle Case 1: tHIS IS A SAMPLE STRING.
	Toggle Case 2: Complex sTRING WITH mULTIPLE wORDS.
*/

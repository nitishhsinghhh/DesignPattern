#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum ConversionType {
	CT_LowerCase,
	CT_UpperCase,
	CT_Capitalize,
	CT_SentenceCase,
	CT_ToggleCase
};

// Library Classes

class StringConversion {
public:
	virtual string convertString(string s) = 0;	// pure virtual class
	virtual ~StringConversion() {}
};

class ClasstoLowerCase : public StringConversion {
public:
	string convertString(string s) {
		for (auto& c : s)
			if ('A' <= c && c <= 'Z')
				c = c - 'A' + 'a';
		return s;
	}
};

class ClasstoUpperCase : public StringConversion {
public:
	string convertString(string s) {
		for (auto& c : s)
			if ('a' <= c && c <= 'z')
				c = c - 'a' + 'A';
		return s;
	}
};

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

class Client {
public:
	Client() : pstringConversion(nullptr) {}

	void BuildStringConversion(ConversionType conversionType) {
		StringConversionFactory* scf = new StringConversionFactory();
		pstringConversion = scf->build(conversionType);

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
  
  // Lower case
	Client* pClient = new Client();
	pClient->BuildStringConversion(CT_LowerCase);
	pClient->getConversionType()->convertString("aBGDFDYIwwerr");

	// Upper Case
	pClient->BuildStringConversion(CT_UpperCase);
	pClient->getConversionType()->convertString("aBGDFDYIwwerr");

	// Sentense Case
	pClient->BuildStringConversion(CT_SentenceCase);
	pClient->getConversionType()->convertString("aBGDF DY Iwwe rr");

	// Capitalize
	pClient->BuildStringConversion(CT_Capitalize);
	pClient->getConversionType()->convertString("aBGDF dfDYI fww gerr");

	// Toggle Case
	pClient->BuildStringConversion(CT_ToggleCase);
	pClient->getConversionType()->convertString("aBGD FDddd YIwTGtSE werr");
  
	delete pClient;
	return 0;
}

#include <string>
#include <iostream>
using namespace std;

string getFirstWord(string theString);
string getLastWord(string theString);
string extractWord(string& theString);
bool isUppercase(string theString);
string makeUppercase(string theString);
bool hasMultipleExclamations(string theString);
bool isGibberishWord(string theString);
bool isSpam(string theSubject, string theBody);

int spamScore = 0;

string getFirstWord(string theString)
{
	int length = theString.length();
	string theResult = "";
	for (int i = 0; i < length; i++)
	{
		if (isalpha(theString[i]))
			theResult += theString[i];
		if (theString[i] == ' ' || isalpha(theString[i]) == 0)
			i = length;
	}
	return theResult;
}

string getLastWord(string theString)
{
	int length = theString.length();
	string theResult = "";
	int numSpaces = 0;
	int finalStart = 0;
	for (int i = 0; i < length; i++)
	{
		if (theString[i] == ' ')
			numSpaces += 1;
	}
	for (int i = 0; numSpaces > 0; i++)
	{
		if (theString[i] == ' ')
			numSpaces -= 1;
		if (numSpaces == 0)
			finalStart = i + 1;
	}
	theResult = theString.substr(finalStart,length);
	return theResult;
}

int wordCounter(string theString)
{
	int wordCounter = 0;
	do {
		extractWord(theString);
		wordCounter++;
	}
	while (theString.length() > 0);
	return wordCounter;
}

string extractWord(string& theString)
{
	int counter = 1;
	for (int i = 0; i < counter; i++)
	{
		if (isalpha(theString[i]) == 0)
			counter++;
		else
			i = counter;
	}
	theString.erase(0, (counter - 1));
	string firstWord = getFirstWord(theString);
	int length = theString.length();
	int letterCounter = 0;
	for (int i = 0; i < length; i++)
	{
		if (theString[i] != ' ')
			letterCounter++;
		if (theString[i] == ' ')
			i = length;
	}
	theString.erase(0, letterCounter);
	return firstWord;
}

bool isUppercase(string theString)
{
	int length = theString.length();
	int lowerCounter = 0;
	for (int i = 0; i != length; i++)
		if (isupper(theString[i]) == 0)
			lowerCounter++;
	if (lowerCounter > 0)
		return false;
	else 
		return true;
}

string makeUppercase(string theString)
{
	int length = theString.length();
	string theResult = "";
	for (int i = 0; i != length; i++)
	{
		if (isalpha(theString[i]))
			theResult += toupper(theString[i]);
		else
			theResult += theString[i];
	}
	return theResult;
}

bool hasMultipleExclamations(string theString)
{
	int length = theString.length();
	int exclamationCounter = 0;
	for (int i = 0; i != length; i++)
	{
		if (exclamationCounter == 3)
			i = length - 1;
		if (theString[i] == '!')
			exclamationCounter++;
		else
			exclamationCounter = 0;
	}
	if (exclamationCounter >= 3)
		return true;
	else
		return false;
}

bool isGibberishWord(string theString)
{
	int length = theString.length();
	int consonantCounter = 0;
	for (int i = 0; i != length; i++)
	{
		if (consonantCounter > 3)
			i = length - 1;
		if (isalpha(theString[i]) && (
			theString[i] != 'a' &&
			theString[i] != 'e' &&
			theString[i] != 'i' &&
			theString[i] != 'o' &&
			theString[i] != 'u' &&
			theString[i] != 'A' &&
			theString[i] != 'E' &&
			theString[i] != 'I' &&
			theString[i] != 'O' &&
			theString[i] != 'U'))
			consonantCounter++;
		else
			consonantCounter = 0;
	}
	if (consonantCounter > 3)
		return true;
	else
		return false;
}

int uppercaseSubjectTest(string theSubject)
{
	string tempWord = "";
	int score = 0;
	float upperCount = 0;
	float wordCount = wordCounter(theSubject);
	const double UPPER_THRESHOLD = 0.90;

	for (int i = 0; i < wordCount; i++)
	{
		tempWord = extractWord(theSubject);
		if (isUppercase(tempWord))
		{
			upperCount++;
		}
	}

	float percentUpper = upperCount / wordCount;
	
	if (percentUpper > UPPER_THRESHOLD)
		score = 30;

	return score;
}

int consonantSubjectTest(string theSubject)
{
	int score = 0;
	string tempLastWord = getLastWord(theSubject);

	if (isGibberishWord(tempLastWord))
		score += 40;

	return score;
}

int exclamationSubjectTest(string theSubject)
{
	int score = 0;

	if (hasMultipleExclamations(theSubject))
		score += 20;

	return score;
}

int uppercaseBodyTest(string theBody)
{
	int score = 0;
	
	string tempBodyWord = "";
	float bodyUpperCount = 0;
	float bodyWordCount = 1;
	float const UPPER_BODY_THRESHOLD = 0.50;

	for (int i = 0; i < bodyWordCount; i++)
	{
		tempBodyWord = extractWord(theBody);
		if (isUppercase(tempBodyWord))
		{
			bodyUpperCount++;
			bodyWordCount++;
		}
		else
			bodyWordCount++;
	}

	float percentBodyUpper = bodyUpperCount / bodyWordCount;
	
	if (percentBodyUpper > UPPER_BODY_THRESHOLD)
		score += 40;

	return score;
}

bool isSpam(string theSubject/*, string theBody*/)
{
	// > 90% uppercase words in subject test

	spamScore += uppercaseSubjectTest(theSubject);

	// last word > 3 consecutive consonants in subject test

	spamScore += consonantSubjectTest(theSubject);

	// > 2 consecutive exclamations in subject test

	spamScore += exclamationSubjectTest(theSubject);

	// body has > 0 words, 50% of words uppercase test

	//spamScore += uppercaseBodyTest(theBody);

	// special words test
	
	

	// score calculator

	if (spamScore > 100)
		return true;
	else
		return false;
}

int main()
{
	int spamCounter = 0;
	int legitCounter = 0;
	bool repeatTest = true;

	do {
		cout << "Enter the subject line of the email: ";
		string subject = "";
		getline(cin, subject);

		//cout << "Enter the body of the email.  Press Enter on an empty line to finish.";
		//string body;
		//getline(cin, body);

		if (isSpam(subject))
		{
			spamCounter++;
			cout << "This email is classified as spam, because its spam score is " << spamScore << endl;
		}
		else
		{
			legitCounter++;
			cout << "This email is classified as legitimate, because its spam score is " << spamScore << endl;
		}

		bool repeatResponse = true;
		do {

			cout << "Would you like to classify another email (y or n)? ";
			string response = "";
			cin >> response;
			if (response == "y")
			{
				repeatTest = true;
				repeatResponse = false;
			}
			if (response == "n")
			{
				repeatTest = false;
				cout << "Number of spam messages: " << spamCounter << endl;
				cout << "Number of legitimate messages: " << legitCounter << endl;
				repeatResponse = false;
			}
			if (response != "y" && response != "n")
			{
				cout << "Please enter y or n." << endl;
				repeatResponse = true;
			}
		}
		while (repeatResponse == true);
	}
	while (repeatTest == true);
	return 0;
}
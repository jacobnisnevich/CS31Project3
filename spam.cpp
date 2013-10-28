#include <string>
#include <iostream>
using namespace std;

// function prototyping

string getFirstWord(string theString);
string getLastWord(string theString);
int wordCounter(string theString);
string extractWord(string& theString);
bool isUppercase(string theString);
string makeUppercase(string theString);
bool hasMultipleExclamations(string theString);
bool isGibberishWord(string theString);
int uppercaseSubjectTest(string theSubject);
int consonantSubjectTest(string theSubject);
int exclamationSubjectTest(string theSubject);
int uppercaseBodyTest(string theBody);
int specialWordBodyTest(string theBody);
bool isSpam(string theSubject, string theBody);

// declaration/initialization of spamScore counter

int spamScore = 0;

// function that copies the first word from a string and returns it

string getFirstWordImpl(string theString, int& lastPos)
{
	lastPos = 0;
	int length = theString.length();
	int i = 0;
	string theResult = "";
	for ( ; i < length; i++)
	{
		if (isalpha(theString[i]))
		{
			theResult += theString[i];
		}
		if ((theString[i] == ' ' || !(isalpha(theString[i]))) && theResult != "")
		{
			break;
		}
	}
	lastPos = i;
	return theResult;
}

string getFirstWord(string theString)
{
	int lastPos = 0;
	return getFirstWordImpl(theString, lastPos);
}

// function that copies the last word from a string and returns it

string getLastWord(string theString)
{
	int length = theString.length();
	string theResult = "";
	string intermediate = "";
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
	intermediate = theString.substr(finalStart,length);
	int lengthIntermediate = intermediate.length();
	for (int i = 0; i < lengthIntermediate; i++)
	{
		if (isalpha(intermediate[i]))
			theResult += intermediate[i];
	}
	return theResult;
}

// function that counts and returns the number of words in a string

int wordCounter(string theString)	
{
	int wordCounter = 0;
	do {
		extractWord(theString);
		wordCounter++;
	}
	while (theString.length() > 0);
	return (wordCounter - 1);
}

// function that copies and removes the first word from a string and returns it

string extractWord(string& theString)
{
	int lastPos = 0;
	string firstWord = getFirstWordImpl(theString, lastPos);
	theString = theString.substr(lastPos);
	return firstWord;
}

// function that tests if a string is uppercase

bool isUppercase(string theString)
{
	int length = theString.length();
	int lowerCounter = 0;
	for (int i = 0; i != length; i++)
		if (isalpha(theString[i]) && !(isupper(theString[i])))
			lowerCounter++;
	if (lowerCounter > 0)
		return false;
	else 
		return true;
}

// function that makes a string uppercase

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

// function that tests if a string has three or more exclamations in a row

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

// function that tests if a string has four or more consecutive consonantsT

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

// function that tests if the subject is 90%+ uppercase

int uppercaseSubjectTest(string theSubject)
{
	string tempWord = "";
	int score = 0;
	int upperCount = 0;
	int wordCount = wordCounter(theSubject);
	const double UPPER_THRESHOLD = 0.90;

	for (int i = 0; i < wordCount; i++)
	{
		tempWord = extractWord(theSubject);
		if (isUppercase(tempWord))
		{
			upperCount++;
		}
	}

	float percentUpper = (float)upperCount / (float)wordCount;
	
	if (percentUpper > UPPER_THRESHOLD)
		score = 30;

	return score;
}

// function that tests if the subject has a gibberish last word

int consonantSubjectTest(string theSubject)
{
	int score = 0;
	string tempLastWord = getLastWord(theSubject);

	if (isGibberishWord(tempLastWord))
		score = 40;

	return score;
}

// function that tests if the subject has three or more exclamation marks in a row

int exclamationSubjectTest(string theSubject)
{
	int score = 0;

	if (hasMultipleExclamations(theSubject))
		score = 20;

	return score;
}

// function that tests if the body is 50%+ uppercase

int uppercaseBodyTest(string theBody)
{
	int score = 0;
	
	string tempBodyWord = "";
	int bodyUpperCount = 0;
	int bodyWordCount = wordCounter(theBody);
	float const UPPER_BODY_THRESHOLD = 0.50;

	for (int i = 0; i < bodyWordCount; i++)
	{
		tempBodyWord = extractWord(theBody);
		if (isUppercase(tempBodyWord))
		{
			bodyUpperCount++;
		}
	}

	float percentBodyUpper = (float)bodyUpperCount / (float)bodyWordCount;
	
	if (percentBodyUpper > UPPER_BODY_THRESHOLD)
		score = 40;

	return score;
}

// function that checks for any of 13 special words in the body

int specialWordBodyTest(string theBody)
{
	int score = 0;

	string tempBodyWord = "";
	string lowerWord= "";
	int specialWordCounter = 0;
	int bodyWordCount = wordCounter(theBody);

	for (int i = 0; i < bodyWordCount; i++)
	{
		tempBodyWord = extractWord(theBody);
		int length = tempBodyWord.length();
		lowerWord = "";
		for (int i = 0; i < length; i++)
			lowerWord += tolower(tempBodyWord[i]);
		if (lowerWord == "buy" || 
			lowerWord == "cheap" ||
			lowerWord == "click" ||
			lowerWord == "diploma" ||
			lowerWord == "enlarge" ||
			lowerWord == "free" ||
			lowerWord == "lonely" ||
			lowerWord == "money" ||
			lowerWord == "now" ||
			lowerWord == "offer" ||
			lowerWord == "only" ||
			lowerWord == "pills" ||
			lowerWord == "sex")
		{
			specialWordCounter++;
		}
	}

	score = specialWordCounter * 5;

	return score;
}

// function that combines the subject and body tests and returns whether an email is spam or not

bool isSpam(string theSubject, string theBody)
{
	// > 90% uppercase words in subject test

	spamScore += uppercaseSubjectTest(theSubject);

	// last word > 3 consecutive consonants in subject test

	spamScore += consonantSubjectTest(theSubject);

	// > 2 consecutive exclamations in subject test

	spamScore += exclamationSubjectTest(theSubject);

	// body has > 0 words, 50% of words uppercase test

	spamScore += uppercaseBodyTest(theBody);

	// special words test
	
	spamScore += specialWordBodyTest(theBody);

	// score calculator

	if (spamScore > 100)
		return true;
	else
		return false;
}

int main()
{
	// declaration and initialization of spam and legitimate email counters
	int spamCounter = 0;
	int legitCounter = 0;
	bool repeatTest = true;

	// main loop that continues until user stops testing emails

	do {

		// clears getline input from cin

		cin.clear();
		cin.sync();

		// subject line input

		cout << "Enter the subject line of the email: ";
		string subject = "";
		getline(cin, subject);

		// clears getline input from cin

		cin.clear();
		cin.sync();

		// email body input

		cout << "Enter the body of the email.  Press Enter on an empty line to finish. " << endl;

		// stores lines of body into body variable

		string temp = "";
		string body = "";
		do	{
			cin.clear();
			cin.sync();
			getline(cin, temp);
			body += temp + " ";
		}
		while (!temp.empty());

		// spam test that returns either spam or legitimate result

		if (isSpam(subject, body))
		{
			spamCounter++;
			cout << "This email is classified as spam, because its spam score is " << spamScore << endl;
		}
		else
		{
			legitCounter++;
			cout << "This email is classified as legitimate, because its spam score is " << spamScore << endl;
		}

		// loop that checks if you want to classify additional emails

		bool repeatResponse = true;
		do {
			cin.clear();
			cin.sync();

			cout << "Would you like to classify another email (y or n)? ";
			string response = "";
			cin >> response;
			if (response == "y")
			{
				repeatTest = true;
				repeatResponse = false;
				spamScore = 0;
			}
			if (response == "n")
			{
				repeatTest = false;
				cout << endl;
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
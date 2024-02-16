#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct fileData
{
	int letter[26] = { 0 }; //26 rows for each letter
};

void openFile(string fileName, string outputName);
void count(ifstream& inFile, ofstream& outFile);
void printResults(ofstream& outFile, const fileData uppercase, const fileData lowercase, const int totalLetters);

int main()
{
	string fileName;
	string outputName;

	cout << "Anthony Cantu\t" << "L3-6\t" << "L3-6.exe" << endl;

	cout << "Enter the name of the input file: ";
	cin >> fileName;
	cout << endl;
	cout << "Enter the name of the output file: ";
	cin >> outputName;
	openFile(fileName, outputName);
	
	cout << "Press any key to Exit.";
	char q;
	cin.ignore(2, '\n');
	cin.get(q);
	return 0;
}

void openFile(string fileName, string outputName)
{
	ifstream inFile;
	ofstream outFile;

	inFile.open(fileName);
	outFile.open(outputName);

	if (!inFile.is_open() || !outFile.is_open())
	{
		cout << "ERROR: Unable to open file name provided. Application Terminated." << endl;
		cout << "Press any key to Exit.";
		char q;
		cin.ignore(2, '\n');
		cin.get(q);
		exit(1);
	}
	count(inFile, outFile);
}

void count(ifstream& inFile, ofstream& outFile)
{
	fileData uppercase;
	fileData lowercase;
	string word;
	int totalLetters = 0;
	char ch;

	while (inFile >> word) //Continue loop until reach end of file
	{
		for (int i = 0; i < word.length(); i++)
		{
			ch = word[i];
			if (isalpha(ch) && isupper(ch))
			{
				uppercase.letter[ch - 'A']++;
				totalLetters++;
			}
			else if (isalpha(ch) && islower(ch))
			{
				lowercase.letter[ch - 'a']++;
				totalLetters++;
			}
		}
	}
	inFile.close();
	printResults(outFile, uppercase, lowercase, totalLetters);
}

void printResults(ofstream& outFile, const fileData uppercase, const fileData lowercase, const int totalLetters)
{
	double percOfOccurence = 0.00;

	cout << endl; //Line Break
	cout << "Total number of letters input -->: " << totalLetters << endl;
	outFile << setfill(' ');
	outFile << fixed << showpoint << setprecision(2);
	outFile << setw(9) << left << "Letter"
		<< setw(8) << left << "Count"
		<< "Percentage of Occurence" << endl;

	for (int i = 0; i < 26; i++)
	{
		percOfOccurence = (static_cast<double>(uppercase.letter[i]) / totalLetters) * 100;
		outFile << setw(2) << "" << static_cast<char>(65 + i)
			<< setw(11) << right << uppercase.letter[i]
			<< setw(16) << right << percOfOccurence << "%" << endl;
	}

	for (int i = 0; i < 26; i++)
	{
		percOfOccurence = (static_cast<double>(lowercase.letter[i]) / totalLetters) * 100;
		outFile << setw(2) << "" << static_cast<char>(97 + i)
			<< setw(11) << right << lowercase.letter[i]
			<< setw(16) << right << percOfOccurence << "%" << endl;
	}
	outFile.close();
}
//Name- Tasfique Enam
//Student ID- 5886429
//LabTask3 Q2

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int elementCount, menu1_count=0;
const int elementNo=110;

struct ChemicalElement
{
	int atomicNumber;
	char name[100];
	char symbol[3];
	float mass;
};
ChemicalElement elements[elementNo];
ChemicalElement chemicalElement;

fstream file;
ofstream writeBinaryFile("binaryChemical.txt", ios::out | ios::binary);

void readWrite() // Read records from the text file and write to binary file.
{
	if(menu1_count==0)
	{
		file.open("chemicalElements.txt", ios::in);
		if(file.is_open())
		{
			elementCount=0;
			while(!file.eof()) //to check the file has an end or not.
			{
				file >> elements[elementCount].mass >> elements[elementCount].name >> elements[elementCount].symbol >> elements[elementCount].atomicNumber;
				elementCount++;
			}
			for(int i=0; i<elementCount; i++)
			{
				cout << elements[i].mass << "  " << elements[i].name << "  " << elements[i].symbol << "  " << elements[i].atomicNumber << endl;
			}
			writeBinaryFile.write((char*)&elements, sizeof(ChemicalElement)*elementNo); //if u r using array u have to multiply by the length.
			cout << "Data have been Successfully Written!" << endl;
			cout << endl;
		}
		else
		{
			cout << "File was not Found!" << endl;
			cout << endl;
		}
		file.close();
		writeBinaryFile.close();
		menu1_count++;
	}
	else
	{
		cout << "Data have been written already!" << endl;
		cout << endl;
	}
}

bool findValue() // find by name or symbol
{
	char find[200]; //it the size of array which is 200
	ifstream readFile("binaryChemical.txt", ios::in | ios::binary);
	if(readFile.good())
	{
		readFile.read((char*)&elements, sizeof(elements)*elementNo);

		cout << "Insert Name or Element letter : ";
		cin >> find;

		for(int i=0; i<elementNo; i++)
		{
			if(strcmp(find,elements[i].name)==0||strcmp(find,elements[i].symbol)==0)
			{
				cout << "Search Result." << endl;
				cout << "Mass : " << elements[i].mass << endl;
				cout << "Name : " << elements[i].name << endl;
				cout << "Symbol : " << elements[i].symbol << endl;
				cout << "Atomic Number : " << elements[i].atomicNumber << endl;
				cout << endl;
				readFile.close();
				return true;
			}
		}
		readFile.close();
		return false;
	}
	else
	{
		cout << "File failed to load." << endl;
		cout << endl;
	}
}

void displayData1() // Display data with atomic mass greater than the value passed to it
{
	ifstream readFile("binaryChemical.txt", ios::in | ios::binary);
	int inputValue;
	if(readFile.good())
	{
		readFile.read((char*)&elements, sizeof(elements)*elementNo);
		cout << "Input a number for atomic mass : ";
		cin >> inputValue;
		while(inputValue<0)
		{
			cout << "Wrong value, input a number for atomic mass : ";
			cin >> inputValue;
		}
		cout << endl;

		cout << "The data with atomic mass greater than the value passed to it." << endl;
		for(int i=0; i<elementNo; i++)
		{
			if(elements[i].mass > inputValue)
			{
				cout << elements[i].mass << "  " << elements[i].name << "  " << elements[i].symbol << "  " << elements[i].atomicNumber << endl;
			}
		}
		cout << endl;
		readFile.close();
	}
	else
	{
		cout << "Failed to load file" << endl;
		cout << endl;
	}
}

void displayData2() // Display data between two given atomic number
{
	ifstream readFile("binaryChemical.txt", ios::in | ios::binary);
	int inputValue1, inputValue2;
	if(readFile.good())
	{
		readFile.read((char*)&elements, sizeof(elements)*elementNo);
		cout << "Input the first atomic number : ";
		cin >> inputValue1;

		while(inputValue1<0)
		{
			cout << "Wrong input, input the first atomic number : ";
			cin >> inputValue1;
		}

		cout << "Input the second atomic number : ";
		cin >> inputValue2;

		while(inputValue2<0)
		{
			cout << "Wrong input, input the second atomic number : ";
			cin >> inputValue2;
		}

		cout << "Data between two given atomic number." << endl;
		for(int i=0; i<elementNo; i++)
		{
			if((elements[i].atomicNumber>=inputValue1&&elements[i].atomicNumber<=inputValue2)||
			(elements[i].atomicNumber<=inputValue1&&elements[i].atomicNumber>=inputValue2))
			{
				cout << elements[i].mass << "  " << elements[i].name << "  " << elements[i].symbol << "  " << elements[i].atomicNumber << endl;
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Failed to load file" << endl;
		cout << endl;
	}
	readFile.close();
}

void displayData3() // Display data given a record number
{
	int byte_size;
	int recordNumber;
	ifstream readFile;
	readFile.open("binaryChemical.txt", ios::in | ios::binary);
	readFile.seekg(0, ios::end);
	byte_size=readFile.tellg();
	cout << "Number of records in file : " << byte_size/sizeof(ChemicalElement) << endl;
	cout << "Input the record number to display : ";
	cin >> recordNumber;
	if(recordNumber < 1 || (recordNumber > byte_size/sizeof(ChemicalElement)))
	{
		cout << "The record not existing here!" << endl;
	}
	else
	{
		readFile.seekg(((recordNumber-1)*sizeof(ChemicalElement)), ios::beg);
		readFile.read((char*)&elements, sizeof(elements)*elementNo);
		cout << elements[recordNumber-1].mass << "  " << elements[recordNumber-1].name << "  " << elements[recordNumber-1].symbol << "  " << elements[recordNumber-1].atomicNumber << endl;
		cout << endl;
	}
	readFile.close();
}

int main()
{
    cout << "Read records from the text file and write to binary file"<< endl;
	readWrite();
	cout << "Search by name or symbol"<< endl;
	findValue();
	cout << "Display data with atomic mass greater than the value passed to it"<< endl;
	displayData1();
	cout << "Display data between two given atomic number"<< endl;
	displayData2();
	cout << "Display data given a record number"<< endl;
	displayData3();


	return 0;
}

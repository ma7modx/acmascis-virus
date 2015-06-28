#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "dirent.h"
using namespace std; 

int StringToInt(string str)
{
	stringstream ss;
	ss << str;
	int num;
	ss >> num;
	return num;
}
string IntToString(int num)
{
	stringstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;
}

//--
int GetFileIndex(int argc, char* argv[])
{
	/* 
	each time the program send the number of the process to itself as an argument 
	except at the first time there's no passed arguments 
	TODO -> return the argument 
	*/
	if (argc > 1)
	{
		cout << "Argument : " << string(argv[1]) << endl;
		return StringToInt(string(argv[1]));
	}
	return 0;
}

//--
string settingTheDesiredPath(string currentFilePath)
{
	/*
	both files have the same name but with different extensions
	all files in the desired path are .bin
	TODO -> return the desired file path
	*/

}
vector<string> getFiles(char* path)
{
	vector<string> files;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			printf("FILE : %s\n", ent->d_name);
			files.push_back(string(ent->d_name));
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
	}
	return files; 
}

streampos size;
char* readFromFile(fstream* myfile)
{
	// to store the data
	char* memblock; 

	if (myfile->is_open())
	{
		myfile->seekg(0, ios::end);
		streampos end = myfile->tellg();
		myfile->seekg(0, ios::beg);
		streampos begin = myfile->tellg();
		size = end - begin;
		memblock = new char[size];
		myfile->read(memblock, size);

		return memblock;
	}
	else
		return NULL;
}

//--
void writeInFile(char* data, fstream* myfile)
{
	/*
	the data of the desired file has been stored in variable [data]
	to know more check function [readFromFile]
	now you should exchange the corrupted file with these data
	TODO -> write data into myfile
	*/
	if (myfile->is_open())
	{
		myfile->seekp(0, ios::beg);
		myfile->write(data, size);
	}
}

//--
void programRecall(int fileIndex)
{
	/*
	TODO -> pass a command to the command prompt to run the virus again 
			BUT with incremented file index 
	*/
	string command = "start C:\\virus\\Release\\virus.exe " + IntToString(fileIndex + 1);
	system("pause");
	system(command.c_str());
}

int main(int argc ,char* argv[])
{
	// brain folder that contains the corrupted files
	char* folderPath = "C:\\virus\\virus\\Brain";

	// get the files within the folder
	vector<string> files = getFiles(folderPath);

	// choose the file that being modified
	int fileIndex = GetFileIndex(argc, argv);
	cout << "changing : " << files[fileIndex] << endl; 

	// setting the files directory
	string currentFile = "C:\\virus\\virus\\Brain\\" + files[fileIndex];
	//--
	string desiredFile = "C:\\virus\\virus\\New folder (2)\\" + files[fileIndex];
	
	// open the files in binary format
	fstream theCurrentFile = fstream(currentFile, ios::binary | ios::out);
	fstream theDesiredFile = fstream(desiredFile, ios::binary | ios::in);
	
	// exchange the data 
	char* data = readFromFile(&theDesiredFile);
	writeInFile(data, &theCurrentFile);

	// close and save 
	theDesiredFile.close();
	theCurrentFile.close();

	//recall the program from the command prompt in a new process with incremented argument
	programRecall(fileIndex);
	
}
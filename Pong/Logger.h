//===================Logger.h==========================
// Purpose:			Logger | Creating log and print text to console
//
//=====================================================

#pragma once
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class CLogger
{
public:
	ofstream Log_File;
	//Log Output for creating log file
	string LogOutput;
	//Type of message
	enum TypeMessage
	{
		Debug,
		Warning,
		Error,
		FatalError
	};

	//Print func for debug and print text on LogOutput
	void Print(string Text, TypeMessage type);
	void CreateLogFile();
	void ShowErrorMsg();
};

extern CLogger *logger;

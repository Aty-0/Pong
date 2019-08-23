//===================Logger.cpp========================
// Purpose:			Logger | Creating log and print text to console
//
//=====================================================

#include "Logger.h"
#include "Game.h"

//Print on console and log output 
void CLogger::Print(string Text, TypeMessage type)
{
	switch (type)
	{
	case CLogger::Debug:
		cout << "Debug: " << Text << endl;
		LogOutput += string("\nDebug: ") + string(Text);
		break;
	case CLogger::Warning:
		cout << "Warning: " << Text << endl;
		LogOutput += string("\nWarning: ") + string(Text);
		break;
	case CLogger::Error:
		cout << "Error: " << Text << endl;
		LogOutput += string("\nError: ") + string(Text);
		game->LOOP_UPDATE = false;
		break;
	case CLogger::FatalError:
		cout << "FatalError: " << Text << endl;
		LogOutput += string("\nFatalError: ") + string(Text);
		game->LOOP_UPDATE = false;
		break;
	}

}

//Create a Log File
void CLogger::CreateLogFile()
{
	Log_File.open("Log.log");
	//Check on error
	if (!Log_File)
		std::cout << "Can't create log file!" << std::endl;

	Log_File << "Pong Log File\n";
	Log_File << "===================================================================\n";
	Log_File << LogOutput;
	Log_File.close();
}
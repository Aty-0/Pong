//===================Logger.cpp========================
// Purpose:			Logger | Creating log and print text to console
//
//=====================================================

#include "Logger.h"
#include "Game.h"
#include <windows.h>

//Print on console and log output 
void CLogger::Print(string Text, TypeMessage type)
{
	switch (type)
	{
	case CLogger::Debug:
		LogOutput += string("\nDebug: ") + string(Text);
		break;
	case CLogger::Warning:
		LogOutput += string("\nWarning: ") + string(Text);
		break;
	case CLogger::Error:
		LogOutput += string("\nError: ") + string(Text);
		//game->LOOP_UPDATE = false;
		break;
	case CLogger::FatalError:
		LogOutput += string("\nFatalError: ") + string(Text);
		game->m_App_State = false;
		break;
	}
}

void CLogger::ShowErrorMsg()
{
	MessageBox(0, L"FATAL ERROR!\nSee log for details.", L"FATAL ERROR", 0);
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
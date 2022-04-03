/***
 *  BoostedBreak - BoostedBreakCAN Program
 *  
 *  main.cpp
 *  
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#include "stdafx.h"
#include "ConsoleInterface.h"
#include "PCANBasicDriver.h"
#include "BoostedBreakCAN.h"

#define BOOSTEDBREAKCAN_TITLE "BoostedBreak - BoostedBreakCAN "
#define BOOSTEDBREAKCAN_AUTHOR "- Created by Alexander Krysl (axkrysl47) "
#define BOOSTEDBREAKCAN_VERSION "v0.0.1"

#define CURSOR_TRANSMITMODE_ACTIVE 86, 1

void printTableHeader(BoostedBreakCAN* program);
void printTableHeaderTransmitMode(BoostedBreakCAN* program);

int main()
{
    char c;

    // Initialize User Interface
    ConsoleInit();

    ConsolePrint(BOOSTEDBREAKCAN_TITLE);
    ConsolePrint(BOOSTEDBREAKCAN_AUTHOR);
    ConsolePrint(BOOSTEDBREAKCAN_VERSION);
    ConsolePrint("\n");

    // Initialize CAN Driver
    PCANBasicDriver* driver = new PCANBasicDriver(PCAN_USBBUS1, PCAN_BAUD_250K, true);
    if (driver->GetIsInitialized() == false)
    {
        ConsolePrint("PCAN-Basic could not initialize. Please check the defines in the code.\n");
        ConsolePrint("Press any key to exit . . .\n");
        
        c = ConsoleInput();
        delete driver;
        return 0;
    }

    // Initialize CAN Driver Trace Configuration
    driver->ConfigureTrace(false, true, true, false, 2, 
        "C:\\BoostedBreak\\BoostedBreakCAN\\TraceFiles", 
        250);
    if (driver->GetIsTraceConfigured() == false)
    {
        ConsolePrint("PCAN-Basic could not configure trace. Please check the defines in the code.\n");
        ConsolePrint("Press Escape to exit, or press any other button to continue . . .\n");

        c = ConsoleInput();
        if (c == 27)
        {
            delete driver;
            return 0;
        }
    }
    else
    {
        ConsolePrint("PCAN-Basic successfully initialized.\n");
        ConsolePause();
    }

    driver->SetDriverThreadErrorLogging(false);
    driver->StartTrace();
    driver->StartDriverThread();
    ConsoleClear();

    // Initialize BoostedBreakCAN Program
    BoostedBreakCAN* program = new BoostedBreakCAN(driver);
    
    printTableHeader(program);
    program->SetViewMode(VIEWMODE_TABLE);
    program->StartControlThread();

    // Control Loop
    while (true)
    {
        c = _getch();
        if (c == 65 || c == 97) // A key
        {
            program->SetViewMode(VIEWMODE_STREAM);
        }
        else if (c == 83 || c == 115) // S key
        {
            if (program->SetViewMode(VIEWMODE_TABLE) == true)
            {
                printTableHeader(program);
            }
        }
        else if (c == 68 || c == 100) // D key
        {
            program->SetViewMode(VIEWMODE_BRIEF);
        }
        else if (c == 81 || c == 113) // Q key
        {
            if (program->SetTransmitMode(TRANSMITMODE_NONE) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 87 || c == 119) // W key
        {
            if (program->SetTransmitMode(TRANSMITMODE_PINGONLY) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 69 || c == 101) // E key
        {
            if (program->SetTransmitMode(TRANSMITMODE_PINGPOWEROFF) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 82 || c == 114) // R key
        {
            if (program->SetTransmitMode(TRANSMITMODE_EMULATEESC) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 84 || c == 116) // T key
        {
            if (program->SetTransmitMode(TRANSMITMODE_EMULATESRB) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 89 || c == 121) // Y key
        {
            if (program->SetTransmitMode(TRANSMITMODE_EMULATEXRB) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 85 || c == 117) // U key
        {
            if (program->SetTransmitMode(TRANSMITMODE_BEAMBREAKSRB) == true)
            {
                printTableHeaderTransmitMode(program);
            }
        }
        else if (c == 46 || c == 62 ) // . key
        {
            program->DebugCommand();
        }
        else if (c == 27) // Escape key
        {
            break;
        }
    }

    // De-initialize Program.
    ConsolePrint("\n");
    program->StopControlThread();
    driver->StopDriverThread();
    delete program;
    delete driver;
    return 0;
}

void printTableHeader(BoostedBreakCAN* program)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    ConsolePrint(BOOSTEDBREAKCAN_TITLE);
    ConsolePrint(BOOSTEDBREAKCAN_VERSION);
    ConsolePrint("                                                                    Press [Escape] to Exit. \n");
    ConsolePrint("View Modes:     Stream[A] |  Table[S]   |     Brief[D]     |||  Active Transmit Mode:  \n");
    ConsolePrint("Transmit Modes:  None[Q]  | ESC Ping[W] | ESC Power Off[E] | Emulate ESC[R] | Emulate SRB[T] | Emulate XRB[Y] | BeamBreak SRB[U]\n");

    printTableHeaderTransmitMode(program);
}

void printTableHeaderTransmitMode(BoostedBreakCAN* program)
{
    uint8_t transmitMode = program->GetTransmitMode();

    if (transmitMode == TRANSMITMODE_NONE)
    {
        ConsolePrint("Off                        ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_PINGONLY)
    {
        ConsolePrint("Pinging...                 ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_PINGPOWEROFF)
    {
        ConsolePrint("Pinging Power Off...       ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_EMULATEESC)
    {
        ConsolePrint("Emulating ESC...           ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_EMULATESRB)
    {
        ConsolePrint("SRB not yet implemented.   ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_EMULATEXRB)
    {
        ConsolePrint("XRB not yet implemented.   ", CURSOR_TRANSMITMODE_ACTIVE);
    }
    else if (transmitMode == TRANSMITMODE_BEAMBREAKSRB)
    {
        ConsolePrint("Emulating SRB (BeamBreak)...", CURSOR_TRANSMITMODE_ACTIVE);
    }
}

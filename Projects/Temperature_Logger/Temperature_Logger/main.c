/*******************************************************************************
* Programm:   main.c
* Filename:   .c
*
* Autor:      Andrin Schaller
* Version:    1.0
* Datum:      25.05.2021
*
********************************************************************************
* Datum             Vers.    Kommentar / Änderungsgrund
* 25.05.2021        1.0      Initial Version
*
*
********************************************************************************
*
* Verwendungszweck: C-Schulung
*
* Beschreibung:
*
*
* Precondition:  -
*
* Postcondition: -
*
* Benötigte Libraries:
* - stdlib.h
* - stdio.h
* - time.h
* - string.h
* - Windwos.h
*
* Copyright (©) 2021 by Andrin Schaller, CH-6300 Zug
*******************************************************************************/

/*** Präprozessor Definitionen ************************************************/
#define _CRT_SECURE_NO_WARNINGS

/***  Include Files ***********************************************************/
#include <stdlib.h>  /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>   /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <time.h>    /* Zeitfunktionen */
#include <string.h>  /* Weitere String-Funktionen */
#include <Windows.h> /* Für Sleep() Funktion */

/***  Globale Deklarationen und Definitionen **********************************/
int read_path_loop = 1;
int read_com_loop = 1;
int read_main_loop = 1;
int read_loop = 1;

/***  Funktions-Deklarationen *************************************************/

// ------------------------- ERROR FUNCTIONS ----------------------------------

void error_PathNotFound() {

    printf("\nERROR reading/writing the file. Possible error causes: ");
    printf("\n\t- Path not found");
    printf("\n\t- File not writeable");
    printf("\n\t- File is opened by another user\n");
}
// end error: PathNotFound


void error_ComNotFound() {

    printf("\nERROR! COM Port not found.");
    printf("\nPlease make sure you provide the correct COM Port.\n");
}
// end error: PathNotFound


void error_FileNotWriteable(char* path, char* file_name, char* current_datetime) {

    printf("\n\n%s - ERROR writing the file\t\t@ %s", file_name, current_datetime);
    printf("\n\t\t\t\t\t\t\t\tPfad: %s", path);
}
// end error: FileNotWriteable


// ------------------------- CONSTANTS FUNCTIONS ----------------------------------


void pathDefinition(char* path, char* day_str, char* file_name) {

    strcat(path, "\\LogFile_");         // Connect strings
    strcat(path, day_str);              
    strcat(path, ".csv");

    strcat(file_name, day_str);
}
// end define path


void timeConstants(char* time_str, char* day_str, char* current_datetime) {
    time_t rawtime;
    struct tm* timeinfo;
    // end local variables

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_str, 100, "%H:%M Uhr", timeinfo);                     // Time for file input
    strftime(day_str, 100, "%y%m%d", timeinfo);                         // Date for file name
    strftime(current_datetime, 100, "%d.%m.%y, %H:%M:%S", timeinfo);    // Datetime for CMD
    // end time formatting
}
// end time constants


// ------------------------- MAIN FUNCTIONS ----------------------------------


void readPathInput(char* path_input) {
    printf("Please enter the path where the log file should be saved: ");
    scanf("%s", path_input);
}
// end read path input


void readComPathInput(char* com_path) {
    printf("\nPlease enter the COM port where the ELOB-board is pluged in: ");
    scanf("%s", com_path);
}
// end read path input


void copyString(char* original, char* copy) {
    int i;
    for (i = 0; original[i] != '\0'; i++) {     // Iteration through every array element
        copy[i] = original[i];                  // Copy original element into copy element
    }
    copy[i] = '\0';
}
// end copy string


void checkFile(FILE* fptr, char* path_check) {
    fptr = fopen(path_check, "a");              // open file as "append" -> if not existing: create file

    if (fptr == NULL) {                         // if path doesn't exist, no permissions to create/write file, file is already open, ...
        error_PathNotFound();

        printf("\n");
        return;
        // end throw error
    }
    fclose(fptr);
    printf("\nPath selected successfully.\n");

    read_path_loop = 0;
}
// end checkFile


void checkSerialPort(char* com_path) {
    HANDLE hComm;
    char temp_com_path[100] = "";

    // end local variables

    strcat(temp_com_path, "\\\\.\\");
    strcat(temp_com_path, com_path);

    hComm = CreateFileA(temp_com_path,      // Port name               
        GENERIC_READ,                       // Read only
        0,                                  // No Sharing
        NULL,                               // No Security
        OPEN_EXISTING,                      // Open existing port only
        0,                                  // Non Overlapped I/O
        NULL);                              // Null for Comm Devices
    // end create virtual file

    if (hComm == INVALID_HANDLE_VALUE) {    // check if COM port exists / is available to open
        error_ComNotFound();
        return;
    }
    CloseHandle(hComm);                     // close virtual file

    read_com_loop = 0;
}


void readSerialPort(char* buffer, char* com_path) {
    HANDLE hComm;
    DCB Dcb;

    char temp_com_path[100] = "";
    int nbRead;
    // end local variables


    // end local variables

    strcat(temp_com_path, "\\\\.\\");
    strcat(temp_com_path, com_path);

    hComm = CreateFileA(temp_com_path,      // Port name               
        GENERIC_READ,                       // Read only
        0,                                  // No Sharing
        NULL,                               // No Security
        OPEN_EXISTING,                      // Open existing port only
        0,                                  // Non Overlapped I/O
        NULL);                              // Null for Comm Devices
    // end create virtual file
    
    GetCommState(hComm, &Dcb);              // Retrieves the current control settings for a specified communications device.

    Dcb.BaudRate = CBR_115200;              // BaudRate: the number of symbols transmitted per period
    Dcb.StopBits = ONESTOPBIT;
    Dcb.ByteSize = 8;
    Dcb.Parity = NOPARITY;
    Dcb.fParity = 0;
    Dcb.fOutxCtsFlow = 0;
    Dcb.fOutxDsrFlow = 0;
    Dcb.fDsrSensitivity = 0;
    Dcb.fTXContinueOnXoff = TRUE;
    Dcb.fOutX = 0;
    Dcb.fInX = 0;
    Dcb.fNull = 0;
    Dcb.fErrorChar = 0;
    Dcb.fAbortOnError = 0;
    Dcb.fRtsControl = RTS_CONTROL_DISABLE;
    Dcb.fDtrControl = DTR_CONTROL_DISABLE;
    // end config

    SetCommState(hComm, &Dcb);                  // Configures a communications device according to the specifications in a device-control block (a DCB structure)
    ReadFile(hComm, buffer, 10, &nbRead, NULL); // Reads data from the specified file or input/output (I/O) device
    CloseHandle(hComm);                         
    // end read and close file

}
// end read serial port

double getBufferAsDouble(char* buffer) {

    double temp_temperature;
    char* ptr;

    ptr = strchr(buffer, '░');                      // Removes every char after '░' ('°') char.
    if (ptr != NULL) {
        *ptr = '\0';
    }

    memmove(buffer, buffer + 1, strlen(buffer));    // Removes first element of string (always 'R')

    sscanf(buffer, "%lf", &temp_temperature);       // Converting string (char array) into double
    // end get temperature out of string

    return temp_temperature;
}
// end convert buffer


void writeFile(FILE* fptr, char* path, char* file_name, double avg_temperature, 
    char* current_datetime) {
    
    fptr = fopen(path, "a");                        // Opens file as "append"

    if (fptr == NULL) {

        error_FileNotWriteable(path, file_name, current_datetime);
        printf("\n");
    }
    // end check file

    else {

        fprintf(fptr, "%.1lf%c C; ;%s\n", avg_temperature, '°', current_datetime);          // Writes into file
        fclose(fptr);

        printf("\n\n%s - Success writing the file\t\t@ %s", file_name, current_datetime);
        printf("\n\t\t\t\t\t\t\t\Path: %s", path);
    }
}
// end write file


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {

    FILE* fptr;                 
    char path_input[100];       // Constant array -> doesn't get changed
    char path_check[100];       // Copy of 'path_input' -> to check if path is findable or if file is writeable if already exists
    char path[100];             // Copy of 'path_input' -> actual path

    char com_input[100];        // Input of COM Port path
    char check_com_path[100];   // Copy of 'com_input' -> to check if COM Port is available
    char com_path[100];         // Copy of 'com_input' -> actual COM Port path

    char time_str_check[100];
    char day_str_check[100];
    char current_datetime_check[100];
    char file_name_check[100] = "LogFile_";
    // end local variables

    while (read_path_loop) {                // loop to repeat file reading after writing file
        readPathInput(&path_input);
        copyString(path_input, path);
        copyString(path_input, path_check);
        // end Input

        timeConstants(&time_str_check, &day_str_check, &current_datetime_check);
        // end get time for checkFile

        pathDefinition(&path_check, &day_str_check, &file_name_check);
        // end get path for checkFile

        checkFile(&fptr, &path_check);
        // end check if file exists 
    }

    while (read_com_loop) {                 // loop to save COM Port data after every second
        readComPathInput(com_input);
        copyString(com_input, com_path);
        copyString(com_input, check_com_path);

        checkSerialPort(check_com_path);
    }
    // end check serial port

    // -------------------------------------------------------------------------------------

    printf("\nThe serial port is read out and the data get calculated...");
    while (read_main_loop) {
        int read_count = 0;

        double avg_temperature;
        double temp_temperature = 0;

        char time_str[100];
        char day_str[100];
        char current_datetime[100];
        char file_name[100] = "LogFile_";

        char buffer[100];

        timeConstants(&time_str, &day_str, &current_datetime);
        // end get time

        copyString(path_input, path);
        pathDefinition(&path, &day_str, &file_name);


        while ((read_count <= 59) && (read_loop)) {          // repeat 60 times (1 time per second)
            readSerialPort(&buffer, com_path);
            temp_temperature += getBufferAsDouble(&buffer);

            read_count++;
        }

        avg_temperature = temp_temperature / 60;             // repeat 60 times per minute when waiting 1s automatically per iteration.
        writeFile(&fptr, &path, &file_name, avg_temperature, &current_datetime);
        // end writeFile

        printf("\n");
    }

    return (0);
}
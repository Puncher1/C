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

    printf("\ERROR! COM Port not found.");
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

    strcat(path, "\\LogFile_");
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
    for (i = 0; original[i] != '\0'; i++) {
        copy[i] = original[i];
    }
    copy[i] = '\0';
}
// end copy string


void checkFile(FILE* fptr, char* path_check) {
    fptr = fopen(path_check, "a");  // open file as "append"

    if (fptr == NULL) {
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

    hComm = CreateFileA(temp_com_path,                //port name
        GENERIC_READ, //Read/Write
        0,                            // No Sharing
        NULL,                         // No Security
        OPEN_EXISTING,// Open existing port only
        0,            // Non Overlapped I/O
        NULL);        // Null for Comm Devices
    // end create virtual file

    if (hComm == INVALID_HANDLE_VALUE) {
        error_ComNotFound();
        return;
    }
    CloseHandle(hComm);

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

    hComm = CreateFileA(temp_com_path,                //port name
        GENERIC_READ, //Read/Write
        0,                            // No Sharing
        NULL,                         // No Security
        OPEN_EXISTING,// Open existing port only
        0,            // Non Overlapped I/O
        NULL);        // Null for Comm Devices
    // end create virtual file
    
    GetCommState(hComm, &Dcb);

    Dcb.BaudRate = CBR_115200;
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

    SetCommState(hComm, &Dcb);
    ReadFile(hComm, buffer, 10, &nbRead, NULL);
    CloseHandle(hComm);
    // end read and close file

}
// end read serial port

double getBufferAsDouble(char* buffer) {

    double temp_temperature;
    char* ptr;

    ptr = strchr(buffer, '░');  // remove every char after '░' ('°') char.
    if (ptr != NULL) {
        *ptr = '\0';
    }

    memmove(buffer, buffer + 1, strlen(buffer));    // remove first element of string (always 'R')

    sscanf(buffer, "%lf", &temp_temperature);       // converting string (char array) into double
    // end get temperature out of string

    return temp_temperature;
}
// end convert buffer


void writeFile(FILE* fptr, char* path, char* file_name, double avg_temperature, 
    char* current_datetime) {
    
    fptr = fopen(path, "a");        // open file as "append"

    if (fptr == NULL) {

        error_FileNotWriteable(path, file_name, current_datetime);
        printf("\n");
    }
    // end check file

    else {

        fprintf(fptr, "%.1lf%c C; ;%s\n", avg_temperature, 176, current_datetime); // 176 = °
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
    char path_input[100];       // constant array -> doesn't get changed
    char path_check[100];       // copy of 'path_input' -> to check if path is findable or if file is writeable if already exists
    char path[100];             // copy of 'path_input' -> actual path

    char com_input[100];
    char check_com_path[100];
    char com_path[100];

    char time_str_check[100];
    char day_str_check[100];
    char current_datetime_check[100];
    char file_name_check[100] = "LogFile_";

    // end local variables

    while (read_path_loop) {
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

    while (read_com_loop) {
        readComPathInput(com_input);
        copyString(com_input, com_path);
        copyString(com_input, check_com_path);

        checkSerialPort(check_com_path);
    }
    // end check serial port

    // ---------------------------------------------

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


        while ((read_count <= 1) && (read_loop)) {  // 60 times (1 time per second)
            readSerialPort(&buffer, com_path);
            temp_temperature += getBufferAsDouble(&buffer);

            read_count++;
        }

        avg_temperature = temp_temperature / 2;   // 120 times per minute when waiting 500ms per iteration.
        writeFile(&fptr, &path, &file_name, avg_temperature, &current_datetime);
        // end writeFile

        printf("\n");
    }

    return (0);
}
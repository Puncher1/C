/*******************************************************************************
* Programm:   main.c
* Filename:   .c
*
* Autor:      Andrin Schaller
* Version:    1.0
* Datum:      25.05.2021
*
********************************************************************************
* Datum             Vers.    Kommentar / �nderungsgrund
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
* Ben�tigte Libraries:
* - stdlib.h
* - stdio.h
*
* Copyright (�) 2021 by Andrin Schaller, CH-6300 Zug
*******************************************************************************/

/*** Pr�prozessor Definitionen ************************************************/
#define _CRT_SECURE_NO_WARNINGS

/***  Include Files ***********************************************************/
#include <stdlib.h> /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>  /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <time.h>   /* Zeitfunktionen */
#include <string.h> /* Weitere String-Funktionen */
#include <Windows.h> /* F�r Sleep() Funktion */

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/

// ------------------------- ERROR FUNKTIONEN ----------------------------------

void error_PathNotFound() {

    printf("\nFehler beim Erstellen/Schreiben der Datei! Moegliche Fehlerursachen: ");
    printf("\n\t- Pfad nicht gefunden");
    printf("\n\t- Datei nicht beschreibbar");
    printf("\n\t- Datei ist von einem anderen Benutzer geoeffnet");
}
// end error: PathNotFound


void error_FileNotWriteable(char* path, char* file_name, char* current_datetime) {

    printf("\n\n%s - Fehler beim Schreiben der Datei\t\t@ %s", file_name, current_datetime);
    printf("\n\t\t\t\t\t\t\t\tPfad: %s", path);
}
// end error: FileNotWriteable


// ------------------------- MAIN FUNKTIONEN ----------------------------------

void readInput(char *path_input) {
    printf("Bitte Pfad angeben: ");
    scanf("%s", path_input);
}
// end read Input


void checkFile(FILE *fptr, char *path_check) {
    fptr = fopen(path_check, "a");

    if (fptr == NULL) {
        error_PathNotFound();

        printf("\n");
        return;
        // end throw error
    }
    fclose(fptr);
    printf("\nPfad erfolgreich gewaehlt.");
}
// end checkFile


void writeFile(FILE* fptr, char* path, char* file_name, char* current_datetime) {
    fptr = fopen(path, "a");

    if (fptr == NULL) {
        error_FileNotWriteable(&path, &file_name, &current_datetime);
        printf("\n");
    }
    // end check file

    else {
        fprintf(fptr, "hallo;hallo;hallo\n");
        fclose(fptr);

        printf("\n\n%s erfolgreich beschrieben \t\t\t\t@ %s", file_name, current_datetime);
        printf("\n\t\t\t\t\t\t\t\tPfad: %s", path);
    }
    // end write file
}


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
    // end local constants

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_str, 100, "%H:%M Uhr", timeinfo);
    strftime(day_str, 100, "%y%m%d", timeinfo);
    strftime(current_datetime, 100, "%d.%m.%y, %H:%M:%S", timeinfo);
    // end time formatting
}
// end time constants


void copyString(char* original, char* copy) {
    int i;
    for (i = 0; original[i] != '\0'; i++) {
        copy[i] = original[i];
    }
    copy[i] = '\0';
}
// end copy string


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {
    FILE* fptr;
    char path_input[100];       // constant array -> doesn't get changed
    char path_check[100];       // copy of 'path_input' -> to check if path is findable or if file is writeable if already exists
    char path[100];             // copy of 'path_input' -> actual path

    char time_str_check[100];
    char day_str_check[100];
    char current_datetime_check[100];

    char file_name_check[100] = "LogFile_";
    // end local constants

    readInput(&path_input);
    copyString(path_input, path);
    copyString(path_input, path_check);
    // end Input

    timeConstants(&time_str_check, &day_str_check, &current_datetime_check);
    // end get time for checkFile

    pathDefinition(&path_check, &day_str_check, &file_name_check);
    // end get path for checkFile

    checkFile(&fptr, &path_check);
    // end check if file exists 


    // ...
    // end USB Port Input

    char time_str[100];
    char day_str[100];
    char current_datetime[100];

    char file_name[100] = "LogFile_";
    // end local constants

    timeConstants(&time_str, &day_str, &current_datetime);
    // end get time

    copyString(path_input, path);
    pathDefinition(&path, &day_str, &file_name);
    // end get path
    
   

    FILE* file_COM;
    file_COM = fopen("\\\\.\\COM4", "r");
    char data[100];

    if (file_COM == NULL) {
        printf("COM existiert nicht");
        return;
    }

    fread(data, 100, 1, file_COM);
    printf("%s\n", data);
    printf("\nData: %s", data);

    fclose(file_COM);

    //writeFile(&fptr, &path, &file_name, &current_datetime);
    // end writeFile


    printf("\n");
    return (0);
}
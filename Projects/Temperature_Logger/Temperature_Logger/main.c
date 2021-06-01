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
#include <stdlib.h> /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>  /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <time.h>   /* Zeitfunktionen */
#include <string.h> /* Weitere String-Funktionen */
#include <Windows.h> /* Für Sleep() Funktion */

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/


void readInput(char *path_input) {
    printf("Bitte Pfad angeben: ");
    scanf("%s", path_input);
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


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {

    FILE* fptr;
    char path_input[100];       // constant array -> doesn't get changed
    char path_check[100];       // copy of 'path_input' -> to check if path is findable or if file is writeable if already exists
    char path[100];             // copy of 'path_input' -> actual path

    char time_str[100];
    char day_str[100];
    char current_datetime[100];

    char file_name_check[100] = "LogFile_";

    readInput(&path_input);
    copyString(path_input, path);
    copyString(path_input, path_check);
    // end Input

    timeConstants(&time_str, &day_str, &current_datetime);
    // end get time


    pathDefinition(&path_check, &day_str, &file_name_check);
    // end get path

    fptr = fopen(path_check, "a");

    if (fptr == NULL) {
        error_PathNotFound();

        printf("\n");
        return;
        // end throw error
    }
    fclose(fptr);
    printf("\nPfad erfolgreich gewaehlt.");

    // end check if file exists 


    // ...
    // end USB Port Input
    int count = 0;
    char random_str[100];

    while (1) {
        if (count == 0) {
            strcpy(random_str, "test1;Lol\n");
        }
        else if (count == 1) {
            strcpy(random_str, "test2;Lol\n");
        }
        else if (count == 2) {
            strcpy(random_str, "test3;Lol\n");
        }

        char time_str[100];
        char day_str[100];
        char current_datetime[100];

        timeConstants(&time_str, &day_str, &current_datetime);
        // end get time

        char file_name[100] = "LogFile_";

        copyString(path_input, path);
        pathDefinition(&path, &day_str, &file_name);

        // end get path


        fptr = fopen(path, "a");
        // end open file

        if (fptr == NULL) {
            error_FileNotWriteable(&path, &file_name, &current_datetime);
            printf("\n");
            // end throw error
        }
        else {
            fprintf(fptr, random_str);
            fclose(fptr);

            printf("\n\n%s erfolgreich beschrieben \t\t\t\t@ %s", file_name, current_datetime);
            printf("\n\t\t\t\t\t\t\t\tPfad: %s", path);
        }
        // end write file
        count++;
        Sleep(10 * 1000);
    }

    printf("\n");
    return (0);
}
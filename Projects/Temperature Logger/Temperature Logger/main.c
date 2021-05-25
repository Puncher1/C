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

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/
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


void error_PathNotFound() {
    printf("\nFehler beim Erstellen/Schreiben der Datei! Moegliche Fehlerursachen: ");
    printf("\n\t- Pfad nicht gefunden");
    printf("\n\t- Datei nicht beschreibbar");
    printf("\n\t- Datei ist von einem anderen Benutzer geoeffnet");

    return;
}
// end error: PathNotFound

/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {


    // end USB Port Input

    char time_str[100];
    char day_str[100];
    char current_datetime[100];

    timeConstants(&time_str, &day_str, &current_datetime);
    // end get time

    char path[100];
    char file_name[100] = "LogFile_";

    printf("Bitte Pfad angeben: ");
    scanf("%s", &path);
    pathDefinition(&path, &day_str, &file_name);
    // get path

    FILE* fptr;
    fptr = fopen(path, "w");
    // end open file

    if (fptr == NULL) {
        error_PathNotFound();
        // end throw error
    }
    else {
        printf("\nPfad erfolgreich gefunden.");
        for (int i = 0; i <= 2; i++) {
            fprintf(fptr, "Hallo;Hallo\n");
        }
        fclose(fptr);
        printf("\n\n%s erfolgreich beschrieben @ %s", file_name, current_datetime);
        printf("\nPfad: %s", path);
    }
    // end write file


    printf("\n");
    return (0);
}




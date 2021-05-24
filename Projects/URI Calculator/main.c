/*******************************************************************************
* Programm:   main.c
* Filename:   .c
*
* Autor:      Andrin Schaller
* Version:    1.0
* Datum:      22.03.2020
*
********************************************************************************
* Datum             Vers.    Kommentar / Änderungsgrund
* 22.03.2020        1.0      Initial Version
*
*
********************************************************************************
*
* Verwendungszweck: C-Schulung
*
* Beschreibung: Ein Rechner, der auf Wunsch Spannung, Strom und Widerstand berechnen kann.
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
* Copyright (c) 2020 by Andrin Schaller
*******************************************************************************/

// Präprozessor Definitionen 
#define _CRT_SECURE_NO_WARNINGS

/***  Include Files ***********************************************************/
#include <stdlib.h>     /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>      /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <string.h>     /* Erweiterte String-Funktionen */
#include <Windows.h>    /* Gebraucht für Sleep() */
#include <math.h>
#include <ctype.h>

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/

void lowercase(char str[100]) {

    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}   


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {

    
    char einheit[100];

    int sleep_seconds = 1 * 1000;    // Sekunden * 1000 (Umwandlung Millisekungen -> Sekunden)

    int while_bool= 1;
    int first_time = 1;

    int repeat = 0;

    while (while_bool == 1) {

        // Abfrage, ob es das 1. Mal die Schleife durchgeht
        if (first_time == 1) {
            printf("Bitte geben Sie die Einheit an, die sie berechnen moechten (Spannung, Strom, Widerstand): ");
            first_time = 0;
        }
        else if (first_time == 0) {
            printf("\nBitte geben Sie die Einheit an, die sie berechnen moechten (Spannung, Strom, Widerstand): ");
        }

        fgets(einheit, 100, stdin);             // Holt die Eingabe vom Terminal
        
        einheit[strcspn(einheit, "\n")] = 0;    // Entfernt \n, die beim Bestätigen der Eingabe mit Enter entsteht
        lowercase(einheit);
        if (strcmp(einheit, "spannung") == 0) {

            double strom;
            double widerstand;

            printf("\nSie haben erfolgreich die Einheit Spannung gewaehlt...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie den Strom in Ampere an: ");
            scanf("%lf", &strom);

            printf("\nSie haben erfolgreich den Strom angegeben...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie den Widerstand in Ohm an: ");
            scanf("%lf", &widerstand);

            printf("\nSie haben erfolgreich den Widerstand angegeben. Berechnungen laufen...");

            Sleep(sleep_seconds);

            double resultat_spannung = strom * widerstand;
            printf("\nDie Spannung betraegt: %.3f V\n", resultat_spannung);

            printf("\n1) Programm schliessen\t2) Erneut rechnen: ");
            int answer;
            scanf("%d", &answer);

            if (answer == 1) {
                while_bool = 0;

            }
            else if (answer == 2) {
                while_bool = 1;
            }
            else {
                while_bool = 0;
            }



        }
        else if (strcmp(einheit, "Strom") == 0) {

            float spannung;
            float widerstand;

            printf("\nSie haben erfolgreich die Einheit Strom gewaehlt...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie die Spannung in Volt an: ");
            scanf("%f", &spannung);

            printf("\nSie haben erfolgreich die Spannung angegeben...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie den Widerstand in Ohm an: ");
            scanf("%f", &widerstand);

            printf("\nSie haben erfolgreich den Widerstand angegeben. Berechnungen laufen...");

            Sleep(sleep_seconds);

            float resultat_spannung = spannung / widerstand;

            printf("\nDer Strom betraegt: %.3f A\n", resultat_spannung);

            while_bool = 0;
        }
        else if (strcmp(einheit, "Widerstand") == 0) {

            float spannung;
            float strom;

            printf("\nSie haben erfolgreich die Einheit Widerstand gewaehlt...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie die Spannung in Volt an: ");
            scanf("%f", &spannung);

            printf("\nSie haben erfolgreich die Spannung angegeben...");

            Sleep(sleep_seconds);

            printf("\nBitte geben Sie den Strom in Ampere an: ");
            scanf("%f", &strom);

            printf("\nSie haben erfolgreich den Strom angegeben. Berechnungen laufen...");

            Sleep(sleep_seconds);

            float resultat_spannung = spannung / strom;

            printf("\nDer Widerstand betraegt: %.3f Ohm\n", resultat_spannung);

            while_bool = 0;
        }

        else {
            printf("\nFalsche Eingabe!");
        }
    }


    return (0);
}





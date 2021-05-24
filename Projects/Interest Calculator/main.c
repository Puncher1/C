/*******************************************************************************
* Programm:   main.c
* Filename:   .c
*
* Autor:      Andrin Schaller
* Version:    2.0
* Datum:      23.03.2020
*
********************************************************************************
* Datum             Vers.    Kommentar / Änderungsgrund
* 23.03.2020        1.0      Initial Version
* 27.03.2021        2.0      Error Handling
*
*
********************************************************************************
*
* Verwendungszweck: C-Schulung
*
* Beschreibung: Zinsrechner, der berechnet, wie viele Jahre man warten muss, bis das gewünschte Kapital erreicht ist.
*
*
* Precondition:  -
*
* Postcondition: -
*
* Benötigte Libraries:
* - stdlib.h
* - stdio.h
* - string.h
* - Windows.h
* - ctype.h
*
* Copyright (©) 2021 by Andrin Schaller, CH-6300 Zug
*******************************************************************************/

/*** Präprozessor Definitionen ************************************************/
#define _CRT_SECURE_NO_WARNINGS

/***  Include Files ***********************************************************/
#include <stdlib.h>     /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>      /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <string.h>     /* Erweiterte String-Funktionen */
#include <Windows.h>    /* für Sleep() */
#include <ctype.h>      /* für isalpha() und isdigit() */

/***  Globale Deklarationen und Definitionen **********************************/
int sleep_seconds = 1 * 1000;    // Sekunden für Sleep()

/***  Funktions-Deklarationen *************************************************/


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {

    int while_bool_main = 1;

    while (while_bool_main == 1) {                      // while loop, damit das Programm "neu gestartet" (wiederholt) werden kann

        char kapital_str[100];                          // für die Überprüfung der Eingabe
        char zinssatz_str[100];
        char wunschsumme_str[100];

        double kapital;                                 // der eigentliche Speicher der Zahlen
        double zinssatz;
        double wunschsumme;        

        int index = 0;                                  // für die Iteration des char arrays
        int alpha = 0;                                  // boolean: setzt sich auf 1, falls ein Buchstabe im char array ist

        printf("\nBitte geben Sie das Kapital (Anfangskapital) in CHF an: ");
        scanf("%s", &kapital_str);

        Sleep(sleep_seconds);

        kapital_str[strcspn(kapital_str, "\n")] = 0;    // Entfernt \n, das beim Bestätigen der Eingabe mit Enter entsteht

        while (strlen(kapital_str) >= index) {          // Iteration des char arrays
            if (isalpha(kapital_str[index])) {          // Überprüft jeden char im char array nach Buchstaben
                alpha = 1;
            }
            index++;
        }

        if (alpha) {                                    
            printf("\nFalsche Eingabe! Bitte beachten Sie, dass es sich um eine Zahl handeln muss");
        }
        else {

            kapital = atof(kapital_str);                // Wandelt die Zahl vom char array in ein double um

            int while_bool_zinssatz = 1;

            while (while_bool_zinssatz) {               // Wiederholung solange die Eingabe falsch ist
                index = 0;
                alpha = 0;

                printf("\nBitte geben Sie den jaehrlichen Zinssatz in %% an: ");
                scanf("%s", &zinssatz_str);

                Sleep(sleep_seconds);

                zinssatz_str[strcspn(zinssatz_str, "\n")] = 0;

                while (strlen(zinssatz_str) >= index) {
                    if (isalpha(zinssatz_str[index])) {
                        alpha = 1;
                    }
                    index++;
                }

                if (alpha) {
                    printf("\nFalsche Eingabe! Bitte beachten Sie, dass es sich um eine Zahl handeln muss");
                }
                else {
                    while_bool_zinssatz = 0;
                }
            }

            zinssatz = atof(zinssatz_str);

            int while_bool_wunschsumme = 1;

            while (while_bool_wunschsumme) {
                index = 0;
                alpha = 0;

                printf("\nBitte geben Sie die gewuenschte Summe in CHF an: ");
                scanf("%s", &wunschsumme_str);

                Sleep(sleep_seconds);

                wunschsumme_str[strcspn(wunschsumme_str, "\n")] = 0;

                while (strlen(wunschsumme_str) >= index) {
                    if (isalpha(wunschsumme_str[index])) {
                        alpha = 1;
                    }
                    index++;
                }

                if (alpha) {
                    printf("\nFalsche Eingabe! Bitte beachten Sie, dass es sich um eine Zahl handeln muss");
                }
                else {
                    while_bool_wunschsumme = 0;
                }

            }

            wunschsumme = atof(wunschsumme_str);

            printf("\nBerechnungen laufen...");

            Sleep(sleep_seconds);


            double kapital_neu;
            kapital_neu = kapital;                              // Kopiert kapital, damit kapital nicht überschrieben wird
            int jahr = 0;

            while (kapital_neu < wunschsumme) {               
                double zins = kapital_neu * (zinssatz / 100);   
                kapital_neu += zins;               // Zinseszins-Effekt
                jahr++;                                         // + 1 Jahr bei jeder Wiederholung (Jahreszins)
            }                                                 

            char string[100];

            if (jahr == 1) {                //
                strcpy(string, "Jahr");       //
            }                                   // Rechtschreibung 
            else {                            //
                strcpy(string, "Jahren");   //
            }


            printf("\n\nSie werden in %d %s mit einem neuen Kapital von CHF %.2lf Ihr Ziel von CHF %.2lf erreicht haben. \n",
                jahr, string, kapital_neu, wunschsumme);


            int while_bool_question = 1;

            while (while_bool_question) {

                char answer[100];
                printf("\n1) Programm schliessen\t2) Erneut rechnen : ");
                scanf("%s", &answer);

                answer[strcspn(answer, "\n")] = 0;

                if (strcmp(answer, "2") == 0) {
                    while_bool_main = 1;                             // Programm wird "neu gestartet" (wiederholt)
                    while_bool_question = 0;
                    printf("\nProgramm wird neugestartet...\n");
                    Sleep(sleep_seconds);
                }

                else if (strcmp(answer, "1") == 0) {
                    while_bool_main = 0;                             // Programm wird beendet
                    while_bool_question = 0;
                    printf("\nProgramm wird beendet...\n");
                    Sleep(sleep_seconds);
                }
                else {
                    printf("\nFalsche Eingabe! Bitte beachten Sie, dass es sich um die Zahlen 1 oder 2 handeln muss.");
                }
            }
           
        }

    }
    return (0);
}




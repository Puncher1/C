/*******************************************************************************
* Programm:   main.c
* Filename:   .c
*
* Autor:      Andrin Schaller
* Version:    1.0
* Datum:      16.05.2021
*
********************************************************************************
* Datum             Vers.    Kommentar / Änderungsgrund
* 16.05.2021        1.0      Initial Version
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
* Copyright (©) 2020 by Andrin Schaller, CH-6300 Zug
*******************************************************************************/

/*** Präprozessor Definitionen ************************************************/
#define _CRT_SECURE_NO_WARNINGS

/***  Include Files ***********************************************************/
#include <stdlib.h> /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>  /* Funktionsbibliothek: Standard Ein- Ausgabe */

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {

    double noten[10];
    printf("1. Note eingeben: ");
    scanf("%lf", &noten[0]);        // gespeichert in index 0
    
    printf("2. Note eingeben: ");
    scanf("%lf", &noten[1]);
    
    printf("3. Note eingeben: ");
    scanf("%lf", &noten[2]);
    
    printf("4. Note eingeben: ");
    scanf("%lf", &noten[3]);
    
    printf("5. Note eingeben: ");
    scanf("%lf", &noten[4]);
    
    printf("6. Note eingeben: ");
    scanf("%lf", &noten[5]);
    
    printf("7. Note eingeben: ");
    scanf("%lf", &noten[6]);
    
    printf("8. Note eingeben: ");
    scanf("%lf", &noten[7]);

    printf("9. Note eingeben: ");
    scanf("%lf", &noten[8]);

    printf("10. Note eingeben: ");
    scanf("%lf", &noten[9]);

    // end input & speichern

    int index = 0;
    double durchschnitt = 0;
    double summe = 0;
    for (noten; index <= 9; index++) {      // Iteration durch jedes Element (index wird immer um 1 grösser)
        durchschnitt += noten[index];       
        summe += noten[index];
    }
    durchschnitt /= sizeof(noten) / sizeof(noten[0]); 
    // 'durchschnitt' geteilt durch die Anzahl der Elemente im Array (10 Elemente)
    
    printf("\n\nDurschnitt: %.3lf", durchschnitt);
    printf("\nSumme: %.3lf\n", summe);



    return (0);
}




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
* Beschreibung: Software, der mit einem Sortieralgorythmus 100 Zahlen in einem Array sortiert.
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

/*  Include Files */
#include <stdlib.h> /* Funktionsbibliothek: Hilfsfunktionen */
#include <stdio.h>  /* Funktionsbibliothek: Standard Ein- Ausgabe */
#include <time.h> /* Für random Integer */

/***  Globale Deklarationen und Definitionen **********************************/


/***  Funktions-Deklarationen *************************************************/
void swap(int *arr, int arr_size) {

    int index = 0;
    for (index; index <= arr_size; index++) {
        int num_1 = arr[index];
        int num_2 = arr[index+1];

        int *num_1_ = num_1;
        int *num_2_ = num_2;
        int temp_ = num_1_;

        
        if ((num_1 > num_2) && !(index == arr_size)) {
            num_1_ = num_2;
            num_2_ = temp_;
        }

    }

}

/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {
    
    int arr[] = {10, 11, 2, 1, 4};
    
    srand(time(NULL));
    int arr_size = (sizeof(arr) / sizeof(arr[0]) - 1); // '-1' weil die Grösse != letzter Index.
    int index = 0;
    printf("Bevor: ");

    int index_before = 0;
    while (index_before <= arr_size) {
        printf("%d, ", arr[index_before]);
        index_before++;
    }

    swap(&arr, arr_size);
    swap(&arr, arr_size);
    swap(&arr, arr_size);

    printf("\n\nNachher: ");

    int index_after = 0;
    while (index_after <= arr_size) {
        printf("%d, ", arr[index_after]);
        index_after++;
    }
    return (0);
}




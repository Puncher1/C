/*******************************************************************************
* Programm:	  main.c
* Filename:   .c
*
* Author:     Andrin Schaller
* Version:    1.0
* Date:       24-MAY-2021
*
********************************************************************************
* Date             Vers.    Comment / Reason
* 24-MAY-2021        1.0      Initial Version
*
*
********************************************************************************
*
* Usage: C training
*
* Description: Parking meter: Creation of a software for a cashier station in a parking garage
* 
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
#include <Windows.h> /* Wird für Sleep() gebraucht */
#include <math.h> /* Zusätzliche mathematische Funktionen */

/*  Globale Deklarationen und Definitionen */


/*  Funktions-Deklarationen */

double preis_berechnung(int parkzeit) {
    int zeit_check = 30;                            // Für Vergleich von der Parkzeit
    int preis_check = 0;
    int preis;
    for (parkzeit; zeit_check <= 1440; preis_check += 50) {
        if (parkzeit <= zeit_check) {
            if (parkzeit == zeit_check) {
                preis = preis_check + 50;           // für jede 30s -> 50 Rp.
            }
            else {
                preis = preis_check;
            }
            break;
        }
        zeit_check += 30;
    }
    double preis_reformatted = (double)preis;

    return preis_reformatted;
    // end Preisberechnung

}


/*******************************************************************************
******************************* HAUPTPROGRAMM **********************************
*******************************************************************************/
int main(void) {
    int parkzeit;
    int while_main_main = 1;

    int muenzenstock[6] = { 0, 2, 5, 6, 10, 15 };    // <- Coin stock: Changeable, ! -----------------------------------

    int franken_5 = muenzenstock[0];
    int franken_2 = muenzenstock[1];
    int franken_1 = muenzenstock[2];
    int rappen_50 = muenzenstock[3];
    int rappen_20 = muenzenstock[4];
    int rappen_10 = muenzenstock[5];
    // end lokale Variabeln

    while (while_main_main) {
        int while_main = 1;

        printf("Parkticket loesen (max. 24h)");
        printf("\n============================\n\n");
        printf("Parkzeit\t|\tPreis");
        printf("\n----------------|----------------");
        printf("\njede 30m\t|\t+ 50 Rp.");
        printf("\n----------------|----------------\n");

        printf("\nGewuenschte Parkzeit in ganzen Minuten eingeben: ");
        // end Zeiteingabe

        while (while_main) {
            int while_zahlung = 1;

            scanf("%d", &parkzeit);
            if (parkzeit <= 1440) {     // max. Zeit beträgt 24h = 1440s
                char park_einheit;
                double parkzeit_reformatted = (double)parkzeit;

                if (parkzeit >= 60) {
                    parkzeit_reformatted /= 60;
                    park_einheit = 'h';
                }
                else {
                    park_einheit = 'm';
                }
                // end Zeitformat

                double preis = preis_berechnung(parkzeit);  // Aufruf der Funktion
                char preis_einheit[4];
                double zahlung_remain = preis / 100;


                if (preis > 50) {
                    strcpy(preis_einheit, "Fr.");
                    preis /= 100;
                }
                else {
                    strcpy(preis_einheit, "Rp.");
                }
                // end Preisformat


                printf("Zu zahlender Preis fuer %.2lf%c: %.2lf %s", parkzeit_reformatted, park_einheit,
                    preis, preis_einheit);
                Sleep(1000);
                printf("\n\nFolgende Muenzen werden akzeptiert");
                printf("\n==================================");
                printf("\n5 Fr. | 2 Fr. | 1 Fr. | 50 Rp. | 20 Rp. | 10 Rp.\n");

                double zahlung_now;
                double muenzen[6] = { 5, 2, 1, 0.5, 0.2, 0.1 };     // akzeptierte Münzen

                double zahlung_gesamt = 0;
                double zahlung_muenzen[200] = { 0 };
                int count_zahlung = 0;
                while (while_zahlung) {                             // Wiederholung bis Zahlung beglichen ist
                    printf("\nBitte Muenze einwerfen (%.2lf Fr. verbleibend): ", zahlung_remain);
                    scanf("%lf", &zahlung_now);
                    zahlung_gesamt += zahlung_now;
                    zahlung_muenzen[count_zahlung] = zahlung_now;
                    count_zahlung++;
                    // end Zahlungseingabe

                    int index_correct = 0;
                    int bool_muenze = 0;
                    for (muenzen; index_correct <= 6; index_correct++) {
                        if (muenzen[index_correct] == zahlung_now) {
                            bool_muenze = 1;
                            break;
                        }
                    }
                    // end Überprüfung: korrekte Münzen

                    if (bool_muenze) {
                        zahlung_remain -= zahlung_now;

                        int index_amount = 0;

                        for (muenzen; index_amount <= 6; index_amount++) {
                            if ((muenzen[index_amount] == (double)5) && (franken_5 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    franken_5 += 1;
                                }
                            }
                            else if ((muenzen[index_amount] == (double)2) && (franken_2 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    franken_2 += 1;
                                }
                            }
                            else if ((muenzen[index_amount] == (double)1) && (franken_1 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    franken_1 += 1;
                                }
                            }
                            else if ((muenzen[index_amount] == (double)0.5) && (rappen_50 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    rappen_50 += 1;
                                }
                            }
                            else if ((muenzen[index_amount] == (double)0.2) && (rappen_20 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    rappen_20 += 1;
                                }
                            }
                            else if ((muenzen[index_amount] == (double)0.1) && (rappen_10 < 50)) {
                                if ((double)muenzen[index_amount] == zahlung_now) {
                                    rappen_10 += 1;
                                }
                            }
                        }
                        // end Münze zum Münzenstück hinzufügen

                        double power_micro = pow(10, -6);      // für das "Vergleichen" von doubles
                        double abs_remain = fabs(zahlung_remain);          // absoluter Wert

                        if ((abs_remain < power_micro)) {
                            printf("\nErfolgreich bezahlt!");
                            while_zahlung = 0;
                        }

                        if (zahlung_remain * 100 < -9) {
                            double abs_zahlung_remain = fabs(zahlung_remain);
                            double rounded_zahlung_remain = round(abs_zahlung_remain * 100) / 100;

                            int rueckgeld_5 = 0;            // auszugebenes Rückgeld in Variabeln gespeichert
                            int rueckgeld_2 = 0;
                            int rueckgeld_1 = 0;
                            int rueckgeld_50 = 0;
                            int rueckgeld_20 = 0;
                            int rueckgeld_10 = 0;

                            double rest = rounded_zahlung_remain;
                            double abs_rest = fabs(rest);   // absoluter Wert

                            int end_5 = 1;                  // Kein Rückgeld -> werden in Variabeln gespeichert
                            int end_2 = 1;
                            int end_1 = 1;
                            int end_50 = 1;
                            int end_20 = 1;
                            int end_10 = 1;

                            int end_bool = 0;
                            int while_rueckgeld = 1;
                            // end lokale Variabeln: Rückgeldausgabe

                            while (power_micro < abs_rest && while_rueckgeld) {
                                if ((rest >= 5) && (franken_5 > 0)) {       // allgemeine Abfrage um Menge abzurufen
                                    double rest_5 = rest / 5;
                                    if ((franken_5 - (int)rest_5) >= 0) {   // Abfrage: hat es genug, um direkt alle nötigen Münzen zu gebrauchen?

                                        rueckgeld_5 += (int)(rest_5);
                                        rest = (rest_5 - (int)(rest_5)) * 5;
                                        end_5 = 0;
                                    }
                                    else if (franken_5 > 0) {               // Falls nein: Abfrage: hat es überhaupt Münzen im Stock?
                                        while (franken_5 > 0) {             // Restliche Münzen werden gebraucht
                                            franken_5--;
                                            rueckgeld_5++;
                                            rest -= 5;

                                        }
                                        end_5 = 0;
                                    }

                                }
                                else if ((rest >= 2) && (franken_2 > 0)) {
                                    double rest_2 = rest / 2;
                                    if ((franken_2 - (int)rest_2) >= 0) {

                                        rueckgeld_2 += (int)(rest_2);
                                        rest = (rest_2 - (int)(rest_2)) * 2;
                                        end_2 = 0;

                                    }
                                    else if (franken_2 > 0) {
                                        while (franken_2 > 0) {
                                            franken_2--;
                                            rueckgeld_2++;
                                            rest -= 2;
                                        }
                                        end_2 = 0;
                                    }
                                }
                                else if ((rest >= 1) && (franken_1 > 0)) {
                                    double rest_1 = rest / 1;
                                    if ((franken_1 - (int)rest_1) >= 0) {

                                        rueckgeld_1 += (int)(rest_1);
                                        rest = (rest_1 - (int)(rest_1)) * 1;
                                        end_1 = 0;

                                    }
                                    else if (franken_1 > 0) {
                                        while (franken_1 > 0) {
                                            franken_1--;
                                            rueckgeld_1++;
                                            rest -= 1;
                                        }
                                        end_1 = 0;
                                    }
                                }
                                else if ((rest >= 0.5) && (rappen_50 > 0)) {
                                    double rest_50 = rest / 0.5;
                                    if ((rappen_50 - (int)rest_50) >= 0) {
                                        rueckgeld_50 += (int)(rest_50);
                                        rest = (rest_50 - (int)(rest_50)) * 0.5;
                                        end_50 = 0;

                                    }
                                    else if (rappen_50 > 0) {

                                        while (rappen_50 > 0) {
                                            rappen_50--;
                                            rueckgeld_50++;
                                            rest -= 0.5;
                                        }
                                        end_50 = 0;
                                    }
                                }
                                else if ((rest >= 0.2) && (rappen_20 > 0)) {
                                    double rest_20 = rest / 0.2;
                                    if ((rappen_20 - (int)rest_20) >= 0) {

                                        rueckgeld_20 += (int)(rest_20);
                                        rest = (rest_20 - (int)(rest_20)) * 0.2;
                                        end_20 = 0;

                                    }
                                    else if (rappen_20 > 0) {
                                        while (rappen_20 > 0) {
                                            rappen_20--;
                                            rueckgeld_20++;
                                            rest -= 0.2;
                                        }
                                        end_20 = 0;
                                    }
                                }
                                else if ((rest >= 0.1) && (rappen_10 > 0)) {
                                    double rest_10 = rest / 0.1;
                                    if ((rappen_10 - (int)rest_10) >= 0) {

                                        rueckgeld_10 += (int)(rest_10);
                                        rest = (rest_10 - (int)(rest_10)) * 0.1;
                                        end_10 = 0;

                                    }
                                    else if (rappen_10 > 0) {
                                        while (rappen_10 > 0) {
                                            rappen_10--;
                                            rueckgeld_10++;
                                            rest -= 0.1;
                                        }
                                        end_10 = 0;
                                    }
                                    else {              // Falls true: es hat nicht genug von allen Münzen
                                        end_bool = 1;
                                        while_rueckgeld = 0;
                                    }
                                }
                                else {                  // Falls true: es hat nicht genug von allen Münzen
                                    end_bool = 1;
                                    while_rueckgeld = 0;
                                }

                                if (end_5 == 1 && end_2 == 1 && end_1 == 1 && end_50 == 1 && end_20 == 1 && end_10 == 1) { // Falls true: es hat nicht genug von allen Münzen
                                    end_bool = 1;
                                    while_rueckgeld = 0;
                                }
                                abs_rest = fabs(rest);
                            }
                            // end Rückgeldberechnung
                            
                            if (!end_bool) {
                                int count_loading = 0;

                                printf("\nErfolgreich bezahlt!");
                                Sleep(1000);
                                printf("\n\nRueckgeld ausgeben |");

                                while (count_loading < 3) {     // Design: Ladekreis
                                    printf("\b/");
                                    Sleep(150);
                                    printf("\b-");
                                    Sleep(150);
                                    printf("\b\\");
                                    Sleep(150);
                                    printf("\b|");
                                    Sleep(150);
                                    printf("\b/");
                                    Sleep(150);
                                    printf("\b-");
                                    Sleep(150);
                                    printf("\b\\");
                                    Sleep(150);
                                    count_loading++;
                                }

                                printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                                printf("Rueckgeld ausgegeben: %.2lf Fr.", abs_zahlung_remain);

                                printf("\n\n|\t||\t5 Fr.\t|\t2 Fr.\t|\t1 Fr.\t|\t50 Rp.\t|\t20 Rp.\t|\t10 Rp.\t|");
                                printf("\n|-------||--------------|---------------|---------------|---------------|---------------|---------------|");
                                printf("\n| Menge\t||\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|",
                                    rueckgeld_5, rueckgeld_2, rueckgeld_1, rueckgeld_50, rueckgeld_20, rueckgeld_10);
                                while_zahlung = 0;
                                // end Rückgeldausgabe

                            }
                            else {      // Falls true: kein Rückgeld -> Geld wird wieder ausgegeben
                                int count_loading = 0;

                                printf("\nErfolgreich bezahlt!");
                                Sleep(1000);

                                printf("\n\nRueckgeld kann nicht ausgegeben werden, da zu wenig Geld vorhanden ist.");
                                printf("\nGeld ausgeben |");

                                while (count_loading < 3) {
                                    printf("\b/");
                                    Sleep(150);
                                    printf("\b-");
                                    Sleep(150);
                                    printf("\b\\");
                                    Sleep(150);
                                    printf("\b|");
                                    Sleep(150);
                                    printf("\b/");
                                    Sleep(150);
                                    printf("\b-");
                                    Sleep(150);
                                    printf("\b\\");
                                    Sleep(150);
                                    count_loading++;
                                }
                                printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                                printf("Geld ausgegeben: %.2lf Fr.", zahlung_gesamt);

                                int count_geld_ausgabe = 0;
                                int zahlung_muenzen_len = 0;

                                for (zahlung_muenzen; !(zahlung_muenzen[zahlung_muenzen_len] < power_micro); zahlung_muenzen_len++) {
                                    zahlung_muenzen_len++;
                                }
                                // end länge von 'zahlung_muenzen' ermitteln

                                for (zahlung_muenzen; count_geld_ausgabe <= zahlung_muenzen_len; count_geld_ausgabe++) {
                                    if (zahlung_muenzen[count_geld_ausgabe] == (double)5) {
                                        franken_5--;
                                    }
                                    else if (zahlung_muenzen[count_geld_ausgabe] == (double)2) {
                                        franken_2--;
                                    }
                                    else if (zahlung_muenzen[count_geld_ausgabe] == (double)1) {
                                        franken_1--;
                                    }
                                    else if (zahlung_muenzen[count_geld_ausgabe] == (double)0.5) {
                                        rappen_50--;
                                    }
                                    else if (zahlung_muenzen[count_geld_ausgabe] == (double)0.2) {
                                        rappen_20--;
                                    }
                                    else if (zahlung_muenzen[count_geld_ausgabe] == (double)0.1) {
                                        rappen_10--;
                                    }
                                    // end Geld von Münzenstock wieder entfernen
                                }

                                while_zahlung = 0;
                                // end Kein Rückgeld: Geldausgabe

                            }
                        }
                    }
                    else {
                        printf("\nMuenze nicht erkannt! Bitte stellen Sie sicher, dass Sie eine akzeptierte Muenze einwerfen.");
                    }
                }
                Sleep(6000);
                system("cls");      // CMD-Output wird zurückgesetzt
                while_main = 0;     // beginnt von vorne (Münzenstock bleibt erhalten)
            }
            else {
                printf("Die maximale Parkzeit betraegt 24h (1440m), bitte erneut eingeben: ");
            }

        }
    }
    return (0);
}




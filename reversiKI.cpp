/**
 * Praktikum Informatik 1 MMXXIII
 *
 * @file reversiKI.cpp
 *
 * Stellt eine KI fuer das Spiel Reversi zur Verfuegung
 */

#include "reversiKI.h"
#include "config.h"
#include <iostream>

extern int rundenAnzahl;
extern int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler);
extern void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY);
extern bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY);
extern void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X]);

bool computerZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }
    int voraussehen[GROESSE_Y][GROESSE_X];
    int min_x = 0;
    int min_y = 0;
    int min = GROESSE_X * GROESSE_Y;

    for (int j = 0; j < GROESSE_Y; j++)
    {
        for (int i = 0; i < GROESSE_X; i++)
        {
            // Spielfeld zuruecksetzen
            for (int cj = 0; cj < GROESSE_Y; cj++)
            {
                for (int ci = 0; ci < GROESSE_X; ci++)
                {
                    voraussehen[cj][ci] = spielfeld[cj][ci];
                }
            }

            if (zugGueltig(voraussehen, aktuellerSpieler, i, j))
            {
                zugAusfuehren(voraussehen, aktuellerSpieler, i, j);
                if (moeglicheZuege(voraussehen, 3 - aktuellerSpieler) < min)
                {
                    min = moeglicheZuege(voraussehen, 3 - aktuellerSpieler);
                    min_x = i;
                    min_y = j;
                }
            }
        }
    }
    std::cout << "\nRunde: " << rundenAnzahl;
    zugAusfuehren(spielfeld, aktuellerSpieler, min_x, min_y);
    // zeigeSpielfeld(spielfeld);
    rundenAnzahl++;
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char)(min_x + 65) << (min_y + 1) << std::endl;
    zeigeSpielfeld(spielfeld);

    return true;
}
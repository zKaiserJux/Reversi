 /**
  * @mainpage Reversi
  *
  * Dokumentation des Spiels Reversi im Rahmen des Praktikums Informatik 1.
  *
  */

#include <iostream>
#include <string>
#include "config.h"
#include "reversiKI.h"

// Definiert die aktuelle Rundenanzahl
int rundenAnzahl = 1;

/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
	for (int j = 0; j < GROESSE_Y; j++)
	{
		for (int i = 0; i < GROESSE_X; i++)
		{
			spielfeld[j][i] = 0;
		}
	}
	spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
	spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
	spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
	spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
 * @brief Ausgabe des Spielfelds auf der Konsole
 *
 * Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
 * Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
 *
 *  @param spielfeld  Spielfeld, das ausgeben wird
 */
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
	std::cout << "   | ";

	//Start bei ASCII 65 = A
	for (int i = 65; i < 65 + GROESSE_X; ++i)
		std::cout << ((char)i) << " | ";

	std::cout << std::endl;

	for (int j = 0; j < GROESSE_Y; ++j)
	{
		for (int i = 0; i < GROESSE_X; ++i)
		{
			std::cout << "---+";
		}
		std::cout << "---+" << std::endl;

		std::cout << " " << j + 1 << " |";
		for (int i = 0; i < GROESSE_X; ++i)
		{
			switch (spielfeld[j][i])
			{
			case 0:
				std::cout << "   ";
				break;
			case 1:
				std::cout << " X ";
				break;
			case 2:
				std::cout << " O ";
				break;
			default:
				std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
				std::cout << "Abbruch .... " << std::endl;
				exit(0);
				break;
			}
			std::cout << "|";
		};  //for i
		std::cout << std::endl;
	}  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
	int zaehlerSpieler1 = 0;
	int zaehlerSpieler2 = 0;

	for (int j = 0; j < GROESSE_Y; ++j)
	{
		for (int i = 0; i < GROESSE_X; ++i)
		{
			if (spielfeld[j][i] == 1)
			{
				++zaehlerSpieler1;
			}
			if (spielfeld[j][i] == 2)
			{
				++zaehlerSpieler2;
			}

		}
	}

	if (zaehlerSpieler1 == zaehlerSpieler2)
	{
		return 0;
	}
	if (zaehlerSpieler1 < zaehlerSpieler2)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

/**
 * @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
 *
 * @param posX Index fuer die Spalte
 * @param posY Index fuer die Zeile
 * @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
 */
bool aufSpielfeld(const int posX, const int posY)
{
	// Hier erfolgt jetzt Ihre Implementierung ...
	if ((0 <= posX) && (posX < GROESSE_X) && (0 <= posY) && (posY < GROESSE_Y))
	{
		return true;
	}
	return false;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return gibt true zurück, wenn ein übergebener Zug gültig ist, ansonsten false
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
	int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
	//               if aktuellerSpieler == 2 -> gegner = 1
	if (!aufSpielfeld(posX, posY))
	{
		// Wenn sich die ausgesuchte Position nicht mehr auf dem Spielfeld befindet, ist der Zug ungueltig
		return false;
	}

	if (spielfeld[posY][posX] != 0)
	{
		// Wenn die ausgesucht Position schon besetzt ist, ist der Zug ebenfalls ungueltig
		return false;
	}

	// Alle Richtungen ueberpruefen, bis der erste gueltige Zug gefunden wurde
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			// Unterusucht die Richtung nur dann, wenn sich in der Umgebung ein gegnerischer Stein befindet und sich diese Poistion auf dem Spielfeld befindet
			if (spielfeld[posY + j][posX + i] == gegner && aufSpielfeld(posX, posY))
			{
				for (int n = 1; n < GROESSE_X; n++)
				{
					// Ueberueft, ob sich die neue Position noch auf dem Spielfeld befindet
					if (aufSpielfeld(posX + i * n, posY + j * n))
					{
						// Ueberprueft, ob nach dem letzten gegnerischen Stein ein Platz frei ist
						if (spielfeld[posY + j * n][posX + i * n] == 0)
						{
							// Wenn ein Platz frei ist, koennen die dazwischenliegenden Steine laut Regelwerk nicht umgeschlossen werden -> Ausbruch aus der Schleife und Rueckgabewert: false
							break;
						}

						// Wenn noch nicht aus der Schleife ausgebrochen wurde, muss der nachfolgende Stein ein eigener sein und der Zug ist somit gueltig
						else if (spielfeld[posY + j * n][posX + i * n] == aktuellerSpieler)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

/**
 * @brief Funktion, die einen Zug ausfuehrt
 *	Dreht alle, der von zwei Steinen des aktuellen Spielers eingeschlossenen Steine um bzw. wandelt diese in die eigenen um
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
	int gegner = 3 - aktuellerSpieler;

	if (!aufSpielfeld(posX, posY))
	{
		return;
	}

	if (spielfeld[posY][posX] != 0)
	{
		return;
	}

	//Alle Richtungen bearbeiten
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			// aehnlich wie die Funktion zugGueltig(), aber stellen Sie sicher, das alle gegnerischen Steine in
			// allen Richtungen in Ihre eigenen Steine umgewandelt werden
			// Hier erfolgt jetzt Ihre Implementierung ...
			if (spielfeld[posY + j][posX + i] == gegner)
			{
				int n = 1;
				while (spielfeld[posY + j * n][posX + i * n] == gegner && aufSpielfeld(posX + i * n, posY + j * n))
				{
					n++;
				}
				if ((spielfeld[posY + j * n][posX + i * n] == aktuellerSpieler) && aufSpielfeld(posX + i * n, posY + j * n))
				{
					for (int k = n; k >= 0; k--)
					{
						spielfeld[posY + j * k][posX + i * k] = aktuellerSpieler;
					}
				}
			}
		}
	}
}

/**
 * @brief ueberprueft wie viele gueltige Zuege ein Spieler zur Verfügung hat
 * @param spielfeld das aktuelle Spielfeld
 * @param aktuellerSpieler Der Spieler der gerade am Zug ist
 * @return Zaehlt ueber die beiden for-Schleifen, wie viele gueltige Zuege moeglich sind und gibt den Counter wieder
 */
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
	// Hier erfolgt jetzt Ihre Implementierung ...
	int counter = 0;
	for (int j = 0; j <= GROESSE_X; j++)
	{
		for (int i = 0; i <= GROESSE_Y; i++)
		{
			if (zugGueltig(spielfeld, aktuellerSpieler, j, i))
			{
				counter++;
			}
		}
	}
	return counter;
}

/**
 * @brief Fuehrt den Zug eines menschlichen Spielers aus
 *
 * ueberprueft zuerst, ob der aktuelle Spieler ueberhaupt einen gueltigen Zug hat, wenn nicht wird der Spieler gewechselt
 * falls der aktuelle Spieler einen gueltigen Zug hat, wird der Spieler gefragt, wo er seinen Stein anlegen moechte,
 * wenn dieser gueltig ist, wird der Stein an die entsprechende Stelle angelegt, sonst wird dem Spieler eine entsprechende Rueckmeldung in der Konsole ausgegeben,
 * dass sein gewaehlter Zug nicht gueltig ist und er bitte einen neuen Zug angeben soll
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler
 * @return true, falls der Zug durchgefuehrt werden kann, sonst false
 */

bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
	if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
	{
		return false;
	}

	int posX;
	int posY;
	std::string symbolSpieler;
	if (aktuellerSpieler == 1)
	{
		symbolSpieler = "X";
	}
	else
	{
		symbolSpieler = "O";
	}

	while (true)
	{
		std::string eingabe;
		std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): ";
		std::cin >> eingabe;
		posX = (int)eingabe[0] % 32 - 1;
		posY = (int)eingabe[1] - 49;

		// wenn der Zug gültig ist, wird die Schleife sofort verlassen und es wird anschließend der entsprechende Zug ausgeführt
		if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
		{
			//accept turn;
			break;
		}
		// wenn der Zug nicht gültig ist, wird dem aktuellen Spieler über die Konsole eine entsprechende Mitteilung ausgegeben
		else
		{
			std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
		}
	}
	std::cout << "Runde: " << rundenAnzahl << std::endl;
	zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
	zeigeSpielfeld(spielfeld);
	rundenAnzahl++;
	std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char)(posX + 65) << (posY + 1) << "\n" << std::endl;
	return true;
}


void spielen(const int spielerTyp[2])
{
	int spielfeld[GROESSE_Y][GROESSE_X];

	//Erzeuge Startaufstellung
	initialisiereSpielfeld(spielfeld);
	int aktuellerSpieler = 1;

	// solange noch Zuege bei einem der beiden Spieler moeglich sind
	//
	// Hier erfolgt jetzt Ihre Implementierung ...
	// Ermittlung des aktuellen Spielers
	int gegner = 3 - aktuellerSpieler;
	int rundenAnzahl;
	while (moeglicheZuege(spielfeld, gegner) + moeglicheZuege(spielfeld, aktuellerSpieler) > 0)
	{
		// zeigeSpielfeld(spielfeld);
		// Wenn der aktuelle Spieler ein Mensch ist, wird dementsprechend die Funktion menschlicher Zug ausgeführt
		if (spielerTyp[aktuellerSpieler - 1] == MENSCH)
		{
			menschlicherZug(spielfeld, aktuellerSpieler);
			rundenAnzahl++;
		}

		// Andernfalls muss der aktuelle Spieler ein Computer sein und mit Hilfe der Funktion computerZug wird ein Zug der KI durchgeführt
		else
		{
			computerZug(spielfeld, aktuellerSpieler);
			rundenAnzahl++;
		}

		aktuellerSpieler = gegner;
		gegner = 3 - aktuellerSpieler;
	}

	// Gewinner wird mit der oben definierten Funktion "int gewinner" ermittelt und ausgegeben
	switch (gewinner(spielfeld))
	{
		// Hier erfolgt jetzt Ihre Implementierung ...
	case 1:
		std::cout << "\nDer Spieler 1 hat das Spiel gtewonnen!" << std::endl;
		break;
	case 2:
		std::cout << "\nDer Spieler 2 hat das Spiel gewonnen!" << std::endl;
		break;
	default:
		std::cout << "\nDas Spiel endet unentscheiden" << std::endl;
		break;
	}
}

int main()
{
	/*if (TEST == 0)
	{
		bool gesamtErgebnis = ganzenTestAusfuehren();
		if (gesamtErgebnis == true)
		{
			std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
		}
		else
		{
			std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
			exit(1);
		}
		std::cout << std::endl << std::endl;
	}
	*/

	int spielfeld[GROESSE_Y][GROESSE_X];

	// Es wird eine Abfrage gemacht, ob ein Mensch oder Computer fuer den ersten oder zweiten Spieler spielt
	std::string input1;
	std::cout << "Ist Spieler 1 ein Computer ? (j/n) ";
	std::cin >> input1;
	int spieler1 = (input1 == "j" || input1 == "J") ? 2 : 1;
	std::cout << "\n";
	std::string input2;
	std::cout << "Ist Spieler 2 ein Computer ? (j/n) ";
	std::cin >> input2;
	int spieler2 = (input2 == "j" || input2 == "J") ? 2 : 1;
	std::cout << "\n";

	// Spielfeld wird erstellt
	initialisiereSpielfeld(spielfeld);
	std::cout << "Startfeld" << std::endl;
	zeigeSpielfeld(spielfeld);

	int spielerTyp[2] = { spieler1, spieler2 };  // Feld, das Informationen ueber den Typ des Spielers enthaelt. MENSCH(=1) oder COMPUTER(=2)
	// Hier erfolgt das eigentliche Spiel
	spielen(spielerTyp);

	return 0;
}
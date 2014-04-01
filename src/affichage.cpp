#include "stdafx.h"
#include "affichage.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void affichage::messageBanniere()
{
	cout << "" << endl;
	cout << " ________       _________         _      _  " << endl;
	cout << "|                   |            | \\    / | " << endl;
	cout << "|________           |            |  \\  /  | " << endl;
	cout << "|                   |            |   \\/   | " << endl;
	cout << "|________ asy       | witter     |        | anager" << endl;
	cout << "" << endl;
}

void affichage::pause()
{
	system("PAUSE");
}

int affichage::menu()
{
	string input = "";
	int response = 0;

	while (true)
	{
		sautLigne();
		cout << "--Menu--" << endl;
		sautLigne();
		cout << "   1 - Envoyer un tweet" << endl;
		cout << "   2 - Follow en masse" << endl;
		cout << "   3 - Unfollow en masse" << endl;
		cout << "   4 - Configuration" << endl;
		cout << "   5 - Informations" << endl;
	   
		// Recuperation de la valeur entree par l'utilisateur
		getline(cin, input);

		// Test conversion string to int et entre 1 et 5
		stringstream myStream(input);
		if (myStream>>response)
		{
			if (response<1 || response>5)
			{
				sautLigne();
				cout << "Erreur, veuillez entrer un chiffre entre 1 et 5." << endl;
			}
			else
			{
				break;
			}
		}
	}
	return response;
}

void affichage::sautLigne()
{
	cout << "" << endl;
}

void affichage::redirectMenu(int choix)
{
	switch (choix){
		case 1: {
			sautLigne();
			cout << "Choix 1" << endl;
			sautLigne();
			break;
		}
		case 2: {
			sautLigne();
			cout << "Choix 2" << endl;
			sautLigne();
			break;
		}
		case 3: {
			sautLigne();
			cout << "Choix 3" << endl;
			sautLigne();
			break;
		}
		case 4: {
			sautLigne();
			cout << "Choix 4" << endl;
			sautLigne();
			break;
		}
		case 5: {
			sautLigne();
			cout << "Choix 5" << endl;
			sautLigne();
			break;
		}
	}
}
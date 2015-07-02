#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main (int m, char* arg[])
{
    if (m != 4) {
        printf("Syntaxe: %s nomFichier n nomModele\n", arg[0]);
        return 1;
    }

    char* monFichier = arg[1];
    string n = arg[2];
    char* nomModele = arg[3];

    string monMot;
    string temps;
    string mot;

    monMot = "w"+n+" = ";

    ifstream fichier(monFichier);

    while (!fichier.eof())
    {

        fichier >> temps;
        fichier >> mot;

        if (!fichier.eof())
            monMot += mot;

    }

    char nouveauFichier[1000] = "../Resultat";
    strcat(nouveauFichier, nomModele);
    strcat(nouveauFichier, "/");
    strcat(nouveauFichier, monFichier);
    strcat(nouveauFichier, ".txt");
    ofstream fichierTraite (nouveauFichier, ios::app);

    fichierTraite << monMot << endl;
    fichierTraite.close();
    return 0;
}

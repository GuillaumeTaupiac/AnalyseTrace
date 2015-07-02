#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int indice(char c) {
    return c-0x30;
}

int automateToInt(string automate) {
    if (automate.compare("1") == 0) {
        return 1;
    }
    if (automate.compare("2") == 0) {
        return 2;
    }
    if (automate.compare("3") == 0) {
        return 3;
    }
    if (automate.compare("4") == 0) {
        return 4;
    }
    if (automate.compare("5") == 0) {
        return 5;
    }
    if (automate.compare("6") == 0) {
        return 6;
    }
    if (automate.compare("7") == 0) {
        return 7;
    }
    if (automate.compare("8") == 0) {
        return 8;
    }
    if (automate.compare("9") == 0) {
        return 9;
    }
    if (automate.compare("10") == 0) {
        return 10;
    }
}

bool validation(string mot, string automate) {
    int trans1[5][4] = {{1,-1,-1,-1}, {-1,2,-1,-1}, {-1,-1,3,-1}, {-1,4,-1,-1}, {-1,-1,-1,-1}};
    int trans2[6][4] = {{1,-1,-1,-1}, {-1,2,-1,-1}, {-1,-1,3,-1}, {-1,4,-1,-1}, {5,-1,-1,-1}, {-1,-1,-1,-1}};
    int trans3[7][4] = {{1,-1,-1,-1}, {-1,2,-1,-1}, {-1,-1,3,-1}, {-1,4,-1,-1}, {-1,-1,5,-1}, {-1,6,-1,-1}, {-1,-1,-1,-1}};
    int trans4[7][4] = {{1,-1,-1,-1}, {-1,2,-1,-1}, {-1,-1,3,-1}, {-1,4,-1,-1}, {5,-1,-1,-1}, {-1,6,-1,-1}, {-1,-1,-1,-1}};
    int trans5[6][4] = {{1,-1,-1,-1}, {-1,2,-1,-1}, {-1,-1,3,-1}, {-1,4,-1,-1}, {-1,-1,5,-1}, {-1,-1,-1,-1}};
    int trans6[5][4] = {{1,-1,-1,-1}, {-1,-1,2,-1}, {-1,3,-1,-1}, {4,-1,-1,-1}, {-1,-1,-1,-1}};
    int trans7[7][4] = {{1,-1,-1,-1}, {-1,-1,2,-1}, {-1,3,-1,-1}, {-1,-1,4,-1}, {-1,5,-1,-1}, {6,-1,-1,-1}, {-1,-1,-1,-1}};
    int trans8[7][4] = {{-1,-1,1,-1}, {-1,2,-1,-1}, {3,-1,-1,-1}, {-1,4,-1,-1}, {5,-1,-1,-1}, {-1,6,-1,-1}, {-1,-1,-1,-1}};
    int trans9[7][4] = {{-1,-1,1,-1}, {2,-1,-1,-1}, {-1,3,-1,-1}, {-1,-1,4,-1}, {-1,5,-1,-1}, {-1,-1,6,-1}, {-1,-1,-1,-1}};
    bool ef1[] = {false, false, false, false, true};
    bool ef2[] = {false, false, false, false, false, true};
    bool ef3[] = {false, false, false, false, false, false, true};
    bool ef4[] = {false, false, false, false, false, false, true};
    bool ef5[] = {false, false, false, false, false, true};
    bool ef6[] = {false, false, false, false, true};
    bool ef7[] = {false, false, false, false, false, false, true};
    bool ef8[] = {false, false, false, false, false, false, true};
    bool ef9[] = {false, false, false, false, false, false, true};

    int (*transitions)[4] = NULL;
    bool *etatfinal = NULL;
    switch (automateToInt(automate)) {
        case 1:
            transitions = trans1;
            etatfinal = ef1;
            break;
        case 2:
            transitions = trans2;
            etatfinal = ef2;
            break;
        case 3:
            transitions = trans3;
            etatfinal = ef3;
            break;
        case 4:
            transitions = trans4;
            etatfinal = ef4;
            break;
        case 5:
            transitions = trans5;
            etatfinal = ef5;
            break;
        case 6:
            transitions = trans6;
            etatfinal = ef6;
            break;
        case 7:
            transitions = trans7;
            etatfinal = ef7;
            break;
        case 8:
            transitions = trans8;
            etatfinal = ef8;
            break;
        case 9:
            transitions = trans9;
            etatfinal = ef9;
            break;
        default:
            cout << "Erreur: automate non trouvé" << endl;
            break;
    }
    int etat = 0;
    for (unsigned int i=0; i<mot.length(); i++) {
        int car = indice(mot[i]);
        if (car<0) {
            cout << "Erreur: caractère non reconnu" << endl;
            return 1;
        }
        etat = transitions[etat][car];
        if (etat == -1)
            return false;
    }
    return etatfinal[etat];
}

bool validationTemporelle(string mot, string temps[100]) {
    double autom1[6][2] = {{0.0, 14.0}, {13.0, 15.0}, {13.0, 15.0}, {13.0, 15.0}, {0.4, 0.5}, {2.0, 12.0}};
    int transition = 0;
    bool res = true;
    double delta = 0;
    for (int i=1; i<mot.length(); i++) {
        delta = atof(temps[i].c_str()) - atof(temps[i-1].c_str());
        switch (mot[i-1]) {
            case '0':
                switch (mot[i]) {
                    case '1':
                        transition = 0;
                        break;
                    case '2':
                        transition = 1;
                        break;
                }
                break;
            case '1':
                switch (mot[i]) {
                    case '0':
                        transition = 2;
                        break;
                    case '2':
                        transition = 3;
                        break;
                }
                break;
            case '2':
                switch (mot[i]) {
                    case '0':
                        transition = 4;
                        break;
                    case '1':
                        transition = 5;
                        break;
                }
                break;
        }
        res &= (delta > autom1[transition][0] && delta < autom1[transition][1]);
    }
    return res;
}

int main (int m, char* arg[]) {

    if (m != 4) {
        cout << "Syntaxe: " << arg[0] << " nomFichier n nomModele" << endl;
        return 1;
    }

    char* monFichier = arg[1];
    string n = arg[2];
    char* nomModele = arg[3];

    string monMot;
    string temps[100];
    string mot;

    monMot = "w"+n+" = ";

    ifstream fichier(monFichier);

    int i=0;
    while (!fichier.eof()) {
        fichier >> temps[i++];
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
    FILE *hd;
    char automate[100];
    char commande[1000] = "grep ";
    strcat(commande, monFichier);
    strcat(commande, " /home/gtaupiac/Documents/IRCCYN/automates.txt | cut -d' ' -f2");
    hd = popen(commande, "r");
    while (fgets(automate, sizeof(automate), hd) != NULL);
    pclose(hd);
    string valide;
    automate[strlen(automate) - 1] = 0;
    string autom(automate);
    if (validation(monMot.substr(string("w"+n+" = ").length()), autom) && validationTemporelle(monMot.substr(string("w"+n+" = ").length()), temps)) {
        valide = " A";
    } else {
        valide = " E";
    }
    fichierTraite << monMot << valide << endl;

    fichierTraite.close();
    return 0;
}

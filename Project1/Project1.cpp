
#include <iostream>

const int longueur = 10;
const int largeur = 20;

struct Hero
{
    int PV = 3;
    int x = 0;
    int y = 0;
};


struct Ennemie
{
    int x = 0;
    int y = 0;
};

void afficher(int grille[longueur * largeur], Hero& hero, Ennemie ene[]) {
    system("cls");
    for (int y = 0; y < largeur; y++) {
        for (int x = 0; x < longueur; x++) {
            int sauv = grille[y * longueur + x];
            if (x == hero.x && y == hero.y) {
                hero.x = x;
                hero.y = y;
                std::cout << "H";
            }
            else {
                bool ennemiAffiche = false;
                for (int i = 0; i < sizeof(ene); i++) {
                    if (x == ene[i].x && y == ene[i].y) {
                        std::cout << "X";
                        ennemiAffiche = true;
                        break;
                    }
                }
                if (!ennemiAffiche) {
                    if (sauv == 0) {
                        std::cout << ".";
                    }
                    if (sauv == 1) {
                        std::cout << "A";
                    }
                    if (sauv == 2) {
                        std::cout << "~";
                    }
                }




            }

            
        }
        std::cout << '\n';
    }
}






    void mouvementHero(Hero & hero, int grille[longueur * largeur], Ennemie ene[]) {
    char touche;
    std::cin >> touche;
    if (touche == 'z' || touche == 'Z') {
        hero.y -= 1;
        if (grille[hero.y * longueur + hero.x] == 1) {
            hero.y += 1;
        }
        if (hero.y < 0) {
            hero.y += 1;
        }
        afficher(grille, hero, ene);
    }
    if (touche == 's' || touche == 'S') {
        hero.y += 1;
        if (grille[hero.y * longueur + hero.x] == 1) {
            hero.y -= 1;
        }
        if (hero.y > 19) {
            hero.y -= 1;
        }
        afficher(grille, hero, ene);
    }
    if (touche == 'd' || touche == 'D') {
        hero.x += 1;
        if (grille[hero.y * longueur + hero.x] == 1) {
            hero.x -= 1;
        }
        if (hero.x > 9) {
            hero.x -=1;
        }
        afficher(grille, hero, ene);
    }
    if (touche == 'q' || touche == 'Q') {
        hero.x -= 1;
        if (grille[hero.y * longueur + hero.x] == 1) {
            hero.x += 1;
        }
        if (hero.x < 0) {
            hero.x += 1;
        }
        afficher(grille, hero, ene);
    }
}

int main()
{
    int grille[longueur * largeur] = {};

    Hero p1;
    p1.y = 1;

	
    
    Ennemie nbEnnemie[4] = {{3,9},{4,16},{9,3},{7,0}};



    for (int i = 0; i < longueur * largeur; i++) {
        grille[i] = 0;
    }
    for (int i = 10; i < 13; i++) {
        for (int j = 5; j < 8; j++) {
            grille[i * longueur + j] = 1;
        }
    }

    afficher(grille, p1, nbEnnemie);
    while (p1.PV > 0) {
        std::cout << "Tour du joueur ";
        mouvementHero(p1,grille,nbEnnemie);
    }
}



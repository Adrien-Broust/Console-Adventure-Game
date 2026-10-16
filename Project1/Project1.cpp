
#include <iostream>
#include <random>

const int longueur = 10;
const int largeur = 20;
const int nbEne = 4;

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

void afficher(int grille[longueur * largeur], Hero& hero, Ennemie ene[nbEne]) {
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
                for (int i = 0; i < nbEne; i++) {
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


void degats(Hero& hero, Ennemie ene[nbEne]) {
    
    for (int i = 0; i < nbEne; i++) {
        if (ene[i].x == hero.x && ene[i].y == hero.y) {
            hero.PV -= 1;
            std::cout << '\n' << "Touche !";
        }
    }
}



    void mouvementHero(Hero & hero, int grille[longueur * largeur], Ennemie ene[nbEne]) {
        std::cout << '\n' << "Tour du joueur " << '\n' << "PV du joueur :" << hero.PV;
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


    void mouvementEnnemie(int grille[longueur * largeur], Ennemie ene[nbEne]) {
        std::cout << "Tour Ennemie";
        
        for (int i = 0; i < nbEne; i++) {
            int direct = rand() % 4;
            int newx = ene[i].x;
            int newy = ene[i].y;


            if (direct == 0) {
                newy -= 1;
                if (grille[newy * longueur + newx] == 1) {
                    newy += 1;
                }
                if (newy < 0) {
                    newy += 1;
                }
                ene[i].y = newy;
            }
           
            if (direct == 1) {
                newy += 1;
                if (grille[newy * longueur + newx] == 1) {
                    newy -= 1;
                }
                if (newy > 19) {
                    newy -= 1;
                }
                ene[i].y = newy;
            }
            
            if (direct == 2) {
                newx -= 1;
                if (grille[newy * longueur + newx] == 1) {
                    newx += 1;
                }
                if (newx < 0) {
                    newx += 1;
                }
                ene[i].x = newx;
            }
            if (direct == 3) {
                newx += 1;
                if (grille[newy * longueur + newx] == 1) {
                    newx -= 1;
                }
                if (newx > 9) {
                    newx -= 1;
                }
                ene[i].x = newx;
            }
        }
    }










int main()
{
    int grille[longueur * largeur] = {};

    Hero p1;
    p1.y = 1;

	
    
    Ennemie nbEnnemie[nbEne] = {{3,9},{4,16},{9,3},{7,0}};



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
        mouvementHero(p1,grille,nbEnnemie);
        degats(p1, nbEnnemie);
        mouvementEnnemie(grille, nbEnnemie);
        degats(p1, nbEnnemie);
    }
    if (p1.PV == 0) {
        system("cls");
        std::cout << "GAME OVER";
    }
}



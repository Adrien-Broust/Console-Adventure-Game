
#include <iostream>
#include <vector>
#include <windows.h>
#include <curses.h>

const int longueur = 20;
const int largeur = 10;

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

enum Carte {
    .,
};

void afficher(int map[longueur * largeur], Hero& hero, std::vector<Ennemie>& ene) {
    clear();
    refresh();
    size_t taille = ene.size();
    for (int y = 0; y < largeur; y++) {
        for (int x = 0; x < longueur; x++) {
            int sauv = map[y * longueur + x];
            if (x == hero.x && y == hero.y) {
                attron(COLOR_PAIR(3));
                printw("H");
                attroff(COLOR_PAIR(3));
            }
            else {
                bool ennemiAffiche = false;
                for (int i = 0; i < taille; i++) {
                    if (x == ene[i].x && y == ene[i].y) {
                        attron(COLOR_PAIR(2));
                        printw("X");
                        attroff(COLOR_PAIR(2));;
                        ennemiAffiche = true;
                        break;
                    }
                }
                if (!ennemiAffiche) {
                    if (sauv == 0) {
                        attron(COLOR_PAIR(8));
                        printw(".");
                        attroff(COLOR_PAIR(8));
                    }
                    if (sauv == 1) {
                        attron(COLOR_PAIR(1));
                        printw("A");
                        attroff(COLOR_PAIR(1));
                    }
                    if (sauv == 2) {
                        attron(COLOR_PAIR(7));
                        printw("~");
                        attroff(COLOR_PAIR(7));
                    }
                    if (sauv == 5) {
                        attron(COLOR_PAIR(4));
                        printw("E");
                        attroff(COLOR_PAIR(4));
                    }
                }
            }
        }
        printw("\n");
    }
}


void degats(Hero& hero,  std::vector<Ennemie>& ene) {
    size_t taille = ene.size();
    for (int i = 0; i < taille; i++) {
        if (ene[i].x == hero.x && ene[i].y == hero.y) {
            hero.PV--;
            break;
        }
    }
}


void deplacer(int& x,int& y,int direction,int map[longueur * largeur]) {
    int newx = x;
    int newy = y;

    if (direction == 0) {
        newy--;
    }
    else if (direction == 1) {
        newy++;
    }
    else if (direction == 2) {
        newx--;
    }
    else if (direction == 3) {
        newx++;
    }
    if (newx < 0 || newx >= longueur ||
        newy < 0 || newy >= largeur) {
        return;
    }
    if (map[newy * longueur + newx] == 1) {
        return;
    }
    x = newx;
    y = newy;
}


void mouvementHero(Hero& hero,int map[longueur * largeur]) {
    printw("\n");
    attron(COLOR_PAIR(3));
    printw("PV du joueur : %d", hero.PV);
    attroff(COLOR_PAIR(3));

    char touche = getch();
    

    int direction = -1;

    if (touche == 'z' || touche == 'Z') {
        direction = 0;
    }
    else if (touche == 's' || touche == 'S') {
        direction = 1;
    }
    else if (touche == 'q' || touche == 'Q') {
        direction = 2;
    }
    else if (touche == 'd' || touche == 'D') {
        direction = 3;
    }

    if (direction != -1) {deplacer(hero.x, hero.y, direction, map);
    }
}


void mouvementEnnemie(int map[longueur * largeur],std::vector<Ennemie>& ene) {
    for (size_t i = 0; i < ene.size(); i++) {
        int direction = rand() % 4;

        deplacer(ene[i].x,ene[i].y,direction,map);
    }
}

void niveau(int map[longueur * largeur], Hero& hero, std::vector<Ennemie>& ene) {
    while (map[hero.y * longueur + hero.x] != 5 && hero.PV > 0) {
        afficher(map, hero, ene);
        mouvementHero(hero, map);
        degats(hero, ene);
        mouvementEnnemie(map, ene);
        degats(hero, ene);
    }
       
}

bool victoire(int map[longueur * largeur], Hero& hero) {
    return map[hero.y * longueur + hero.x] == 5;
}
    
bool defaite(Hero& hero) {
    return hero.PV <= 0;
}



int main()
{
    initscr();

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    

    int niveauActuel = 0;
    const int nombreNiveaux = 2;

    int map[2][longueur * largeur] = {};

    Hero p1;
    p1.y = 1;
	
    
    std::vector<Ennemie> nbEnnemie(3);


    for (int i = 0; i < longueur * largeur; i++) {
        map[0][i] = 0;
    }

    for (int i = 4; i < 7; i++) {
        for (int j = 10; j < 13; j++) {
            map[0][i * longueur + j] = 1;
        }
    }

    map[0][195] = 5;

    for (int i = 0; i < longueur * largeur; i++) {
        map[1][i] = 0;
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 1; j < 8; j++) {
            map[1][i * longueur + j] = 2;
        }
    }

    for (int i = 5; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            map[1][i * longueur + j] = 1;
        }
    }

    map[1][190] = 5;


    while (niveauActuel < nombreNiveaux && p1.PV > 0)
    {
        niveau(map[niveauActuel], p1, nbEnnemie);
        if (defaite(p1))
        {
            clear();
            
            attron(COLOR_PAIR(2));
            printw("======GAME OVER======");
            attroff(COLOR_PAIR(2));
            refresh();
            getch();
            break;
        }

        if (victoire(map[niveauActuel], p1))
        {
            niveauActuel++;
            if (niveauActuel < nombreNiveaux)
            {
                p1.x = 5;
                p1.y = 1;

                clear();
               
                attron(COLOR_PAIR(8));
                printw("======Niveau suivant======");
                attroff(COLOR_PAIR(8));
                refresh();
                Sleep(2500);
            }
            else
            {
                clear();
                
                attron(COLOR_PAIR(4));
                printw("======VICTOIRE======");
                attroff(COLOR_PAIR(4));
                refresh();
                getch();
            }
        }
    }
    endwin();
}



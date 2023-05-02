#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

/*Plik w ktorym znajduja sie klasy obiektow jakie sa w grze*/

#define DisplayTitle "STATKI"
#define DisplayWidth 1200         //definiujemy nazwe i wymiary okna gry
#define DisplayHeight 540

#pragma once

class GameSystem {
public:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;         //klasa bazowa ze zdefiniwanym oknem, kolejka wydarzen i wydarzeniem
    ALLEGRO_EVENT event;

    bool running;

    virtual void init();              //metody do inicjalizacji i zniszczenia displayu
    virtual void destroy();
};

class Menu : public GameSystem {
public:
    ALLEGRO_BITMAP* tytul;
    ALLEGRO_BITMAP* tlo;                          //klasa ekranu menu zawierająca wszystkie obrazy widoczne w menu gry
    ALLEGRO_BITMAP* graj;                       
    ALLEGRO_BITMAP* exit;
    ALLEGRO_BITMAP* jakgrac;
    ALLEGRO_BITMAP* instrukcje;

    bool CzyInstrukcje;
    int Gwidth;
    int Gheight;
    int Ewidth;                         //zawiera tez zmienne ulatwiajace rysowanie bitmap na displayu oraz obsluge roznych ekranow
    bool CzyMenu;

    void init(char Tytul[], char Tlo[], char Graj[], char Exit[], char Jakgrac[], char Instrukcje[]);
    void drawMenu();
    void destroy();                                     //konstruktor do inicjalizacji menu, metody do narysowania i zniszczenia
};

class Pole : public GameSystem {
public:
    ALLEGRO_BITMAP* pole;
    ALLEGRO_BITMAP* hit;
    ALLEGRO_BITMAP* miss;
    
    int x;
    int y;
    bool CzyStatek;
    bool czyTrafione;
    bool wokolStatku;


    Pole(char Pole[], char Hit[], char Miss[], int x, int y, bool statek, bool trafione, bool wokol);

};

class PlanszaGry : public GameSystem {
public:
    std::vector <Pole*> Pola;

    void init();
    void destroy();
    void drawplansza();
};

class Ustawianie : public GameSystem {
public:                                       //klasa ekranu ustawiania statkow
    bool CzyUstawianie;
    ALLEGRO_BITMAP* NapisObracanie;
    ALLEGRO_BITMAP* SrodPanel;
    ALLEGRO_BITMAP* Litery;
    ALLEGRO_BITMAP* Cyfry;
    ALLEGRO_BITMAP* Reset;
    ALLEGRO_BITMAP* Exit;
    ALLEGRO_BITMAP* Graj;
    int ZajetePola{0};

    void init(char Napis[], char Panel[], char litery[], char cyfry[], char reset[], char exit[] ,char graj[]);    //metody do jej inicjalizacji, rysowania i zniszczenia
    void drawUstawianie(PlanszaGry &board);
    void destroy();
};

class Statek1 : public GameSystem {
public:
    ALLEGRO_BITMAP* ship1;
    int defaultX;
    int defaultY;
    float x;
    float y;
    float degree;
    bool isDragged;
    bool CzyUstawiony;
    int Iczesc;

    Statek1(char statek1[], float x, float y, int defaultx, int defaulty);
    void drawstatek1(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie &screen);
    void zaznaczwokol1(ALLEGRO_EVENT event, PlanszaGry &board);
};

class Statek2 : public GameSystem {
public:
    ALLEGRO_BITMAP* ship2;
    ALLEGRO_BITMAP* ship2rotated;
    int defaultX;
    int defaultY;
    float x;
    float y;
    float degree;
    bool obrocony;
    bool isDragged;
    bool CzyUstawiony;
    int Iczesc;
    int IIczesc;

    Statek2(char statek2[], char statek2r[], float x, float y, int defaultx, int defaulty);
    void drawstatek2(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen);
    void zaznaczwokol2(ALLEGRO_EVENT event, PlanszaGry &board);
};

class Statek3 : public GameSystem {
public:
    ALLEGRO_BITMAP* ship3;
    int defaultX;
    int defaultY;
    float x;
    float y;
    float degree;
    bool isDragged;
    bool CzyUstawiony;
    int Iczesc;
    int IIczesc;
    int IIIczesc;

    Statek3(char statek3[], float x, float y, int defaultx, int defaulty);
    void drawstatek3(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen);
    void zaznaczwokol3(ALLEGRO_EVENT event, PlanszaGry& board);
};

class Statek4 : public GameSystem {
public:
    ALLEGRO_BITMAP* ship4;
    int defaultX;
    int defaultY;
    float x;
    float y;
    float degree;
    bool isDragged;
    bool CzyUstawiony;
    int Iczesc;
    int IIczesc;
    int IIIczesc;
    int IVczesc;

    Statek4(char statek4[], float x, float y, int defaultx, int defaulty);
    void drawstatek4(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen);
    void zaznaczwokol4(ALLEGRO_EVENT event, PlanszaGry& board);
};

class ArmiaGracz : public GameSystem {
public:
    std::vector <Statek1*> statki1;
    std::vector <Statek2*> statki2;
    std::vector <Statek3*> statki3;
    std::vector <Statek4*> statki4;

    void init();
    void drawarmia(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie &screen);
    void restart(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen);
    void destroy();
};

class PlanszaPrzeciwnik {
public:
    std::vector <Pole*> PolaPrzeciwnik;

    void init();
    void destroy();
    void drawplanszaprzeciwnika();
};

class GamePlay : public GameSystem {
public:
    bool CzyGameplay;
    bool CzyExit;
    bool CzyWin;
    bool CzyLose;
    ALLEGRO_BITMAP* SrodPanel;
    ALLEGRO_BITMAP* Litery;
    ALLEGRO_BITMAP* Cyfry;
    ALLEGRO_BITMAP* Exit;
    ALLEGRO_BITMAP* ExitScreen;
    ALLEGRO_BITMAP* Win;
    ALLEGRO_BITMAP* Lose;

    void init(Ustawianie &ustawianie, char exitscreen[], char win[], char lose[]);
    void drawgameplay(PlanszaPrzeciwnik& enemyboard);
    void partia(ALLEGRO_EVENT event, PlanszaGry& board, PlanszaPrzeciwnik& enemyboard, Ustawianie& screen);
    void destroy();
};
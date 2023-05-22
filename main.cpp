/**
 * @file main.cpp
 *
 * @brief Plik zawierający funkcję main.
 */

#include "GameSystem.h"
#include "Petla.h"

 /**
  * @brief Funkcja główna programu. 
  * Funkcja main jest punktem wejścia programu. Tworzy obiekty różnych klas, inicjalizuje je, a następnie wywołuje główną pętlę gry.
  * @return Wartość zwracana przez program.
  */
int main() {
    // Ścieżki do plików graficznych i dźwiękowych
    char tytul[] = "elements/tytul.png";
    char tlo[] = "elements/tlomenu.png";
    char graj[] = "elements/graj.png";
    char exit[] = "elements/exit.png";
    char jakgrac[] = "elements/jakgrac.png";
    char instrukcje[] = "elements/instrukcje.png";
    char napisobracanie[] = "elements/obracanie.png";
    char srodpanel[] = "elements/kolumna.png";
    char litery[] = "elements/litery.png";
    char cyfry[] = "elements/liczby.png";
    char reset[] = "elements/reset_statki.png";
    char grajustawianie[] = "elements/graj_ustawianie.png";
    char exitustawianie[] = "elements/wyjscie.png";
    char losujustawianie[] = "elements/losuj_ustawianie.png";
    char losujwarning[] = "elements/zresetuj_statki.png";
    char dzwiek[] = "sounds/click.wav";
    char grajsound[] = "sounds/startgame.wav";

    // Tworzenie obiektów
    GameSystem gamesystem;
    Menu menuscreen;
    Ustawianie ustawianiescreen;
    PlanszaGry plansza;
    PlanszaGry enemyboard;
    ArmiaGracz armiagracz;
    ArmiaPrzeciwnik armiaprzeciwnik;
    GamePlay gameplayscreen;

    // Inicjalizacja obiektów
    gamesystem.init(dzwiek);
    menuscreen.init(tytul, tlo, graj, exit, jakgrac, instrukcje);
    ustawianiescreen.init(napisobracanie, srodpanel, litery, cyfry, reset, exitustawianie, grajustawianie, losujustawianie, losujwarning, grajsound);

    // Wyświetlanie menu
    menuscreen.drawMenu();

    // Główna pętla gry
    PetlaGry(gamesystem, menuscreen, ustawianiescreen, plansza, enemyboard, armiagracz, armiaprzeciwnik, gameplayscreen);

    // Zwalnianie zasobów
    gamesystem.destroy();

    return 0;
}

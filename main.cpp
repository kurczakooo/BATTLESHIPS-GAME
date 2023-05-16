#include "GameSystem.h"
#include "Petla.h"
#include "allegro5/allegro_primitives.h"

int main() {

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

	GameSystem gamesystem;
	Menu menuscreen;
	Ustawianie ustawianiescreen;
	PlanszaGry plansza;
	PlanszaPrzeciwnik enemyboard;
	ArmiaGracz armiagracz;
	ArmiaPrzeciwnik armiaprzeciwnik;
	GamePlay gameplayscreen;

	gamesystem.init(dzwiek);
	menuscreen.init(tytul, tlo, graj, exit, jakgrac, instrukcje);
	menuscreen.drawMenu();
	ustawianiescreen.init(napisobracanie, srodpanel, litery, cyfry, reset, exitustawianie, grajustawianie, losujustawianie, losujwarning);
	
	PetlaGry(gamesystem, menuscreen, ustawianiescreen, plansza, enemyboard, armiagracz, armiaprzeciwnik, gameplayscreen);

	armiagracz.destroy();
	plansza.destroy();
	menuscreen.destroy();
	ustawianiescreen.destroy();
	gamesystem.destroy();
	
	return 0;
}

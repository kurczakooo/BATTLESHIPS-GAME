#include "Petla.h"
/*Plik definiujacy dzialanie fuknkji petli gry, postanowilem wylaczyc ja z pliku gamesystem.cpp, bo robila sie duza
w visual studio do projektu mozna przulaczyc tylko jeden plik naglowkowy, abu podlaczyc kolejny nalezy wejsc projekt->
wlasciwosci->c++/c->zaawansowane->plik wymuszonego doloczenia i wpisac sciezke do pliku naglowkowego*/

char exitscreen[] = "elements/exit_gameplay.png";
char win[] = "elments/win.png";
char lose[] = "elements/lose.png";

void PetlaGry(GameSystem& gamesystem, Menu& menu, Ustawianie& ustawianie, PlanszaGry& plansza, PlanszaPrzeciwnik& enemyboard, ArmiaGracz& armiagracz, GamePlay& gamescreen) {

	while (gamesystem.running) { //glowna petla

		al_wait_for_event(gamesystem.queue, &gamesystem.event); //deklaracja ze kolejka czeka na wydarzenia

		if (gamesystem.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {   //warunek zamkniecia okna 
			int koniec = al_show_native_message_box(gamesystem.display, DisplayTitle, "", "Czy napewno chcesz zamknac gre? Zamkniecie spowoduje utrate postepu.", NULL, ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
			if(koniec == 1) gamesystem.running = false;
		}

		if (menu.CzyMenu) {
			ustawianie.CzyUstawianie = false;
			gamescreen.CzyGameplay = false;
			gamescreen.CzyExit = false;
			menu.CzyInstrukcje = false;
			menu.drawMenu();

			if (gamesystem.event.mouse.x >= 1117 && gamesystem.event.mouse.x <= 1177 && gamesystem.event.mouse.y >= 0 && gamesystem.event.mouse.y <= 100) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					menu.CzyMenu = false;
					menu.CzyInstrukcje = true;
				}
			}

			if (gamesystem.event.mouse.x >= 483 && gamesystem.event.mouse.x <= 718 && gamesystem.event.mouse.y >= 410 && gamesystem.event.mouse.y <= 485) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					gamesystem.running = false;
				}
			}
			
			if (gamesystem.event.mouse.x >= 475 && gamesystem.event.mouse.x <= 725 && gamesystem.event.mouse.y >= 220 && gamesystem.event.mouse.y <= 320) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					ustawianie.CzyUstawianie = true;
 					armiagracz.init();
					plansza.init(); 
					menu.CzyMenu = false;
				}
			}
		}

		if (menu.CzyInstrukcje) {
			al_draw_bitmap(menu.instrukcje, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);
			ustawianie.CzyUstawianie = false;
			gamescreen.CzyGameplay = false;
			gamescreen.CzyExit = false;
			menu.CzyMenu = false;

			if (gamesystem.event.mouse.x > 900 || gamesystem.event.mouse.x < 300 || gamesystem.event.mouse.y > 470 || gamesystem.event.mouse.y < 70) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && gamesystem.event.mouse.button == 1) {
					menu.CzyInstrukcje = false;
					menu.CzyMenu = true;
				}
			}
		}

		if (ustawianie.CzyUstawianie) {
			menu.CzyMenu = false;
			gamescreen.CzyGameplay = false;
			gamescreen.CzyExit = false;
			menu.CzyInstrukcje = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			ustawianie.drawUstawianie(plansza);
			plansza.drawplansza();
			armiagracz.drawarmia(gamesystem.event, plansza, ustawianie);

			if (gamesystem.event.mouse.x >= 514 && gamesystem.event.mouse.x <= 570 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					ustawianie.CzyUstawianie = false;
					ustawianie.ZajetePola = 0;
					plansza.destroy();
					armiagracz.destroy();
					menu.drawMenu();
				}
			}

			if (gamesystem.event.mouse.x >= 617 && gamesystem.event.mouse.x <= 680 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					armiagracz.restart(gamesystem.event, plansza, ustawianie);
				}
			}

			if (ustawianie.ZajetePola == 20 && gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
				if (gamesystem.event.mouse.x >= 508 && gamesystem.event.mouse.x <= 692 && gamesystem.event.mouse.y >= 235 && gamesystem.event.mouse.y <= 305) {
					ustawianie.CzyUstawianie = false;
					gamescreen.CzyGameplay = true;
					gamescreen.init(ustawianie, exitscreen, win, lose);
					enemyboard.init();
				}
			}
		}

		if (gamescreen.CzyGameplay) {
			menu.CzyMenu = false;
			ustawianie.CzyUstawianie = false;
			gamescreen.CzyExit = false;
			menu.CzyInstrukcje = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			gamescreen.drawgameplay(enemyboard);
			plansza.drawplansza();
			armiagracz.drawarmia(gamesystem.event, plansza, ustawianie);
			gamescreen.partia(gamesystem.event, plansza, enemyboard, ustawianie);

			if (gamesystem.event.mouse.x >= 514 && gamesystem.event.mouse.x <= 570 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					gamescreen.CzyGameplay = false;
					gamescreen.CzyExit = true;
				}
			}
		}

		if (gamescreen.CzyExit) {
			menu.CzyMenu = false;
			ustawianie.CzyUstawianie = false;
			menu.CzyInstrukcje = false;
			al_draw_bitmap(gamescreen.ExitScreen, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);

			if (gamesystem.event.mouse.x >= 345 && gamesystem.event.mouse.x <= 480 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					ustawianie.ZajetePola = 0;
					al_clear_to_color(al_map_rgb(255, 255, 255));
					plansza.destroy();
					armiagracz.destroy();
					menu.drawMenu();
				}
			}

			if (gamesystem.event.mouse.x >= 700 && gamesystem.event.mouse.x <= 860 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					gamescreen.CzyExit = false;
					gamescreen.CzyGameplay = true;

				}
			}
		}

		al_flip_display();
	}
}

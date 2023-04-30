#include "Petla.h"
/*Plik definiujacy dzialanie fuknkji petli gry, postanowilem wylaczyc ja z pliku gamesystem.cpp, bo robila sie duza
w visual studio do projektu mozna przulaczyc tylko jeden plik naglowkowy, abu podlaczyc kolejny nalezy wejsc projekt->
wlasciwosci->c++/c->zaawansowane->plik wymuszonego doloczenia i wpisac sciezke do pliku naglowkowego*/

void PetlaGry(GameSystem& gamesystem, Menu& menu, Ustawianie& ustawianie, PlanszaGry& plansza, ArmiaGracz& armiagracz) {

	while (gamesystem.running) { //glowna petla

		al_wait_for_event(gamesystem.queue, &gamesystem.event); //deklaracja ze kolejka czeka na wydarzenia

		if (gamesystem.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {   //warunek zamkniecia okna 
			int koniec = al_show_native_message_box(gamesystem.display, DisplayTitle, "", "Czy napewno chcesz zamknac gre? Zamkniecie spowoduje utrate postepu.", NULL, ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
			if(koniec == 1) gamesystem.running = false;
		}

		if (menu.CzyInstrukcje && gamesystem.event.mouse.x > 900 || gamesystem.event.mouse.x < 300) {
			if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				menu.CzyInstrukcje = false;
				menu.drawMenu();
				menu.CzyMenu = true;
			}
		}

		if (menu.CzyInstrukcje && gamesystem.event.mouse.y > 470 || gamesystem.event.mouse.y < 70) {
			if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				menu.CzyInstrukcje = false;
				menu.drawMenu();
				menu.CzyMenu = true;
			}
		}

		if (gamesystem.event.mouse.x >= 1117 && gamesystem.event.mouse.x <= 1177 && gamesystem.event.mouse.y >= 0 && gamesystem.event.mouse.y <= 100) {
			if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				al_draw_bitmap(menu.instrukcje, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);
				menu.CzyInstrukcje = true;
				menu.CzyMenu = false;
			}
		}

		if (menu.CzyMenu) {
			if (gamesystem.event.mouse.x >= 483 && gamesystem.event.mouse.x <= 718 && gamesystem.event.mouse.y >= 410 && gamesystem.event.mouse.y <= 485) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					std::cout << "koniec ";
					gamesystem.running = false;
				}
			}
			
			if (gamesystem.event.mouse.x >= 475 && gamesystem.event.mouse.x <= 725 && gamesystem.event.mouse.y >= 220 && gamesystem.event.mouse.y <= 320) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					ustawianie.CzyUstawianie = true;
 					armiagracz.init();
					plansza.init(); 
					menu.CzyMenu = false;
				}
			}
		}

		if (ustawianie.CzyUstawianie) {
			menu.CzyMenu = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			ustawianie.drawUstawianie(plansza);
			plansza.drawplansza();
			armiagracz.drawarmia(gamesystem.event, plansza, ustawianie);

			if (gamesystem.event.mouse.x >= 514 && gamesystem.event.mouse.x <= 570 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					ustawianie.CzyUstawianie = false;
					plansza.destroy();
					armiagracz.destroy();
					menu.drawMenu();
				}
			}

			if (gamesystem.event.mouse.x >= 617 && gamesystem.event.mouse.x <= 680 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					armiagracz.restart(gamesystem.event, plansza, ustawianie);
				}
			}
		}
		al_flip_display();
	}
}

/*  warunek do zaznaczanie juz pol trafionych
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (event.mouse.x > pole->x && event.mouse.x < pole->x + 40 && event.mouse.y > pole->y && event.mouse.y < pole->y + 40) {
				pole->pole = pole->miss;
			}
		}
*/
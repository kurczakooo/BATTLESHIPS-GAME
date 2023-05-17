#include "Petla.h"
/*Plik definiujacy dzialanie fuknkji petli gry, postanowilem wylaczyc ja z pliku gamesystem.cpp, bo robila sie duza
w visual studio do projektu mozna przulaczyc tylko jeden plik naglowkowy, abu podlaczyc kolejny nalezy wejsc projekt->
wlasciwosci->c++/c->zaawansowane->plik wymuszonego doloczenia i wpisac sciezke do pliku naglowkowego*/

char exitscreen[] = "elements/exit_gameplay.png";
char win[] = "elements/win.png";
char lose[] = "elements/lose.png";
char wrongchoice[] = "elements/wrong_choice.png";
char outofboard[] = "elements/out_of_board.png";
char tiletemp[] = "elements/pole.png";
char hitsound[] = "sounds/hit.wav";
char misssound[] = "sounds/miss.wav";
char winsound[] = "sounds/win.wav";
char losesound[] = "sounds/lose.wav";

void PetlaGry(GameSystem& gamesystem, Menu& menu, Ustawianie& ustawianie, PlanszaGry& plansza, PlanszaGry& enemyboard, ArmiaGracz& armiagracz, ArmiaPrzeciwnik& armiaprzeciwnik, GamePlay& gamescreen) {

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
			gamescreen.CzyWin = false;
			gamescreen.CzyLose = false;
			menu.CzyInstrukcje = false;
			menu.drawMenu();

			if (gamesystem.event.mouse.x >= 1117 && gamesystem.event.mouse.x <= 1177 && gamesystem.event.mouse.y >= 0 && gamesystem.event.mouse.y <= 100) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					menu.CzyMenu = false;
					menu.CzyInstrukcje = true;
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}

			if (gamesystem.event.mouse.x >= 483 && gamesystem.event.mouse.x <= 718 && gamesystem.event.mouse.y >= 410 && gamesystem.event.mouse.y <= 485) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					gamesystem.running = false;
				}
			}
			
			if (gamesystem.event.mouse.x >= 475 && gamesystem.event.mouse.x <= 725 && gamesystem.event.mouse.y >= 220 && gamesystem.event.mouse.y <= 320) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu.CzyInstrukcje = false;
					menu.CzyMenu = true;
				}
			}
		}

		if (ustawianie.CzyUstawianie) {
			menu.CzyMenu = false;
			gamescreen.CzyGameplay = false;
			gamescreen.CzyExit = false;
			gamescreen.CzyWin = false;
			gamescreen.CzyLose = false;
			menu.CzyInstrukcje = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			ustawianie.DrawUstawianie(plansza);
			plansza.drawplansza();
			armiagracz.drawarmia(gamesystem.event, plansza, ustawianie);

			if (gamesystem.event.mouse.x >= 514 && gamesystem.event.mouse.x <= 570 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.CzyUstawianie = false;
					ustawianie.ZajetePola = 0;
					plansza.destroy();
					armiagracz.destroy();
					menu.CzyMenu = true;
				}
			}

			if (gamesystem.event.mouse.x >= 508 && gamesystem.event.mouse.x <= 692 && gamesystem.event.mouse.y >= 390 && gamesystem.event.mouse.y <= 444) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					armiagracz.LosujPlansze(gamesystem.event, plansza, ustawianie);
					armiagracz.CzyMoznaLosowac = false;
				}
			}

			if (gamesystem.event.mouse.x >= 617 && gamesystem.event.mouse.x <= 680 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					armiagracz.restart(gamesystem.event, plansza, ustawianie);
				}
			}

			if (ustawianie.ZajetePola == 20 && gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
				if (gamesystem.event.mouse.x >= 508 && gamesystem.event.mouse.x <= 692 && gamesystem.event.mouse.y >= 235 && gamesystem.event.mouse.y <= 305) {
					al_play_sample(ustawianie.GrajSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.CzyUstawianie = false;
					gamescreen.CzyGameplay = true;
					armiaprzeciwnik.init();
					gamescreen.init(ustawianie, exitscreen, win, lose, wrongchoice, outofboard, hitsound, misssound, winsound, losesound);
					enemyboard.initprzeciwnik();
					for (auto tile1 : enemyboard.Pola) {
						tile1->czyTrafione = false;
						tile1->pole = al_load_bitmap(tiletemp);
					}
					armiaprzeciwnik.LosujPlansze(enemyboard);
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
			armiagracz.drawarmia(gamesystem.event, plansza, ustawianie);
			plansza.drawplansza();
			gamescreen.Rozgrywka(gamesystem.event, plansza, enemyboard, ustawianie);
/*			for (int i = 0; i < 4; i++) {    //Losowanie pojedynczych statkow
				al_draw_bitmap(armiaprzeciwnik.statki1[i]->ship1, armiaprzeciwnik.statki1[i]->x, armiaprzeciwnik.statki1[i]->y, 0);
			}
			for (int i = 0; i < 3; i++) {    //Losowanie pojedynczych statkow
				al_draw_bitmap(armiaprzeciwnik.statki2[i]->ship2, armiaprzeciwnik.statki2[i]->x, armiaprzeciwnik.statki2[i]->y, 0);
			}
			for (int i = 0; i < 2; i++) {    //Losowanie pojedynczych statkow
				al_draw_bitmap(armiaprzeciwnik.statki3[i]->ship3, armiaprzeciwnik.statki3[i]->x, armiaprzeciwnik.statki3[i]->y, 0);
			}
			al_draw_bitmap(armiaprzeciwnik.statki4[0]->ship4, armiaprzeciwnik.statki4[0]->x, armiaprzeciwnik.statki4[0]->y, 0);
*/
			if (gamescreen.TrafionePlanszaAI == 20) {
				al_play_sample(gamescreen.WinSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				Sleep(1000);
				gamescreen.CzyWin = true;
			}
			
			if (gamescreen.TrafionePlanszaGracz == 20) {
				al_play_sample(gamescreen.LoseSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				Sleep(1000);
				gamescreen.CzyLose = true;
			}

			if (gamesystem.event.mouse.x >= 514 && gamesystem.event.mouse.x <= 570 && gamesystem.event.mouse.y >= 461 && gamesystem.event.mouse.y <= 521) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					gamescreen.CzyGameplay = false;
					gamescreen.CzyExit = true;
				}
			}
		}

		if (gamescreen.CzyWin) {
			gamescreen.CzyGameplay = false;
			menu.CzyMenu = false;
			ustawianie.CzyUstawianie = false;
			menu.CzyInstrukcje = false;
			al_draw_bitmap(gamescreen.Win, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);

			if (gamesystem.event.mouse.x >= 345 && gamesystem.event.mouse.x <= 465 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.ZajetePola = 0;
					gamescreen.TrafionePlanszaAI = 0;
					gamescreen.TrafionePlanszaGracz = 0;
					plansza.destroy();
					armiagracz.destroy();
					enemyboard.destroyprzeciwnik();
					armiaprzeciwnik.destroy();
					menu.CzyMenu = true;
				}
			}

			if (gamesystem.event.mouse.x >= 590 && gamesystem.event.mouse.x <= 860 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.ZajetePola = 0;
					gamescreen.TrafionePlanszaAI = 0;
					gamescreen.TrafionePlanszaGracz = 0;
					plansza.destroy();
					armiagracz.destroy();
					enemyboard.destroyprzeciwnik();
					armiaprzeciwnik.destroy();
					armiagracz.init();
					plansza.init();
					gamescreen.CzyWin = false;
					ustawianie.CzyUstawianie = true;
				}
			}
		}

		if (gamescreen.CzyLose) {
			gamescreen.CzyGameplay = false;
			menu.CzyMenu = false;
			ustawianie.CzyUstawianie = false;
			menu.CzyInstrukcje = false;
			al_draw_bitmap(gamescreen.Lose, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);

			if (gamesystem.event.mouse.x >= 345 && gamesystem.event.mouse.x <= 465 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.ZajetePola = 0;
					gamescreen.TrafionePlanszaAI = 0;
					gamescreen.TrafionePlanszaGracz = 0;
					plansza.destroy();
					armiagracz.destroy();
					enemyboard.destroyprzeciwnik();
					armiaprzeciwnik.destroy();
					menu.CzyMenu = true;
				}
			}

			if (gamesystem.event.mouse.x >= 590 && gamesystem.event.mouse.x <= 860 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.ZajetePola = 0;
					gamescreen.TrafionePlanszaAI = 0;
					gamescreen.TrafionePlanszaGracz = 0;
					plansza.destroy();
					armiagracz.destroy();
					enemyboard.destroyprzeciwnik();
					armiaprzeciwnik.destroy();
					armiagracz.init();
					plansza.init();
					gamescreen.CzyWin = false;
					ustawianie.CzyUstawianie = true;
				}
			}
		}

		if (gamescreen.CzyExit) {
			gamescreen.CzyGameplay = false;
			menu.CzyMenu = false;
			ustawianie.CzyUstawianie = false;
			menu.CzyInstrukcje = false;
			al_draw_bitmap(gamescreen.ExitScreen, DisplayWidth / 2 - 300, DisplayHeight / 2 - 200, 0);
	
			if (gamesystem.event.mouse.x >= 345 && gamesystem.event.mouse.x <= 480 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					ustawianie.ZajetePola = 0;
					gamescreen.TrafionePlanszaAI = 0;
					gamescreen.TrafionePlanszaGracz = 0;
					plansza.destroy();
					armiagracz.destroy();
					enemyboard.destroy();
					armiaprzeciwnik.destroy();
					menu.CzyMenu = true;
				}
			}

			if (gamesystem.event.mouse.x >= 700 && gamesystem.event.mouse.x <= 860 && gamesystem.event.mouse.y >= 380 && gamesystem.event.mouse.y <= 425) {
				if (gamesystem.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gamesystem.event.mouse.button == 1) {
					al_play_sample(gamesystem.dzwiek, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					gamescreen.CzyExit = false;
					gamescreen.CzyGameplay = true;
				}
			}
		}

		al_flip_display();
	}
}

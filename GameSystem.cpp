#include "GameSystem.h"

/*Plik definiujacy metody klas z GameSystem.h*/

char tile[] = "elements/tile1.png";
char hit[] = "elements/hit.png";
char miss[] = "elements/miss.png";
char statek1[] = "elements/1statek.png";
char statek2[] = "elements/2statek.png";
char statek3[] = "elements/3statek.png";
char statek4[] = "elements/4statek.png";

void GameSystem::init() {

	al_init();                    //inicjalizacja displayu, tworzenie ekranu i kolejkki na wydarzenia
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_install_mouse();

	this->display = al_create_display(DisplayWidth, DisplayHeight);
	al_set_window_title(display, DisplayTitle);
	this->queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	//rejestrowanie wydarzen na displayu i wydarzen myszki
	this->running = true;
}

void GameSystem::destroy() {
	al_destroy_display(display);      //niszczenie wszystkich elementow zawartych w klasie GameSystem
	al_destroy_event_queue(queue);
	al_uninstall_mouse();
}

void Menu::init(char Tytul[], char Tlo[], char Graj[], char Exit[], char Jakgrac[], char Instrukcje[]) {

	this->tytul = al_load_bitmap(Tytul);
	this->tlo = al_load_bitmap(Tlo);                  //inicjalizacja menu, ladowanie bitmap
	this->graj = al_load_bitmap(Graj);
	this->exit = al_load_bitmap(Exit);
	this->jakgrac = al_load_bitmap(Jakgrac);
	this->instrukcje = al_load_bitmap(Instrukcje);
	this->CzyInstrukcje = false;
	this->Gwidth = al_get_bitmap_width(graj);
	this->Gheight = al_get_bitmap_height(graj);
	this->Ewidth = al_get_bitmap_width(exit);
}

void Menu::drawMenu() {
	this->CzyMenu = true;                //pozwala na wykonywanie warunkow zwiazanych z ekranem menu(zobacz Petla.cpp lin14)
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap(tlo, 0, 0, 0);          //rysowanie menu, tla i bitmap
	al_draw_bitmap(tytul, 0, 0, 0);
	al_draw_bitmap(graj, DisplayWidth / 2 - Gwidth / 2, DisplayHeight / 2 - Gheight / 2, 0);
	al_draw_bitmap(exit, DisplayWidth / 2 - Ewidth / 2, 410, 0);
	al_draw_bitmap(jakgrac, 1117, 0, 0);
}

void Menu::destroy() {
	this->CzyMenu = false;       //dzieki temu warunki zwwiazane z ekranem menu nie dzialaja
	al_destroy_bitmap(tytul);
	al_destroy_bitmap(graj);           //niszczenie elementow ekranu menu
	al_destroy_bitmap(exit);
	al_destroy_bitmap(jakgrac);
	al_destroy_bitmap(instrukcje);
	al_destroy_bitmap(tlo);
}

Pole::Pole(char Pole[], char Hit[], char Miss[], int x, int y, bool statek, bool trafione, bool wokol) {
	this->pole = al_load_bitmap(Pole);
	this->hit = al_load_bitmap(Pole);                            //do zaznacania potem zmienic
	this->miss = al_load_bitmap(Miss);
	this->x = x;
	this->y = y;
	this->CzyStatek = statek;
	this->czyTrafione = trafione;
	this->wokolStatku = wokol;
}

void PlanszaGry::init() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->Pola.push_back(new Pole(tile, hit, miss, (i*40) + 75, (j*40) + 94, false, false, false));
		}
	}
	this->ZajetePola = 0;
}

void PlanszaGry::destroy() {
	for (auto tile = Pola.begin(); tile != Pola.end(); tile++) {
		delete *tile;
	}
	Pola.clear();
}

void PlanszaGry::drawplansza() {
	for (auto& tile1 : Pola) {
		if (tile1->wokolStatku)
			tile1->pole = tile1->miss;
		else
			tile1->pole = tile1->hit;

		al_draw_bitmap(tile1->pole, tile1->x, tile1->y, 0);
	}
}

void Ustawianie::init(char Napis[], char Panel[], char litery[], char cyfry[], char reset[], char exit[], char graj[]) {
	this->NapisObracanie = al_load_bitmap(Napis);          //inicjalizacja ekranu ustawiania statkow
	this->SrodPanel = al_load_bitmap(Panel);
	this->Litery = al_load_bitmap(litery);
	this->Cyfry = al_load_bitmap(cyfry);
	this->Reset = al_load_bitmap(reset);
	this->Exit = al_load_bitmap(exit);
	this->Graj = al_load_bitmap(graj);
}

void Ustawianie::drawUstawianie(PlanszaGry board) {
	this->CzyUstawianie = true;   //pozwala na wykonywanie warunkow zwiazych z ekranem ustawiania(zobacz Petla.cpp lin38 i 44)
	al_draw_bitmap(NapisObracanie, 700, 0, 0);     //rysowanie ekranu ustawiania statkow
	al_draw_bitmap(SrodPanel, 500, 0, 0);
	al_draw_bitmap(Litery, 76, 44, 0);
	al_draw_bitmap(Cyfry, 24, 94, 0);
	al_draw_bitmap(Reset, 617, 461, 0);
	al_draw_bitmap(Exit, 514, 461, 0);

	if (board.ZajetePola == 20)
		al_draw_bitmap(Graj, 508, 235, 0);
}

void Ustawianie::destroy() {
	this->CzyUstawianie = false;
	al_destroy_bitmap(NapisObracanie);   //niszczenie elementow klasy ustawianie
	al_destroy_bitmap(SrodPanel);
	al_destroy_bitmap(Litery);
	al_destroy_bitmap(Cyfry);
	al_destroy_bitmap(Reset);
	al_destroy_bitmap(Exit);
	al_destroy_bitmap(Graj);
}

Statek1::Statek1(char statek1[], float x, float y, int defaultx, int defaulty) {
	this->degree = 0.0;
	this->ship1 = al_load_bitmap(statek1);
	this->x = x;
	this->y = y;
	this->defaultX = defaultx;
	this->defaultY = defaulty;
	this->isDragged = false;
	this->CzyUstawiony = false;
}

void Statek1::zaznaczwokol1(ALLEGRO_EVENT event, PlanszaGry board) {
	if ((Iczesc + 1) % 10 != 0 && Iczesc != 99) {
		board.Pola[Iczesc + 1]->wokolStatku = true;     //dol statku
		wokol.push_back(Iczesc + 1);
	}
	if (Iczesc % 10 != 0 && Iczesc != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
		wokol.push_back(Iczesc - 1);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo statku
		wokol.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo statku
		wokol.push_back(Iczesc + 10);
	}
	if ((Iczesc - 9) >= 0 && (Iczesc - 9) % 10 != 0) {
		board.Pola[Iczesc - 9]->wokolStatku = true;    //lewo dol statku
		wokol.push_back(Iczesc - 9);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
		wokol.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
		wokol.push_back(Iczesc + 9);
	}
	if ((Iczesc + 11) < 99 && (Iczesc + 11) % 10 != 0) {
		board.Pola[Iczesc + 11]->wokolStatku = true;    //prawo dol statku
		wokol.push_back(Iczesc + 11);
	}
}

void Statek1::drawstatek1(ALLEGRO_EVENT event, PlanszaGry board) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 40) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (!board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						board.Pola[Iczesc]->CzyStatek = true;
						zaznaczwokol1(event, board);
						CzyUstawiony = true;
						board.ZajetePola += 20;
					}
					else {
						x = defaultX;
						y = defaultY;
						degree = 0;
						board.Pola[Iczesc]->CzyStatek = false;
					}
				}
			}
			if (x + 20 >= 475 || x + 20 <= 75 || y + 20 >= 494 || y + 20 <= 94) {
				x = defaultX;
				y = defaultY;
				degree = 0;
			}
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && !CzyUstawiony) {
			degree += 90;
			if (degree > 90)
				degree = 0;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = true;/*
			if (CzyUstawiony) {
				board.Pola[Iczesc]->CzyStatek = false;
				CzyUstawiony = false;
				for (auto& pole : wokol) {
					board.Pola[pole]->wokolStatku = false;
				}
			}*/
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship1) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship1) / 2;
	}
	al_draw_rotated_bitmap(ship1, al_get_bitmap_width(ship1) / 2, al_get_bitmap_height(ship1) / 2, x + al_get_bitmap_width(ship1) / 2, y + al_get_bitmap_height(ship1) / 2, degree * 3.14159 / 180, 0);
	//al_draw_bitmap(ship1, x, y, 0);
}

Statek2::Statek2(char statek2[], float x, float y, int defaultx, int defaulty) {
	this->ship2 = al_load_bitmap(statek2);
	this->degree = 0.0;
	this->x = x;
	this->y = y;
	this->defaultX = defaultx;
	this->defaultY = defaulty;
	this->isDragged = false;
}

void Statek2::zaznaczwokol2(ALLEGRO_EVENT event, PlanszaGry board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
		wokol.push_back(Iczesc - 1);
	}
	if ((IIczesc + 1) % 10 != 0 && IIczesc != 99) {
		board.Pola[IIczesc + 1]->wokolStatku = true;     //dol statku
		wokol.push_back(IIczesc + 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
		wokol.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
		wokol.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
		wokol.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
		wokol.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
		wokol.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
		wokol.push_back(IIczesc + 10);
	}
	if ((IIczesc - 9) >= 0 && (IIczesc - 9) % 10 != 0) {
		board.Pola[IIczesc - 9]->wokolStatku = true;    //lewo dol statku
		wokol.push_back(IIczesc - 9);
	}
	if ((IIczesc + 11) < 99 && (IIczesc + 11) % 10 != 0) {
		board.Pola[IIczesc + 11]->wokolStatku = true;    //prawo dol statku
		wokol.push_back(IIczesc + 11);
	}
}

void Statek2::drawstatek2(ALLEGRO_EVENT event, PlanszaGry board) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 80) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (!board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku && !board.Pola[i + 1]->wokolStatku && i != 99 && (i + 1) % 10 != 0) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						IIczesc = i + 1;
						board.Pola[Iczesc]->CzyStatek = true;
						board.Pola[IIczesc]->CzyStatek = true;		
						zaznaczwokol2(event, board);
						CzyUstawiony = true;
						break;
					}
					else {
						x = defaultX;
						y = defaultY;
						degree = 0;
					} 
				}
			}
			if (x + 20 >= 475 || x + 20 <= 75 || y + 20 >= 494 || y + 20 <= 94) {
				x = defaultX;
				y = defaultY;
				degree = 0;
			}
		}
	/*	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && IIczesc + 10 <= 99 && !board.Pola[IIczesc + 10]->CzyStatek) {
			degree += 90;
			if (degree > 90)
				degree = 0;
			if (degree == 90) {
				board.Pola[Iczesc]->CzyStatek = false;
				board.Pola[IIczesc + 10]->CzyStatek = true;
			}
			if(degree == 0) {
				board.Pola[Iczesc]->CzyStatek = true;
				board.Pola[IIczesc + 10]->CzyStatek = false;
			}
		}*/
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			isDragged = true;
			if (CzyUstawiony) {
				board.Pola[Iczesc]->CzyStatek = false;
				board.Pola[IIczesc]->CzyStatek = false;
				CzyUstawiony = false;
				for (auto& pole : wokol) {
					board.Pola[pole]->wokolStatku = false;
				}
			}
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship2) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship2) / 2;
	}
	al_draw_rotated_bitmap(ship2, al_get_bitmap_width(ship2) / 2, al_get_bitmap_height(ship2) - 20, x + al_get_bitmap_width(ship2) / 2, y + 60, degree * 3.14159 / 180, 0);;
}

Statek3::Statek3(char statek3[], float x, float y, int defaultx, int defaulty) {
	this->ship3 = al_load_bitmap(statek3);
	this->degree = 0.0;
	this->x = x;
	this->y = y;
	this->defaultX = defaultx;
	this->defaultY = defaulty;
	this->isDragged = false;
	this->CzyUstawiony = false;
}

void Statek3::drawstatek3(ALLEGRO_EVENT event, PlanszaGry board) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 120) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (!board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku && i != 99 && i != 98 && (i + 1) % 10 != 0) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						IIczesc = i + 1;
						IIIczesc = i + 2;
						board.Pola[Iczesc]->CzyStatek = true;
						board.Pola[IIczesc]->CzyStatek = true;
						board.Pola[IIIczesc]->CzyStatek = true;
						break;
					}
					else {
						x = defaultX;
						y = defaultY;
						degree = 0;
					}
				}
			}
			if (x + 20 >= 475 || x + 20 <= 75 || y + 20 >= 494 || y + 20 <= 94) {
				x = defaultX;
				y = defaultY;
				degree = 0;
			}
		}
/*		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && IIIczesc + 10 <= 99 && IIIczesc + 20 <= 99 && !board.Pola[IIIczesc + 10]->CzyStatek && !board.Pola[IIIczesc + 20]->CzyStatek) {
			degree += 90;
			if (degree > 90)
				degree = 0;
			if (degree == 90) {
//				board.Pola[Iczesc]->CzyStatek = false;
//				board.Pola[IIczesc]->CzyStatek = false;
//				board.Pola[IIIczesc + 10]->CzyStatek = true;
//				board.Pola[IIIczesc + 20]->CzyStatek = true;
			}
			if (degree == 0) {
//				board.Pola[Iczesc]->CzyStatek = true;
//				board.Pola[IIczesc]->CzyStatek = true;
//				board.Pola[IIIczesc + 10]->CzyStatek = false;
//				board.Pola[IIIczesc + 20]->CzyStatek = false;
			}
		}*/
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			isDragged = true;
			board.Pola[Iczesc]->CzyStatek = false;
			board.Pola[IIczesc]->CzyStatek = false;
			board.Pola[IIIczesc]->CzyStatek = false;
		}
	}

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship3) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship3) / 2;
	}
	al_draw_rotated_bitmap(ship3, al_get_bitmap_width(ship3) / 2, al_get_bitmap_height(ship3) - 20, x + al_get_bitmap_width(ship3) / 2, y + 100, degree * 3.14159 / 180, 0);
}

Statek4::Statek4(char statek4[], float x, float y, int defaultx, int defaulty) {
	this->ship4 = al_load_bitmap(statek4);
	this->degree = 0.0;
	this->x = x;
	this->y = y;
	this->defaultX = defaultx;
	this->defaultY = defaulty;
	this->isDragged = false;
	this->CzyUstawiony = false;
}

void Statek4::drawstatek4(ALLEGRO_EVENT event, PlanszaGry board) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 160) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (!board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku && i != 99 && i != 98 && i != 97 && (i + 1) % 10 != 0) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						IIczesc = i + 1;
						IIIczesc = i + 2;
						IVczesc = i + 3;
						board.Pola[Iczesc]->CzyStatek = true;
						board.Pola[IIczesc]->CzyStatek = true;
						board.Pola[IIIczesc]->CzyStatek = true;
						board.Pola[IVczesc]->CzyStatek = true;
						break;
					}
					else {
						x = defaultX;
						y = defaultY;
						degree = 0;
					}
				}
			}
			if (x + 20 >= 475 || x + 20 <= 75 || y + 20 >= 494 || y + 20 <= 94) {
				x = defaultX;
				y = defaultY;
				degree = 0;
			}
		}
	/*	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && IVczesc + 10 <= 99 && IVczesc + 20 <= 99 && IVczesc + 30 <= 99 && !board.Pola[IVczesc + 10]->CzyStatek && !board.Pola[IVczesc + 20]->CzyStatek && !board.Pola[IVczesc + 30]->CzyStatek) {
			degree += 90;
			if (degree > 90)
				degree = 0;
			if (degree == 90) {
//				board.Pola[Iczesc]->CzyStatek = false;
//				board.Pola[IIczesc]->CzyStatek = false;
//				board.Pola[IIIczesc]->CzyStatek = false;
//				board.Pola[IVczesc + 10]->CzyStatek = true;
//				board.Pola[IVczesc + 20]->CzyStatek = true;
//   			board.Pola[IVczesc + 30]->CzyStatek = true;
			}
			if (degree == 0) {
//				board.Pola[Iczesc]->CzyStatek = true;
//				board.Pola[IIczesc]->CzyStatek = true;
//				board.Pola[IIIczesc]->CzyStatek = true;
//				board.Pola[IVczesc + 10]->CzyStatek = false;
//				board.Pola[IVczesc + 20]->CzyStatek = false;
//				board.Pola[IVczesc + 30]->CzyStatek = false;
			}
		}*/
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			isDragged = true;
			board.Pola[Iczesc]->CzyStatek = false;
			board.Pola[IIczesc]->CzyStatek = false;
			board.Pola[IIIczesc]->CzyStatek = false;
			board.Pola[IVczesc]->CzyStatek = false;
		}
	}

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship4) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship4) / 2;
	}
	al_draw_rotated_bitmap(ship4, al_get_bitmap_width(ship4) / 2, al_get_bitmap_height(ship4) - 20, x + al_get_bitmap_width(ship4) / 2, y + 140, degree * 3.14159 / 180, 0);
}

void ArmiaGracz::init() {
	this->statki1.push_back(new Statek1(statek1, 810.0, 131.0, 810, 131));
	this->statki1.push_back(new Statek1(statek1, 810.0, 211.0, 810, 211));
	this->statki1.push_back(new Statek1(statek1, 810.0, 291.0, 810, 291));
	this->statki1.push_back(new Statek1(statek1, 810.0, 371.0, 810, 371));

	this->statki2.push_back(new Statek2(statek2, 890.0, 131.0, 890, 131));
	this->statki2.push_back(new Statek2(statek2, 890.0, 251.0, 890, 251));
	this->statki2.push_back(new Statek2(statek2, 890.0, 371.0, 890, 371));

	this->statki3.push_back(new Statek3(statek3, 970.0, 131.0, 970, 131));
	this->statki3.push_back(new Statek3(statek3, 970.0, 291.0, 970, 291));

	this->statki4.push_back(new Statek4(statek4, 1050.0, 131.0, 1050, 131));
}

void ArmiaGracz::drawarmia(ALLEGRO_EVENT event, PlanszaGry board) {
	for (auto& boat : statki1) {
		boat->drawstatek1(event, board);
	}
	for (auto& boat : statki2) {
		boat->drawstatek2(event, board);
	}
	for (auto& boat : statki3) {
		boat->drawstatek3(event, board);
	}
	for (auto& boat : statki4) {
		boat->drawstatek4(event, board);
	}
}
 
void ArmiaGracz::restart(ALLEGRO_EVENT event, PlanszaGry board) {
	for (auto& tile1 : board.Pola) {
		tile1->CzyStatek = false;
		tile1->wokolStatku = false;
	}
	for (auto& boat : statki1) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
	for (auto& boat : statki2) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
	}
	for (auto& boat : statki3) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
	}
	for (auto& boat : statki4) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
	}
}

void ArmiaGracz::destroy() {
	for (auto boat = statki1.begin(); boat != statki1.end(); boat++) {
		delete *boat;
	}
	statki1.clear();
	for (auto boat = statki2.begin(); boat != statki2.end(); boat++) {
		delete* boat;
	}
	statki2.clear();
	for (auto boat = statki3.begin(); boat != statki3.end(); boat++) {
		delete* boat;
	}
	statki3.clear();
	for (auto boat = statki4.begin(); boat != statki4.end(); boat++) {
		delete* boat;
	}
	statki4.clear();
}


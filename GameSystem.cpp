#include "GameSystem.h"

/*Plik definiujacy metody klas z GameSystem.h*/

char tile[] = "elements/pole.png";
char hit[] = "elements/hit.png";
char miss[] = "elements/miss.png";
char statek1[] = "elements/1statek.png";
char statek2[] = "elements/2statek.png";
char statek2r[] = "elements/2statek_rotated.png";
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
	this->hit = al_load_bitmap(Hit);                            //do zaznacania potem zmienic
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
}

void PlanszaGry::destroy() {
	for (auto tile = Pola.begin(); tile != Pola.end(); tile++) {
		delete *tile;
	}
	Pola.clear();
}

void PlanszaGry::drawplansza() {
	for (auto& tile : Pola) {
		if (tile->czyTrafione && tile->CzyStatek)
			tile->pole = tile->hit;
		else if (tile->czyTrafione && !tile->CzyStatek)
			tile->pole = tile->miss;
		al_draw_bitmap(tile->pole, tile->x, tile->y, 0);
	}
}

void Ustawianie::init(char Napis[], char Panel[], char litery[], char cyfry[], char reset[], char exit[], char graj[], char losujustawianie[], char losujwarning[]) {
	this->NapisObracanie = al_load_bitmap(Napis);          //inicjalizacja ekranu ustawiania statkow
	this->SrodPanel = al_load_bitmap(Panel);
	this->Litery = al_load_bitmap(litery);
	this->Cyfry = al_load_bitmap(cyfry);
	this->Reset = al_load_bitmap(reset);
	this->Exit = al_load_bitmap(exit);
	this->Graj = al_load_bitmap(graj);
	this->Losuj = al_load_bitmap(losujustawianie);
	this->LosujWarning = al_load_bitmap(losujwarning);
}

void Ustawianie::DrawUstawianie(PlanszaGry &board) {
	this->CzyUstawianie = true;   //pozwala na wykonywanie warunkow zwiazych z ekranem ustawiania(zobacz Petla.cpp lin38 i 44)
	al_draw_bitmap(NapisObracanie, 700, 0, 0);     //rysowanie ekranu ustawiania statkow
	al_draw_bitmap(SrodPanel, 500, 0, 0);
	al_draw_bitmap(Litery, 76, 44, 0);
	al_draw_bitmap(Cyfry, 24, 94, 0);
	al_draw_bitmap(Reset, 617, 461, 0);
	al_draw_bitmap(Exit, 514, 461, 0);
	al_draw_bitmap(Losuj, 508, 390, 0);

	if (ZajetePola == 20)
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

void Statek1::zaznaczwokol1(ALLEGRO_EVENT event, PlanszaGry &board) {
	if ((Iczesc + 1) % 10 != 0 && Iczesc != 99) {
		board.Pola[Iczesc + 1]->wokolStatku = true;     //dol statku
	}
	if (Iczesc % 10 != 0 && Iczesc != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo statku
	}
	if ((Iczesc + 10) <= 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo statku
	}
	if ((Iczesc - 9) >= 0 && (Iczesc - 9) % 10 != 0) {
		board.Pola[Iczesc - 9]->wokolStatku = true;    //lewo dol statku
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
	}
	if ((Iczesc + 11) <= 99 && (Iczesc + 11) % 10 != 0) {
		board.Pola[Iczesc + 11]->wokolStatku = true;    //prawo dol statku
	}
}

void Statek1::drawstatek1(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie &screen) {
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
						screen.ZajetePola++;
						zaznaczwokol1(event, board);
						CzyUstawiony = true;
						break;
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
			isDragged = true;
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship1) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship1) / 2;
	}
	al_draw_rotated_bitmap(ship1, al_get_bitmap_width(ship1) / 2, al_get_bitmap_height(ship1) / 2, x + al_get_bitmap_width(ship1) / 2, y + al_get_bitmap_height(ship1) / 2, degree * 3.14159 / 180, 0);
}

Statek2::Statek2(char statek2[], char statek2r[], float x, float y, int defaultx, int defaulty) {
	this->ship2 = al_load_bitmap(statek2);
	this->ship2rotated = al_load_bitmap(statek2r);
	this->degree = 0.0;
	this->x = x;
	this->y = y;
	this->defaultX = defaultx;
	this->defaultY = defaulty;
	this->isDragged = false;
}

void Statek2::zaznaczwokol2(ALLEGRO_EVENT event, PlanszaGry &board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
	}
	if ((IIczesc + 1) % 10 != 0 && IIczesc != 99) {
		board.Pola[IIczesc + 1]->wokolStatku = true;     //dol statku
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
	}
	if ((IIczesc - 9) >= 0 && (IIczesc - 9) % 10 != 0) {
		board.Pola[IIczesc - 9]->wokolStatku = true;    //lewo dol statku
	}
	if ((IIczesc + 11) <= 99 && (IIczesc + 11) % 10 != 0) {
		board.Pola[IIczesc + 11]->wokolStatku = true;    //prawo dol statku
	}
}

void Statek2::drawstatek2(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 80) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (i <= 98 && (i + 1) % 10 != 0 && !board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku && !board.Pola[i + 1]->wokolStatku) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						IIczesc = i + 1;
						board.Pola[Iczesc]->CzyStatek = true;
						board.Pola[IIczesc]->CzyStatek = true;	
						screen.ZajetePola += 2;
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
	/*	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && !CzyUstawiony) {
			if (obrocony) {
				std::swap(ship2, ship2rotated);
				y -= 40;
				defaultY -= 40;
				obrocony = false;
			}
			else {/////////////////////////////////////////////////////////////////
				std::swap(ship2, ship2rotated);
				y += 40;
				defaultY += 40;
				obrocony = true;
			}
			for (int i = 1; i <= 100; i++) {
				std::cout << board.Pola[i-1]->CzyStatek<<" ";
				if (i % 10 == 0)
					std::cout << "\n";
			}
		}*/
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = true;
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship2) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship2) / 2;
	}
	//al_draw_rotated_bitmap(ship2, al_get_bitmap_width(ship2) / 2, al_get_bitmap_height(ship2) - 20, x + al_get_bitmap_width(ship2) / 2, y + 60, degree * 3.14159 / 180, 0);;
	al_draw_bitmap(ship2, x, y ,0);
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

void Statek3::zaznaczwokol3(ALLEGRO_EVENT event, PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    //lewo III czesci
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    //prawo III czesci
	}
	if ((IIIczesc + 1) % 10 != 0 && IIIczesc != 99) {
		board.Pola[IIIczesc + 1]->wokolStatku = true;      //dol statku
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    //lewo dol statku
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    //prawo dol statku
	}
}

void Statek3::drawstatek3(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 120) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (i <= 97 && (i + 1) % 10 != 0 && (i + 2) % 10 != 0 && !board.Pola[i]->CzyStatek && !board.Pola[i+1]->CzyStatek && !board.Pola[i+2]->CzyStatek && !board.Pola[i]->wokolStatku
						&& !board.Pola[i+1]->wokolStatku && !board.Pola[i+2]->wokolStatku) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						IIczesc = i + 1;
						IIIczesc = i + 2;
						board.Pola[Iczesc]->CzyStatek = true;
						board.Pola[IIczesc]->CzyStatek = true;
						board.Pola[IIIczesc]->CzyStatek = true;
						screen.ZajetePola += 3;
						zaznaczwokol3(event, board);
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
		/*if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && !CzyUstawiony) {
			degree += 90;
			if (degree > 90)
				degree = 0;
		}*/
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = true;
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

void Statek4::zaznaczwokol4(ALLEGRO_EVENT event, PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    //lewo III czesci
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    //prawo III czesci
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    //lewo IVczesci
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    //prawo IVczesci
	}
	if ((IVczesc + 1) % 10 != 0 && IVczesc != 99) {
		board.Pola[IVczesc + 1]->wokolStatku = true;      //dol statku
	}
	if ((IVczesc - 9) >= 0 && (IVczesc - 9) % 10 != 0) {
		board.Pola[IVczesc - 9]->wokolStatku = true;    //lewo dol statku
	}
	if ((IVczesc + 11) <= 99 && (IVczesc + 11) % 10 != 0) {
		board.Pola[IVczesc + 11]->wokolStatku = true;    //prawo dol statku
	}
}

void Statek4::drawstatek4(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen) {
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 160) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = false;
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (i <= 96 && (i + 1) % 10 != 0 && (i + 2) % 10 != 0 && (i + 3) % 10 != 0 && !board.Pola[i]->CzyStatek && !board.Pola[i+1]->CzyStatek && !board.Pola[i+2]->CzyStatek 
						&& !board.Pola[i+3]->CzyStatek && !board.Pola[i]->wokolStatku && !board.Pola[i+1]->wokolStatku && !board.Pola[i+2]->wokolStatku && !board.Pola[i+3]->wokolStatku) {
						
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
						screen.ZajetePola += 4;
						zaznaczwokol4(event, board);
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
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2) {
		//	degree += 90;
		//	if (degree > 90)
		//		degree = 0;
			std::cout << "\n";
			for (int i = 1; i <= 100; i++) {
				std::cout << board.Pola[i - 1]->wokolStatku << " ";
				if (i % 10 == 0)
					std::cout << "\n";
			}
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = true;
		}
	}

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship4) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship4) / 2;
	}
	al_draw_rotated_bitmap(ship4, al_get_bitmap_width(ship4) / 2, al_get_bitmap_height(ship4) - 20, x + al_get_bitmap_width(ship4) / 2, y + 140, degree * 3.14159 / 180, 0);
}

void ArmiaGracz::init() {
	this->statki1.push_back(new Statek1(statek1, 728.0, 94.0, 728, 94));
	this->statki1.push_back(new Statek1(statek1, 808.0, 94.0, 808, 94));
	this->statki1.push_back(new Statek1(statek1, 888.0, 94.0, 888, 94));
	this->statki1.push_back(new Statek1(statek1, 968.0, 94.0, 968, 94));

	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 174.0, 728, 174));
	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 294.0, 728, 294));
	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 414.0, 728, 414));

	this->statki3.push_back(new Statek3(statek3, 848.0, 174.0, 848, 174));
	this->statki3.push_back(new Statek3(statek3, 848.0, 334.0, 848, 334));

	this->statki4.push_back(new Statek4(statek4, 1008.0, 214.0, 1008, 214));

	CzyMoznaLosowac = true;
}

void ArmiaGracz::drawarmia(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie &screen) {
	for (auto& boat : statki1) {
		boat->drawstatek1(event, board, screen);
	}
	for (auto& boat : statki2) {
		boat->drawstatek2(event, board, screen);
	}
	for (auto& boat : statki3) {
		boat->drawstatek3(event, board, screen);
	}
	for (auto& boat : statki4) {
		boat->drawstatek4(event, board, screen);
	}
}
 
void ArmiaGracz::restart(ALLEGRO_EVENT event, PlanszaGry &board, Ustawianie& screen) {
	screen.ZajetePola = 0;
	CzyMoznaLosowac = true;
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
		boat->CzyUstawiony = false;
	}
	for (auto& boat : statki3) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
	for (auto& boat : statki4) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
}

void ArmiaGracz::LosujPojedyncze(int n, ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 99);
	int wylosowane = dis(gen);
	
	if (CzyMoznaLosowac && !statki1[n]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek && !board.Pola[wylosowane]->wokolStatku) {
		statki1[n]->x = board.Pola[wylosowane]->x;
		statki1[n]->y = board.Pola[wylosowane]->y;
		statki1[n]->Iczesc = wylosowane;
		board.Pola[statki1[n]->Iczesc]->CzyStatek = true;
		statki1[n]->CzyUstawiony = true;
		statki1[n]->zaznaczwokol1(event, board);
		screen.ZajetePola++;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPojedyncze(n, event, board, screen);
}

void ArmiaGracz::LosujPodwojne(int n, ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 98);
	int wylosowane = dis(gen);

	if (CzyMoznaLosowac && (wylosowane + 1) % 10 != 0 && !statki2[n]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek 
		&& !board.Pola[wylosowane]->wokolStatku && !board.Pola[wylosowane+1]->CzyStatek && !board.Pola[wylosowane+1]->wokolStatku) {
		statki2[n]->x = board.Pola[wylosowane]->x;
		statki2[n]->y = board.Pola[wylosowane]->y;
		statki2[n]->Iczesc = wylosowane;
		statki2[n]->IIczesc = wylosowane + 1;
		board.Pola[statki2[n]->Iczesc]->CzyStatek = true;
		board.Pola[statki2[n]->IIczesc]->CzyStatek = true;
		statki2[n]->CzyUstawiony = true;
		statki2[n]->zaznaczwokol2(event, board);
		screen.ZajetePola += 2;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPodwojne(n, event, board, screen);
}

void ArmiaGracz::LosujPotrojne(int n, ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 97);
	int wylosowane = dis(gen);
	
	if (CzyMoznaLosowac && (wylosowane + 1) % 10 != 0 && (wylosowane + 2) % 10 != 0 && !statki3[n]->CzyUstawiony 
		&& !board.Pola[wylosowane]->CzyStatek && !board.Pola[wylosowane]->wokolStatku && !board.Pola[wylosowane + 1]->CzyStatek 
		&& !board.Pola[wylosowane + 1]->wokolStatku && !board.Pola[wylosowane + 2]->CzyStatek && !board.Pola[wylosowane + 2]->wokolStatku) {
		statki3[n]->x = board.Pola[wylosowane]->x;
		statki3[n]->y = board.Pola[wylosowane]->y;
		statki3[n]->Iczesc = wylosowane;
		statki3[n]->IIczesc = wylosowane + 1;
		statki3[n]->IIIczesc = wylosowane + 2;
		board.Pola[statki3[n]->Iczesc]->CzyStatek = true;
		board.Pola[statki3[n]->IIczesc]->CzyStatek = true;
		board.Pola[statki3[n]->IIIczesc]->CzyStatek = true;
		statki3[n]->CzyUstawiony = true;
		statki3[n]->zaznaczwokol3(event, board);
		screen.ZajetePola += 3;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPotrojne(n, event, board, screen);
}

void ArmiaGracz::LosujPoczworny(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 96);
	int wylosowane = dis(gen);

	if (CzyMoznaLosowac && (wylosowane + 1) % 10 != 0 && (wylosowane + 2) % 10 != 0 && (wylosowane + 3) % 10 != 0 
		&& !statki4[0]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek && !board.Pola[wylosowane]->wokolStatku 
		&& !board.Pola[wylosowane + 1]->CzyStatek && !board.Pola[wylosowane + 1]->wokolStatku && !board.Pola[wylosowane + 2]->CzyStatek 
		&& !board.Pola[wylosowane + 2]->wokolStatku && !board.Pola[wylosowane + 3]->CzyStatek && !board.Pola[wylosowane + 3]->wokolStatku) {

		statki4[0]->x = board.Pola[wylosowane]->x;
		statki4[0]->y = board.Pola[wylosowane]->y;
		statki4[0]->Iczesc = wylosowane;
		statki4[0]->IIczesc = wylosowane + 1;
		statki4[0]->IIIczesc = wylosowane + 2;
		statki4[0]->IVczesc = wylosowane + 3;
		board.Pola[statki4[0]->Iczesc]->CzyStatek = true;
		board.Pola[statki4[0]->IIczesc]->CzyStatek = true;
		board.Pola[statki4[0]->IIIczesc]->CzyStatek = true;
		board.Pola[statki4[0]->IVczesc]->CzyStatek = true;
		statki4[0]->CzyUstawiony = true;
		statki4[0]->zaznaczwokol4(event, board);
		screen.ZajetePola += 4;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPoczworny(event, board, screen);
}

void ArmiaGracz::LosujPlansze(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {


	LosujPoczworny(event, board, screen);
	for (int i = 0; i < 2; i++) {    //Losowanie potrojnych statkow
		LosujPotrojne(i, event, board, screen);
	}
	for (int i = 0; i < 3; i++) {    //Losowanie podwojnych statkow
		LosujPodwojne(i, event, board, screen);
	}
	for (int i = 0; i < 4; i++) {    //Losowanie pojedynczych statkow
		LosujPojedyncze(i, event, board, screen);
	}

	for (int i = 1; i <= 100; i++) {
		std::cout << board.Pola[i - 1]->wokolStatku<<" ";
		if (i % 10 == 0)
			std::cout << "\n";
	}
	std::cout << "-------------------------------\n";
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

	CzyMoznaLosowac = false;
}

void PlanszaPrzeciwnik::init() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->PolaPrzeciwnik.push_back(new Pole(tile, hit, miss, (i * 40) + 727, (j * 40) + 94, false, false, false));
		}
	}
	PolaPrzeciwnik[0]->CzyStatek = true;          //podwojny
	PolaPrzeciwnik[1]->CzyStatek = true;

	PolaPrzeciwnik[3]->CzyStatek = true;          //podwojny
	PolaPrzeciwnik[4]->CzyStatek = true;

	PolaPrzeciwnik[6]->CzyStatek = true;          //podwojny
	PolaPrzeciwnik[7]->CzyStatek = true;

	PolaPrzeciwnik[9]->CzyStatek = true;
	PolaPrzeciwnik[20]->CzyStatek = true;         //pojedyncze
	PolaPrzeciwnik[22]->CzyStatek = true;
	PolaPrzeciwnik[24]->CzyStatek = true;

	PolaPrzeciwnik[26]->CzyStatek = true;           //potrojny
	PolaPrzeciwnik[27]->CzyStatek = true;
	PolaPrzeciwnik[28]->CzyStatek = true;

	PolaPrzeciwnik[40]->CzyStatek = true;          //potrojny
	PolaPrzeciwnik[41]->CzyStatek = true;
	PolaPrzeciwnik[42]->CzyStatek = true;

	PolaPrzeciwnik[44]->CzyStatek = true;
	PolaPrzeciwnik[45]->CzyStatek = true;          //poczworny
	PolaPrzeciwnik[46]->CzyStatek = true;
	PolaPrzeciwnik[47]->CzyStatek = true;
}

void PlanszaPrzeciwnik::destroy() {
	for (auto tile = PolaPrzeciwnik.begin(); tile != PolaPrzeciwnik.end(); tile++) {
		delete* tile;
	}
	PolaPrzeciwnik.clear();
}

void PlanszaPrzeciwnik::drawplanszaprzeciwnika() {
	for (auto& tile : PolaPrzeciwnik) {
		if (tile->czyTrafione && tile->CzyStatek)
			tile->pole = tile->hit;
		else if (tile->czyTrafione && !tile->CzyStatek)
			tile->pole = tile->miss;
		al_draw_bitmap(tile->pole, tile->x, tile->y, 0);
	}
}

void GamePlay::init(Ustawianie& ustawianie, char exitscreen[], char win[], char lose[], char wrongchoice[], char outofboard[]) {
	this->SrodPanel = ustawianie.SrodPanel;
	this->Litery = ustawianie.Litery;
	this->Cyfry = ustawianie.Cyfry;
	this->Exit = ustawianie.Exit;
	this->ExitScreen = al_load_bitmap(exitscreen);
	this->Win = al_load_bitmap(win);
	this->Lose = al_load_bitmap(lose);
	this->WrongChoice = al_load_bitmap(wrongchoice);
	this->OutOfBoard = al_load_bitmap(outofboard);
	this->TuraGracza = true;
	this->CzyWin = false;
	this->CzyLose = false;
}

void GamePlay::drawgameplay(PlanszaPrzeciwnik& enemyboard) {
	this->CzyGameplay = true;
	al_draw_bitmap(SrodPanel, 500, 0, 0);
	al_draw_bitmap(Litery, 76, 44, 0);
	al_draw_bitmap(Cyfry, 24, 94, 0);
	al_draw_bitmap(Exit, 514, 461, 0);
	enemyboard.drawplanszaprzeciwnika();
	al_draw_bitmap(Litery, 727, 44, 0);
	al_draw_bitmap(Cyfry, 1127, 94, 0);
}

void GamePlay::WyborPolaPrzezGracza(ALLEGRO_EVENT event, PlanszaGry& board, PlanszaPrzeciwnik& enemyboard) {
	if (event.mouse.x >= 727 && event.mouse.x <= 1127 && event.mouse.y >= 94 && event.mouse.y <= 494) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1) {
			for (int i = 0; i < 100; i++) {
				if (event.mouse.x > enemyboard.PolaPrzeciwnik[i]->x && event.mouse.x < enemyboard.PolaPrzeciwnik[i]->x + 40
					&& event.mouse.y > enemyboard.PolaPrzeciwnik[i]->y && event.mouse.y < enemyboard.PolaPrzeciwnik[i]->y + 40) {
					if (!enemyboard.PolaPrzeciwnik[i]->czyTrafione) {
						if(enemyboard.PolaPrzeciwnik[i]->CzyStatek)
							TrafionePlanszaAI++;
						else
							TuraGracza = false;
						enemyboard.PolaPrzeciwnik[i]->czyTrafione = true;
					}
					else {
						al_draw_bitmap(this->WrongChoice, 500, 54, 0);
					}
				}
			}
		}
	}
	else {
		al_draw_bitmap(OutOfBoard, 500, 54, 0);
	}
}

void GamePlay::GetRandomPole(PlanszaGry& board, PlanszaPrzeciwnik& enemyboard) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 99);

	int WylosowanePole = dis(gen);

	if (!board.Pola[WylosowanePole]->czyTrafione) {
		if (board.Pola[WylosowanePole]->CzyStatek) {
			TrafionePlanszaGracz++;
		}
		else
			TuraGracza = true;
		board.Pola[WylosowanePole]->czyTrafione = true;
	}
	else {
		GetRandomPole(board, enemyboard);
	}
}

void GamePlay::Rozgrywka(ALLEGRO_EVENT event, PlanszaGry& board, PlanszaPrzeciwnik& enemyboard, Ustawianie& screen) {

	if (TuraGracza) {
		WyborPolaPrzezGracza(event, board, enemyboard);
	}

	if (!TuraGracza) {
		GetRandomPole(board, enemyboard);	
	}

	enemyboard.drawplanszaprzeciwnika();
}

void GamePlay::destroy() {
	this->CzyGameplay = false;
	al_destroy_bitmap(SrodPanel);
	al_destroy_bitmap(Litery);
	al_destroy_bitmap(Cyfry);
	al_destroy_bitmap(Exit);
}
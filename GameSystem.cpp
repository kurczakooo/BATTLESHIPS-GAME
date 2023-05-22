/**
* @file GameSystem.cpp
* 
* @brief Plik definiujacy metody klas z GameSystem.h
*/


#include "GameSystem.h"

char tile[] = "elements/pole.png";
char hit[] = "elements/hit.png";
char miss[] = "elements/miss.png";
char statek1[] = "elements/1statek.png";
char statek2[] = "elements/2statek.png";
char statek2r[] = "elements/2statek_rotated.png";
char statek3[] = "elements/3statek.png";
char statek4[] = "elements/4statek.png";
char dzwiek1[] = "sounds/setship1.wav";

/**
 * @brief Inicjalizuje klase GameSystem
 * @param dzwiek Ścieżka do pliku dźwiękowego
 */
void GameSystem::init(char dzwiek[]) {
	al_init();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);

	this->display = al_create_display(DisplayWidth, DisplayHeight);
	al_set_window_title(display, DisplayTitle);
	this->queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	this->running = true;
	this->dzwiek = al_load_sample(dzwiek);
}

/**
 * @brief Niszczy zasoby klasy GameSystem
 */
void GameSystem::destroy() {
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_uninstall_mouse();
	al_uninstall_audio();
}

/**
 * @brief Inicjalizuje menu.
 * @param Tytul Ścieżka do pliku bitmapy z tytułem.
 * @param Tlo Ścieżka do pliku bitmapy z tłem.
 * @param Graj Ścieżka do pliku bitmapy przycisku "Graj".
 * @param Exit Ścieżka do pliku bitmapy przycisku "Wyjście".
 * @param Jakgrac Ścieżka do pliku bitmapy przycisku "Jak grać".
 * @param Instrukcje Ścieżka do pliku bitmapy z instrukcjami.
 */
void Menu::init(char Tytul[], char Tlo[], char Graj[], char Exit[], char Jakgrac[], char Instrukcje[]) {
	this->tytul = al_load_bitmap(Tytul);
	this->tlo = al_load_bitmap(Tlo);
	this->graj = al_load_bitmap(Graj);
	this->exit = al_load_bitmap(Exit);
	this->jakgrac = al_load_bitmap(Jakgrac);
	this->instrukcje = al_load_bitmap(Instrukcje);
	this->CzyInstrukcje = false;
	this->Gwidth = al_get_bitmap_width(graj);
	this->Gheight = al_get_bitmap_height(graj);
	this->Ewidth = al_get_bitmap_width(exit);
}

/**
 * @brief Wyświetla menu.
 */
void Menu::drawMenu() {
	this->CzyMenu = true;
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap(tlo, 0, 0, 0);
	al_draw_bitmap(tytul, 0, 0, 0);
	al_draw_bitmap(graj, DisplayWidth / 2 - Gwidth / 2, DisplayHeight / 2 - Gheight / 2, 0);
	al_draw_bitmap(exit, DisplayWidth / 2 - Ewidth / 2, 410, 0);
	al_draw_bitmap(jakgrac, 1117, 0, 0);
}

/**
 * @brief Niszczy zasoby menu.
 */
void Menu::destroy() {
	this->CzyMenu = false;
	al_destroy_bitmap(tytul); 
	al_destroy_bitmap(graj); 
	al_destroy_bitmap(exit); 
	al_destroy_bitmap(jakgrac);
	al_destroy_bitmap(instrukcje); 
	al_destroy_bitmap(tlo); 
}

/**
 * @brief Konstruktor klasy Pole.
 * @param Pole Ścieżka do pliku bitmapy reprezentującej pole.
 * @param Hit Ścieżka do pliku bitmapy reprezentującej trafienie.
 * @param Miss Ścieżka do pliku bitmapy reprezentującej chybienie.
 * @param x Współrzędna x pola.
 * @param y Współrzędna y pola.
 * @param statek Informacja czy na polu znajduje się statek.
 * @param trafione Informacja czy pole zostało trafione.
 * @param wokol Informacja czy wokół pola znajduje się statek.
 */
Pole::Pole(char Pole[], char Hit[], char Miss[], int x, int y, bool statek, bool trafione, bool wokol) {
	this->pole = al_load_bitmap(Pole);
	this->hit = al_load_bitmap(Hit);
	this->miss = al_load_bitmap(Miss);
	this->x = x;
	this->y = y;
	this->CzyStatek = statek;
	this->czyTrafione = trafione;
	this->wokolStatku = wokol;
}

/**
 * @brief Inicjalizuje planszę gry.
 */
void PlanszaGry::init() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			/**
			 * Tworzy obiekt klasy Pole i dodaje go do wektora Pola na planszy.
			 * Ustawia współrzędne x i y pola na podstawie wartości i i j.
			 * Ustawia początkowe wartości pól logicznych (statek, trafione, wokol).
			 */
			this->Pola.push_back(new Pole(tile, hit, miss, (i * 40) + 75, (j * 40) + 94, false, false, false));
		}
	}
	this->click = al_load_sample(dzwiek1); /**< Wczytuje próbkę dźwiękową z pliku. */
}

/**
 * @brief Niszczy planszę gry.
 */
void PlanszaGry::destroy() {
	for (auto tile = Pola.begin(); tile != Pola.end(); tile++) {
		delete* tile;
	}
	Pola.clear();
}

/**
 * @brief Rysuje planszę gry.
 */
void PlanszaGry::drawplansza() {
	for (auto& tile : Pola) {
		if (tile->czyTrafione && tile->CzyStatek) 
			tile->pole = tile->hit; 
		else if (tile->czyTrafione && !tile->CzyStatek) 
			tile->pole = tile->miss;
		al_draw_bitmap(tile->pole, tile->x, tile->y, 0);
	}
}

/**
 * @brief Inicjalizuje ekran ustawiania statków.
 * @param Napis Ścieżka do pliku bitmapy reprezentującej napis.
 * @param Panel Ścieżka do pliku bitmapy reprezentującej panel.
 * @param litery Ścieżka do pliku bitmapy reprezentującej litery.
 * @param cyfry Ścieżka do pliku bitmapy reprezentującej cyfry.
 * @param reset Ścieżka do pliku bitmapy reprezentującej reset.
 * @param exit Ścieżka do pliku bitmapy reprezentującej wyjście.
 * @param graj Ścieżka do pliku bitmapy reprezentującej przycisk "Graj".
 * @param losujustawianie Ścieżka do pliku bitmapy reprezentującej przycisk "Losuj ustawienie".
 * @param losujwarning Ścieżka do pliku bitmapy reprezentującej ostrzeżenie przy losowaniu.
 * @param grajsound Ścieżka do pliku dźwiękowego reprezentującego dźwięk przycisku "Graj".
 */
void Ustawianie::init(char Napis[], char Panel[], char litery[], char cyfry[], char reset[], char exit[], char graj[], char losujustawianie[], char losujwarning[], char grajsound[]) {
	this->NapisObracanie = al_load_bitmap(Napis);
	this->SrodPanel = al_load_bitmap(Panel);
	this->Litery = al_load_bitmap(litery);
	this->Cyfry = al_load_bitmap(cyfry);
	this->Reset = al_load_bitmap(reset);
	this->Exit = al_load_bitmap(exit);
	this->Graj = al_load_bitmap(graj);
	this->Losuj = al_load_bitmap(losujustawianie);
	this->LosujWarning = al_load_bitmap(losujwarning);
	this->GrajSound = al_load_sample(grajsound);
}

/**
 * @brief Rysuje ekran ustawiania statków.
 * @param board Referencja do obiektu PlanszaGry.
 */
void Ustawianie::DrawUstawianie(PlanszaGry& board) {
	this->CzyUstawianie = true; 
	al_draw_bitmap(NapisObracanie, 700, 0, 0);
	al_draw_bitmap(SrodPanel, 500, 0, 0);
	al_draw_bitmap(Litery, 76, 44, 0);
	al_draw_bitmap(Cyfry, 24, 94, 0); 
	al_draw_bitmap(Reset, 617, 461, 0);
	al_draw_bitmap(Exit, 514, 461, 0);
	al_draw_bitmap(Losuj, 508, 390, 0); 

	if (ZajetePola == 20) /**< Jeśli wszystkie pola zostały zajęte. */
		al_draw_bitmap(Graj, 508, 235, 0); /**< Rysuje bitmapę przycisku "Graj" na określonej pozycji. */
}

/**
 * @brief Niszczy zasoby związane z klasą Ustawianie.
 */
void Ustawianie::destroy() {
	this->CzyUstawianie = false;
	al_destroy_bitmap(NapisObracanie);
	al_destroy_bitmap(SrodPanel);
	al_destroy_bitmap(Litery);
	al_destroy_bitmap(Cyfry);
	al_destroy_bitmap(Reset);
	al_destroy_bitmap(Exit);
	al_destroy_bitmap(Graj);
}

/**
 * @brief Inicjalizuje planszę przeciwnika.
 */
void PlanszaGry::initprzeciwnik() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->Pola.push_back(new Pole(tile, hit, miss, (i * 40) + 727, (j * 40) + 94, false, false, false));
		}
	}
}
/**
*@brief Niszczy planszę przeciwnika.
*/
void PlanszaGry::destroyprzeciwnik() {
	for (auto tile = Pola.begin(); tile != Pola.end(); tile++) {
		delete* tile;
	}
	Pola.clear();
}

/**
 * @brief Rysuje planszę przeciwnika.
 */
void PlanszaGry::drawplanszaprzeciwnika() {
	for (auto& tile : Pola) {
		if (tile->czyTrafione && tile->CzyStatek)
			tile->pole = tile->hit;
		else if (tile->czyTrafione && !tile->CzyStatek)
			tile->pole = tile->miss;
		al_draw_bitmap(tile->pole, tile->x, tile->y, 0);
	}
}

/**
 * @brief Konstruktor klasy Statek1.
 * @param statek1 Ścieżka do bitmapy reprezentującej statek.
 * @param x Współrzędna x, na której statek ma być umieszczony.
 * @param y Współrzędna y, na której statek ma być umieszczony.
 * @param defaultx Wartość domyślna współrzędnej x.
 * @param defaulty Wartość domyślna współrzędnej y.
 */
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

/**
 * @brief Zaznacza pola wokół statku.
 * @param board Referencja do obiektu PlanszaGry, na którym znajdują się pola.
 */
void Statek1::zaznaczwokol1(PlanszaGry& board) {
	if ((Iczesc + 1) % 10 != 0 && Iczesc != 99) {
		board.Pola[Iczesc + 1]->wokolStatku = true;     ///< Dol statku
		PolaWokolStatku1.push_back(Iczesc + 1);
	}
	if (Iczesc % 10 != 0 && Iczesc != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     ///< Góra statku
		PolaWokolStatku1.push_back(Iczesc - 1);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    ///< Lewo statku
		PolaWokolStatku1.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) <= 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    ///< Prawo statku
		PolaWokolStatku1.push_back(Iczesc + 10);
	}
	if ((Iczesc - 9) >= 0 && (Iczesc - 9) % 10 != 0) {
		board.Pola[Iczesc - 9]->wokolStatku = true;    ///< Lewo dol statku
		PolaWokolStatku1.push_back(Iczesc - 9);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    ///< Lewo gora statku
		PolaWokolStatku1.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    ///< Prawo gora statku
		PolaWokolStatku1.push_back(Iczesc + 9);
	}
	if ((Iczesc + 11) <= 99 && (Iczesc + 11) % 10 != 0) {
		board.Pola[Iczesc + 11]->wokolStatku = true;    ///< Prawo dol statku
		PolaWokolStatku1.push_back(Iczesc + 11);
	}
}

/**
 * @brief Metoda rysująca jednomasztowy statek.
 *
 * @param event Zdarzenie myszy.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
void Statek1::drawstatek1(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	// Sprawdzenie, czy kursor myszy znajduje się nad statkiem
	if (event.mouse.x >= x && event.mouse.x <= x + 40 && event.mouse.y >= y && event.mouse.y <= y + 40) {
		// Obsługa kliknięcia lewym przyciskiem myszy
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = false;
			// Sprawdzenie, czy statek może zostać umieszczony na danym polu
			for (int i = 0; i < 100; i++) {
				if (x + 20 >= board.Pola[i]->x && x + 20 <= board.Pola[i]->x + 40 && y + 20 >= board.Pola[i]->y && y + 20 <= board.Pola[i]->y + 40) {
					if (!board.Pola[i]->CzyStatek && !board.Pola[i]->wokolStatku) {
						x = board.Pola[i]->x;
						y = board.Pola[i]->y;
						Iczesc = i;
						board.Pola[Iczesc]->CzyStatek = true;
						screen.ZajetePola++;
						zaznaczwokol1(board);
						CzyUstawiony = true;
						al_play_sample(board.click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
			// Sprawdzenie, czy statek wykracza poza planszę
			if (x + 20 >= 475 || x + 20 <= 75 || y + 20 >= 494 || y + 20 <= 94) {
				x = defaultX;
				y = defaultY;
				degree = 0;
			}
		}
		// Obsługa kliknięcia prawym przyciskiem myszy
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 2 && !CzyUstawiony) {
			degree += 90;
			if (degree > 90)
				degree = 0;
		}
		// Obsługa wciśnięcia lewego przycisku myszy
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1 && !CzyUstawiony) {
			isDragged = true;
		}
	}
	// Obsługa ruchu myszy
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES && isDragged) {
		x = event.mouse.x - al_get_bitmap_width(ship1) / 2;
		y = event.mouse.y - al_get_bitmap_height(ship1) / 2;
	}
	// Rysowanie statku
	al_draw_rotated_bitmap(ship1, al_get_bitmap_width(ship1) / 2, al_get_bitmap_height(ship1) / 2, x + al_get_bitmap_width(ship1) / 2, y + al_get_bitmap_height(ship1) / 2, degree * 3.14159 / 180, 0);
}

/**
 * @brief Konstruktor klasy Statek2.
 *
 * @param statek2 Ścieżka do pliku z obrazem statku w domyślnej pozycji.
 * @param statek2r Ścieżka do pliku z obrazem statku obróconego.
 * @param x Współrzędna x statku.
 * @param y Współrzędna y statku.
 * @param defaultx Domyślna współrzędna x statku.
 * @param defaulty Domyślna współrzędna y statku.
 */
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

/**
 * @brief Zaznacza pola wokół statku na planszy.
 *
 * @param board Referencja do obiektu PlanszaGry.
 */
void Statek2::zaznaczwokol2(PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     ///< Pole powyżej statku
		PolaWokolStatku2.push_back(Iczesc - 1);
	}
	if ((IIczesc + 1) % 10 != 0 && IIczesc != 99) {
		board.Pola[IIczesc + 1]->wokolStatku = true;     ///< Pole poniżej statku
		PolaWokolStatku2.push_back(IIczesc + 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    ///< Pole po lewej górze statku
		PolaWokolStatku2.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    ///< Pole po prawej górze statku
		PolaWokolStatku2.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    ///< Pole na lewo od pierwszej części statku
		PolaWokolStatku2.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    ///< Pole na prawo od pierwszej części statku
		PolaWokolStatku2.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    ///< Pole na lewo od drugiej części statku
		PolaWokolStatku2.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    ///< Pole na prawo od drugiej części statku
		PolaWokolStatku2.push_back(IIczesc + 10);
	}
	if ((IIczesc - 9) >= 0 && (IIczesc - 9) % 10 != 0) {
		board.Pola[IIczesc - 9]->wokolStatku = true;    ///< Pole na lewo od dolnej części statku
		PolaWokolStatku2.push_back(IIczesc - 9);
	}
	if ((IIczesc + 11) <= 99 && (IIczesc + 11) % 10 != 0) {
		board.Pola[IIczesc + 11]->wokolStatku = true;    ///< Pole na prawo od dolnej części statku
		PolaWokolStatku2.push_back(IIczesc + 11);
	}
}

/**
 * @brief Rysuje statek na planszy i obsługuje zdarzenia związane z jego przesuwaniem i ustawianiem.
 *
 * @param event Zdarzenie ALLEGRO_EVENT.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
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
						zaznaczwokol2(board);
						CzyUstawiony = true;
						al_play_sample(board.click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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

/**
 * @brief Rysuje statek na planszy i obsługuje zdarzenia związane z jego przesuwaniem i ustawianiem.
 *
 * @param event Zdarzenie ALLEGRO_EVENT.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
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

/**
 * @brief Zaznacza pola wokół statku trójczęściowego na planszy.
 *
 * @param board Referencja do obiektu PlanszaGry.
 */
void Statek3::zaznaczwokol3(PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     ///< Góra statku
		PolaWokolStatku3.push_back(Iczesc - 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    ///< Lewo góra statku
		PolaWokolStatku3.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    ///< Prawo góra statku
		PolaWokolStatku3.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    ///< Lewo I części
		PolaWokolStatku3.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    ///< Prawo I części
		PolaWokolStatku3.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    ///< Lewo II części
		PolaWokolStatku3.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    ///< Prawo II części
		PolaWokolStatku3.push_back(IIczesc + 10);
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    ///< Lewo III części
		PolaWokolStatku3.push_back(IIIczesc - 10);
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    ///< Prawo III części
		PolaWokolStatku3.push_back(IIIczesc + 10);
	}
	if ((IIIczesc + 1) % 10 != 0 && IIIczesc != 99) {
		board.Pola[IIIczesc + 1]->wokolStatku = true;      ///< Dół statku
		PolaWokolStatku3.push_back(IIIczesc + 1);
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    ///< Lewo dół statku
		PolaWokolStatku3.push_back(IIIczesc - 9);
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    ///< Prawo dół statku
		PolaWokolStatku3.push_back(IIIczesc + 11);
	}
}


/**
 * @brief Rysuje statek na planszy i obsługuje zdarzenia związane z jego przesuwaniem i ustawianiem.
 *
 * @param event Zdarzenie ALLEGRO_EVENT.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
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
						zaznaczwokol3(board);
						CzyUstawiony = true;
						al_play_sample(board.click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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

/**
 * @brief Rysuje statek na planszy i obsługuje zdarzenia związane z jego przesuwaniem i ustawianiem.
 *
 * @param event Zdarzenie ALLEGRO_EVENT.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
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

/**
 * @brief Zaznacza pola wokół statku czteroczęściowego na planszy.
 *
 * @param board Referencja do obiektu PlanszaGry.
 */
void Statek4::zaznaczwokol4(PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     ///< Góra statku
		PolaWokolStatku4.push_back(Iczesc - 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    ///< Lewo góra statku
		PolaWokolStatku4.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    ///< Prawo góra statku
		PolaWokolStatku4.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    ///< Lewo I części
		PolaWokolStatku4.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    ///< Prawo I części
		PolaWokolStatku4.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    ///< Lewo II części
		PolaWokolStatku4.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    ///< Prawo II części
		PolaWokolStatku4.push_back(IIczesc + 10);
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    ///< Lewo III części
		PolaWokolStatku4.push_back(IIIczesc - 10);
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    ///< Prawo III części
		PolaWokolStatku4.push_back(IIIczesc + 10);
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    ///< Lewo IV części
		PolaWokolStatku4.push_back(IIIczesc - 9);
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    ///< Prawo IV części
		PolaWokolStatku4.push_back(IIIczesc + 11);
	}
	if ((IVczesc + 1) % 10 != 0 && IVczesc != 99) {
		board.Pola[IVczesc + 1]->wokolStatku = true;      ///< Dół statku
		PolaWokolStatku4.push_back(IVczesc + 1);
	}
	if ((IVczesc - 9) >= 0 && (IVczesc - 9) % 10 != 0) {
		board.Pola[IVczesc - 9]->wokolStatku = true;    ///< Lewo dół statku
		PolaWokolStatku4.push_back(IVczesc - 9);
	}
	if ((IVczesc + 11) <= 99 && (IVczesc + 11) % 10 != 0) {
		board.Pola[IVczesc + 11]->wokolStatku = true;    ///< Prawo dół statku
		PolaWokolStatku4.push_back(IVczesc + 11);
	}
}

/**
 * @brief Rysuje statek czteroczęściowy i obsługuje zdarzenia myszy związane z przeciąganiem statku oraz umieszczaniem go na planszy.
 *
 * @param event Obiekt zdarzenia ALLEGRO_EVENT.
 * @param board Referencja do obiektu PlanszaGry.
 * @param screen Referencja do obiektu Ustawianie.
 */
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
						zaznaczwokol4(board);
						CzyUstawiony = true;
						al_play_sample(board.click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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

/**
 * @brief Inicjalizuje statki gracza i dodaje je do odpowiednich list.
 */
void ArmiaGracz::init() {
	// Inicjalizacja statków jednoczęściowych (statki1)
	this->statki1.push_back(new Statek1(statek1, 728.0, 94.0, 728, 94));
	this->statki1.push_back(new Statek1(statek1, 808.0, 94.0, 808, 94));
	this->statki1.push_back(new Statek1(statek1, 888.0, 94.0, 888, 94));
	this->statki1.push_back(new Statek1(statek1, 968.0, 94.0, 968, 94));

	// Inicjalizacja statków dwuczęściowych (statki2)
	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 174.0, 728, 174));
	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 294.0, 728, 294));
	this->statki2.push_back(new Statek2(statek2, statek2r, 728.0, 414.0, 728, 414));

	// Inicjalizacja statków trzyczęściowych (statki3)
	this->statki3.push_back(new Statek3(statek3, 848.0, 174.0, 848, 174));
	this->statki3.push_back(new Statek3(statek3, 848.0, 334.0, 848, 334));

	// Inicjalizacja statku czteroczęściowego (statki4)
	this->statki4.push_back(new Statek4(statek4, 1008.0, 214.0, 1008, 214));

	CzyMoznaLosowac = true;
}

/**
 * @brief Rysuje statki armii gracza na planszy.
 *
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
void ArmiaGracz::drawarmia(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	// Rysowanie statków jednoczęściowych (statki1)
	for (auto& boat : statki1) {
		boat->drawstatek1(event, board, screen);
	}
	// Rysowanie statków dwuczęściowych (statki2)
	for (auto& boat : statki2) {
		boat->drawstatek2(event, board, screen);
	}
	// Rysowanie statków trzyczęściowych (statki3)
	for (auto& boat : statki3) {
		boat->drawstatek3(event, board, screen);
	}
	// Rysowanie statku czteroczęściowego (statki4)
	for (auto& boat : statki4) {
		boat->drawstatek4(event, board, screen);
	}
}
 
/**
 * @brief Przywraca początkowy stan armii gracza.
 *
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
void ArmiaGracz::restart(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	// Resetowanie zmiennych
	screen.ZajetePola = 0;
	CzyMoznaLosowac = true;
	// Resetowanie pól planszy
	for (auto& tile1 : board.Pola) {
		tile1->CzyStatek = false;
		tile1->wokolStatku = false;
	}
	// Resetowanie statków jednoczęściowych (statki1)
	for (auto& boat : statki1) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
	// Resetowanie statków dwuczęściowych (statki2)
	for (auto& boat : statki2) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
	// Resetowanie statków trzyczęściowych (statki3)
	for (auto& boat : statki3) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
	// Resetowanie statku czteroczęściowego (statki4)
	for (auto& boat : statki4) {
		boat->x = boat->defaultX;
		boat->y = boat->defaultY;
		boat->degree = 0;
		boat->isDragged = false;
		boat->CzyUstawiony = false;
	}
}

/**
 * @brief Losuje i ustawia pojedynczy statek na planszy.
 *
 * @param n         Indeks statku w liście statki1.
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
void ArmiaGracz::LosujPojedyncze(int n, ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 99);
	int wylosowane = dis(gen);

	// Sprawdzenie warunków losowania i ustawienie statku
	if (CzyMoznaLosowac && !statki1[n]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek && !board.Pola[wylosowane]->wokolStatku) {
		statki1[n]->x = board.Pola[wylosowane]->x;
		statki1[n]->y = board.Pola[wylosowane]->y;
		statki1[n]->Iczesc = wylosowane;
		board.Pola[statki1[n]->Iczesc]->CzyStatek = true;
		statki1[n]->CzyUstawiony = true;
		statki1[n]->zaznaczwokol1(board);
		screen.ZajetePola++;
	}
	// Wyświetlenie ostrzeżenia w przypadku niedozwolonego losowania
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	// Powtórzenie losowania w przypadku niepoprawnych warunków
	else
		LosujPojedyncze(n, event, board, screen);
}

/**
 * @brief Losuje i ustawia podwojny statek na planszy.
 *
 * @param n         Indeks statku w liście statki1.
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
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
		statki2[n]->zaznaczwokol2(board);
		screen.ZajetePola += 2;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPodwojne(n, event, board, screen);
}

/**
 * @brief Losuje i ustawia potrojny statek na planszy.
 *
 * @param n         Indeks statku w liście statki1.
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
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
		statki3[n]->zaznaczwokol3(board);
		screen.ZajetePola += 3;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPotrojne(n, event, board, screen);
}

/**
 * @brief Losuje i ustawia poczworny statek na planszy.
 *
 * @param n         Indeks statku w liście statki1.
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
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
		statki4[0]->zaznaczwokol4(board);
		screen.ZajetePola += 4;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPoczworny(event, board, screen);
}

/**
 * @brief Losuje i ustawia statki na planszy.
 *
 * @param event     Zdarzenie ALLEGRO.
 * @param board     Referencja do obiektu PlanszaGry.
 * @param screen    Referencja do obiektu Ustawianie.
 */
void ArmiaGracz::LosujPlansze(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {
	// Sprawdzenie, czy na planszy znajdują się już statki
	for (auto tile : board.Pola) {
		if (tile->CzyStatek)
			CzyMoznaLosowac = false;
	}
	// Losowanie poczwornego statku
	LosujPoczworny(event, board, screen);
	// Losowanie potrójnych statków
	for (int i = 0; i < 2; i++) {
		LosujPotrojne(i, event, board, screen);
	}
	// Losowanie podwójnych statków
	for (int i = 0; i < 3; i++) {
		LosujPodwojne(i, event, board, screen);
	}
	// Losowanie pojedynczych statków
	for (int i = 0; i < 4; i++) {
		LosujPojedyncze(i, event, board, screen);
	}
}

/**
 * @brief Zwalnianie zasobów floty gracza.
 * Usuwa wszystkie statki i czyści kontenery statków.
 */
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

/**
 * @brief Implementacja klasy ArmiaPrzeciwnik.
 */

void ArmiaPrzeciwnik::init() {
	 // Inicjalizacja statków typu Statek1
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));

	// Inicjalizacja statków typu Statek2
	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));
	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));
	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));

	// Inicjalizacja statków typu Statek3
	this->statki3.push_back(new Statek3(statek3, 0, 0, 0, 0));
	this->statki3.push_back(new Statek3(statek3, 0, 0, 0, 0));

	// Inicjalizacja statków typu Statek4
	this->statki4.push_back(new Statek4(statek4, 0, 0, 0, 0));
}

/**
 * @brief Losuje i ustawia pojedynczy statek przeciwnika na planszy.
 * Losuje losową pozycję na planszy i ustawia pojedynczy statek typu Statek1 w podanym indeksie n.
 * @param n Indeks statku w kontenerze statków typu Statek1.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gry.
 */
void ArmiaPrzeciwnik::LosujPojedyncze(int n, PlanszaGry& board) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 99);
	int wylosowane = dis(gen);

	if (!statki1[n]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek && !board.Pola[wylosowane]->wokolStatku) {
		statki1[n]->x = board.Pola[wylosowane]->x;
		statki1[n]->y = board.Pola[wylosowane]->y;
		statki1[n]->Iczesc = wylosowane;
		board.Pola[statki1[n]->Iczesc]->CzyStatek = true;
		statki1[n]->CzyUstawiony = true;
		statki1[n]->zaznaczwokol1(board);
	}
	else LosujPojedyncze(n, board);
}

/**
 * @brief Losuje i ustawia podwójny statek przeciwnika na planszy.
 * Losuje losową pozycję na planszy i ustawia podwójny statek typu Statek2 w podanym indeksie n.
 * @param n Indeks statku w kontenerze statków typu Statek2.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gry.
 */
void ArmiaPrzeciwnik::LosujPodwojne(int n, PlanszaGry& board) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 98);
	int wylosowane = dis(gen);

	if ((wylosowane + 1) % 10 != 0 && !statki2[n]->CzyUstawiony && !board.Pola[wylosowane]->CzyStatek
		&& !board.Pola[wylosowane]->wokolStatku && !board.Pola[wylosowane + 1]->CzyStatek && !board.Pola[wylosowane + 1]->wokolStatku) {
		statki2[n]->x = board.Pola[wylosowane]->x;
		statki2[n]->y = board.Pola[wylosowane]->y;
		statki2[n]->Iczesc = wylosowane;
		statki2[n]->IIczesc = wylosowane + 1;
		board.Pola[statki2[n]->Iczesc]->CzyStatek = true;
		board.Pola[statki2[n]->IIczesc]->CzyStatek = true;
		statki2[n]->CzyUstawiony = true;
		statki2[n]->zaznaczwokol2(board);
	}
	else LosujPodwojne(n, board);
}

/**
 * @brief Losuje i ustawia potrojny statek przeciwnika na planszy.
 * Losuje losową pozycję na planszy i ustawia podwójny statek typu Statek3 w podanym indeksie n.
 * @param n Indeks statku w kontenerze statków typu Statek3.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gry.
 */
void ArmiaPrzeciwnik::LosujPotrojne(int n, PlanszaGry& board) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 97);
	int wylosowane = dis(gen);

	if ((wylosowane + 1) % 10 != 0 && (wylosowane + 2) % 10 != 0 && !statki3[n]->CzyUstawiony
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
		statki3[n]->zaznaczwokol3(board);
	}
	else LosujPotrojne(n, board);
}

/**
 * @brief Losuje i ustawia podwójny statek przeciwnika na planszy.
 * Losuje losową pozycję na planszy i ustawia podwójny statek typu Statek4 w podanym indeksie n.
 * @param n Indeks statku w kontenerze statków typu Statek4.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gry.
 */
void ArmiaPrzeciwnik::LosujPoczworny(PlanszaGry& board) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 96);
	int wylosowane = dis(gen);

	if ((wylosowane + 1) % 10 != 0 && (wylosowane + 2) % 10 != 0 && (wylosowane + 3) % 10 != 0
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
		statki4[0]->zaznaczwokol4(board);
	}
	else LosujPoczworny(board);
}

/**
 * @brief Losuje ustawienie statków przeciwnika na planszy.
 * Losuje ustawienie poczwornego, potrójnego, podwójnego i pojedynczego statku przeciwnika na podanej planszy.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gry.
 */
void ArmiaPrzeciwnik::LosujPlansze(PlanszaGry& board) {
	
	LosujPoczworny(board);           //Losowanie poczwornego statku
	for (int i = 0; i < 2; i++) {    //Losowanie potrojnych statkow
		LosujPotrojne(i, board);
	}
	for (int i = 0; i < 3; i++) {    //Losowanie podwojnych statkow
		LosujPodwojne(i, board);
	}
	for (int i = 0; i < 4; i++) {    //Losowanie pojedynczych statkow
		LosujPojedyncze(i, board);
	}
}

/**
 * @brief Zwalnia zasoby floty przeciwnika.
 * Usuwa wszystkie obiekty statków i czyści kontenery statków.
 */
void ArmiaPrzeciwnik::destroy() {
	for (auto boat = statki1.begin(); boat != statki1.end(); boat++) {
		delete* boat;
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

/**
 * @brief Inicjalizuje obiekt gry.
 * Inicjalizuje obiekt gry na podstawie przekazanych parametrów i wczytuje pliki dźwiękowe i graficzne.
 * @param ustawianie Referencja do obiektu klasy Ustawianie zawierającego ustawienia gry.
 * @param exitscreen Ścieżka do pliku graficznego reprezentującego ekran zakończenia gry.
 * @param win Ścieżka do pliku graficznego reprezentującego ekran wygranej.
 * @param lose Ścieżka do pliku graficznego reprezentującego ekran przegranej.
 * @param wrongchoice Ścieżka do pliku graficznego reprezentującego ekran błędnego wyboru.
 * @param outofboard Ścieżka do pliku graficznego reprezentującego ekran wyjścia poza planszę.
 * @param hitsound Ścieżka do pliku dźwiękowego reprezentującego dźwięk trafienia.
 * @param misssound Ścieżka do pliku dźwiękowego reprezentującego dźwięk chybienia.
 * @param winsound Ścieżka do pliku dźwiękowego reprezentującego dźwięk wygranej.
 * @param losesound Ścieżka do pliku dźwiękowego reprezentującego dźwięk przegranej.
 */
void GamePlay::init(Ustawianie& ustawianie, char exitscreen[], char win[], char lose[], char wrongchoice[], char outofboard[], char hitsound[], char misssound[], char winsound[], char losesound[]) {
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
	this->HitSound = al_load_sample(hitsound);
	this->MissSound = al_load_sample(misssound);
	this->WinSound = al_load_sample(winsound);
	this->LoseSound = al_load_sample(losesound);
}

/**
 * @brief Rysuje interfejs rozgrywki.
 * Rysuje interfejs rozgrywki, w tym planszę przeciwnika i elementy graficzne takie jak litery, cyfry i przycisk wyjścia.
 * @param enemyboard Referencja do obiektu PlanszaGry reprezentującego planszę przeciwnika.
 */
void GamePlay::drawgameplay(PlanszaGry& enemyboard) {
	this->CzyGameplay = true;
	al_draw_bitmap(SrodPanel, 500, 0, 0);
	al_draw_bitmap(Litery, 76, 44, 0);
	al_draw_bitmap(Cyfry, 24, 94, 0);
	al_draw_bitmap(Exit, 514, 461, 0);
    enemyboard.drawplanszaprzeciwnika();
	al_draw_bitmap(Litery, 727, 44, 0);
	al_draw_bitmap(Cyfry, 1127, 94, 0);
}

/**
 * @brief Sprawdza trafienia statków przeciwnika na planszy.
 * Sprawdza, czy statki przeciwnika zostały trafione na planszy przeciwnika i ustawia odpowiednie flagi dla trafionych pól oraz pól wokół statków.
 * @param enemyships Referencja do obiektu ArmiaPrzeciwnik zawierającego statki przeciwnika.
 * @param enemyboard Referencja do obiektu PlanszaGry reprezentującego planszę przeciwnika.
 */
void GamePlay::SprawdzanieStatkowKomputera(ArmiaPrzeciwnik& enemyships, PlanszaGry& enemyboard) {
	for (auto statek : enemyships.statki1) {
		if (enemyboard.Pola[statek->Iczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku1) {
				enemyboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	for (auto statek : enemyships.statki2) {
		if (enemyboard.Pola[statek->Iczesc]->czyTrafione && enemyboard.Pola[statek->IIczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku2) {
				enemyboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	for (auto statek : enemyships.statki3) {
		if (enemyboard.Pola[statek->Iczesc]->czyTrafione && enemyboard.Pola[statek->IIczesc]->czyTrafione
			&& enemyboard.Pola[statek->IIIczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku3) {
				enemyboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	if (enemyboard.Pola[enemyships.statki4[0]->Iczesc]->czyTrafione && enemyboard.Pola[enemyships.statki4[0]->IIczesc]->czyTrafione
		&& enemyboard.Pola[enemyships.statki4[0]->IIIczesc]->czyTrafione && enemyboard.Pola[enemyships.statki4[0]->IVczesc]->czyTrafione) {
		for (auto pole : enemyships.statki4[0]->PolaWokolStatku4) {
			enemyboard.Pola[pole]->czyTrafione = true;
		}
	}
}

/**
 * @brief Sprawdza trafienia statków gracza na planszy.
 * Sprawdza, czy statki gracza zostały trafione na planszy gracza i ustawia odpowiednie flagi dla trafionych pól oraz pól wokół statków.
 * @param myships Referencja do obiektu ArmiaGracz zawierającego statki gracza.
 * @param myboard Referencja do obiektu PlanszaGry reprezentującego planszę gracza.
 */
void GamePlay::SprawdzanieStatkowGracza(ArmiaGracz& myships, PlanszaGry& myboard) {
	for (auto statek : myships.statki1) {
		if (myboard.Pola[statek->Iczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku1) {
				myboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	for (auto statek : myships.statki2) {
		if (myboard.Pola[statek->Iczesc]->czyTrafione && myboard.Pola[statek->IIczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku2) {
				myboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	for (auto statek : myships.statki3) {
		if (myboard.Pola[statek->Iczesc]->czyTrafione && myboard.Pola[statek->IIczesc]->czyTrafione
			&& myboard.Pola[statek->IIIczesc]->czyTrafione) {
			for (auto pole : statek->PolaWokolStatku3) {
				myboard.Pola[pole]->czyTrafione = true;
			}
		}
	}
	if (myboard.Pola[myships.statki4[0]->Iczesc]->czyTrafione && myboard.Pola[myships.statki4[0]->IIczesc]->czyTrafione
		&& myboard.Pola[myships.statki4[0]->IIIczesc]->czyTrafione && myboard.Pola[myships.statki4[0]->IVczesc]->czyTrafione) {
		for (auto pole : myships.statki4[0]->PolaWokolStatku4) {
			myboard.Pola[pole]->czyTrafione = true;
		}
	}
}

/**
 * @brief Obsługuje ruch gracza podczas rozgrywki.
 * Sprawdza, czy gracz kliknął na planszy przeciwnika i wykonuje odpowiednie akcje w zależności od wyniku ruchu.
 * @param event Zdarzenie ALLEGRO_EVENT reprezentujące ruch gracza.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gracza.
 * @param enemyboard Referencja do obiektu PlanszaGry reprezentującego planszę przeciwnika.
 * @param enemyships Referencja do obiektu ArmiaPrzeciwnik zawierającego statki przeciwnika.
 */
void GamePlay::RuchGracza(ALLEGRO_EVENT event, PlanszaGry& board, PlanszaGry& enemyboard, ArmiaPrzeciwnik& enemyships) {
	if (event.mouse.x >= 727 && event.mouse.x <= 1127 && event.mouse.y >= 94 && event.mouse.y <= 494) {
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1) {
			for (int i = 0; i < 100; i++) {
				if (event.mouse.x > enemyboard.Pola[i]->x && event.mouse.x < enemyboard.Pola[i]->x + 40
					&& event.mouse.y > enemyboard.Pola[i]->y && event.mouse.y < enemyboard.Pola[i]->y + 40) {
					if (!enemyboard.Pola[i]->czyTrafione) {
						enemyboard.Pola[i]->czyTrafione = true;
						if (enemyboard.Pola[i]->CzyStatek) {
							TrafionePlanszaAI++;
							al_play_sample(HitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							SprawdzanieStatkowKomputera(enemyships, enemyboard);
						}
						else {
							al_play_sample(MissSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							TuraGracza = false;
						}
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

/**
 * @brief Wykonuje ruch komputera podczas rozgrywki.
 * Losuje pole na planszy gracza i wykonuje odpowiednie akcje w zależności od wyniku ruchu.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gracza.
 * @param enemyboard Referencja do obiektu PlanszaGry reprezentującego planszę przeciwnika.
 * @param myships Referencja do obiektu ArmiaGracz zawierającego statki gracza.
 */
void GamePlay::RuchKomputera(PlanszaGry& board, PlanszaGry& enemyboard, ArmiaGracz& myships) {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dis(0, 99);

	int WylosowanePole = dis(gen);

	if (!board.Pola[WylosowanePole]->czyTrafione) {
		board.Pola[WylosowanePole]->czyTrafione = true;
		if (board.Pola[WylosowanePole]->CzyStatek) {
			TrafionePlanszaGracz++;
			al_play_sample(HitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			SprawdzanieStatkowGracza(myships, board);
		}
		else {
			al_play_sample(MissSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			TuraGracza = true;
		}
	}
	else {
		RuchKomputera(board, enemyboard, myships);
	}
}

/**
 * @brief Wykonuje rundę rozgrywki.
 * Wykonuje ruch gracza lub komputera w zależności od aktualnej tury.
 * @param event Zdarzenie ALLEGRO_EVENT reprezentujące ruch gracza.
 * @param board Referencja do obiektu PlanszaGry reprezentującego planszę gracza.
 * @param enemyboard Referencja do obiektu PlanszaGry reprezentującego planszę przeciwnika.
 * @param screen Referencja do obiektu Ustawianie reprezentującego ekran.
 * @param enemyships Referencja do obiektu ArmiaPrzeciwnik zawierającego statki przeciwnika.
 * @param myships Referencja do obiektu ArmiaGracz zawierającego statki gracza.
 */
void GamePlay::Rozgrywka(ALLEGRO_EVENT event, PlanszaGry& board, PlanszaGry& enemyboard, Ustawianie& screen, ArmiaPrzeciwnik& enemyships, ArmiaGracz& myships) {
	int WylosowanePole = 0;
	if (TuraGracza) {
		RuchGracza(event, board, enemyboard, enemyships);
	}

	if (!TuraGracza) {
		Sleep(200);
		RuchKomputera( board, enemyboard, myships);	
	}

	enemyboard.drawplansza();
}

/**
 * @brief Zniszcza zasoby używane przez obiekt GamePlay i przywraca domyślne ustawienia.
 * Wywołuje funkcje al_destroy_bitmap() dla bitmap używanych w obiekcie GamePlay.
 */
void GamePlay::destroy() {
	this->CzyGameplay = false;
	al_destroy_bitmap(SrodPanel);
	al_destroy_bitmap(Litery);
	al_destroy_bitmap(Cyfry);
	al_destroy_bitmap(Exit);
}
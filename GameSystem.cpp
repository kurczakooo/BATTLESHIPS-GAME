#include "GameSystem.h"

/**
* @file GameSystem.cpp
* @brief Plik definiujacy metody klas z GameSystem.h
*/


char tile[] = "elements/pole.png"; /**< Ścieżka do pliku z obrazem pola. */
char hit[] = "elements/hit.png"; /**< Ścieżka do pliku z obrazem trafionego pola. */
char miss[] = "elements/miss.png"; /**< Ścieżka do pliku z obrazem chybionego pola. */
char statek1[] = "elements/1statek.png"; /**< Ścieżka do pliku z obrazem jednomasztowego statku. */
char statek2[] = "elements/2statek.png"; /**< Ścieżka do pliku z obrazem dwumasztowego statku. */
char statek2r[] = "elements/2statek_rotated.png"; /**< Ścieżka do pliku z obrazem obróconego dwumasztowego statku. */
char statek3[] = "elements/3statek.png"; /**< Ścieżka do pliku z obrazem trójmasztowego statku. */
char statek4[] = "elements/4statek.png"; /**< Ścieżka do pliku z obrazem czteromasztowego statku. */
char dzwiek1[] = "sounds/setship1.wav"; /**< Ścieżka do pliku dźwiękowego dla ustawiania statków. */

/**
 * @brief Inicjalizuje klase GameSystem
 * @param dzwiek Ścieżka do pliku dźwiękowego
 */
void GameSystem::init(char dzwiek[]) {
	al_init(); /**< Inicjalizuje Allegro. */
	al_init_image_addon(); /**< Inicjalizuje dodatek do obsługi obrazów. */
	al_init_native_dialog_addon(); /**< Inicjalizuje dodatek do obsługi okien dialogowych. */
	al_install_mouse(); /**< Instaluje obsługę myszy. */
	al_install_audio(); /**< Instaluje obsługę dźwięku. */
	al_init_acodec_addon(); /**< Inicjalizuje dodatek do obsługi kodeków dźwiękowych. */
	al_reserve_samples(10); /**< Rezerwuje miejsce na 10 próbek dźwiękowych. */

	this->display = al_create_display(DisplayWidth, DisplayHeight); /**< Tworzy obiekt wyświetlania. */
	al_set_window_title(display, DisplayTitle); /**< Ustawia tytuł okna. */
	this->queue = al_create_event_queue(); /**< Tworzy kolejkę zdarzeń. */
	al_register_event_source(queue, al_get_display_event_source(display)); /**< Rejestruje źródło zdarzeń dla wyświetlacza. */
	al_register_event_source(queue, al_get_mouse_event_source()); /**< Rejestruje źródło zdarzeń dla myszy. */

	this->running = true; /**< Ustawia flagę running na true. */
	this->dzwiek = al_load_sample(dzwiek); /**< Wczytuje próbkę dźwiękową z pliku. */
}

/**
 * @brief Niszczy zasoby klasy GameSystem
 */
void GameSystem::destroy() {
	al_destroy_display(display); /**< Niszczy obiekt wyświetlania. */
	al_destroy_event_queue(queue); /**< Niszczy kolejkę zdarzeń. */
	al_uninstall_mouse(); /**< Dezinstaluje obsługę myszy. */
	al_uninstall_audio(); /**< Dezinstaluje obsługę dźwięku. */
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
	this->tytul = al_load_bitmap(Tytul); /**< Wczytuje bitmapę z tytułem. */
	this->tlo = al_load_bitmap(Tlo); /**< Wczytuje bitmapę z tłem. */
	this->graj = al_load_bitmap(Graj); /**< Wczytuje bitmapę przycisku "Graj". */
	this->exit = al_load_bitmap(Exit); /**< Wczytuje bitmapę przycisku "Wyjście". */
	this->jakgrac = al_load_bitmap(Jakgrac); /**< Wczytuje bitmapę przycisku "Jak grać". */
	this->instrukcje = al_load_bitmap(Instrukcje); /**< Wczytuje bitmapę z instrukcjami. */
	this->CzyInstrukcje = false; /**< Ustawia wartość logiczną "CzyInstrukcje" na false. */
	this->Gwidth = al_get_bitmap_width(graj); /**< Pobiera szerokość bitmapy przycisku "Graj". */
	this->Gheight = al_get_bitmap_height(graj); /**< Pobiera wysokość bitmapy przycisku "Graj". */
	this->Ewidth = al_get_bitmap_width(exit); /**< Pobiera szerokość bitmapy przycisku "Wyjście". */
}

/**
 * @brief Wyświetla menu.
 */
void Menu::drawMenu() {
	this->CzyMenu = true; /**< Ustawia flagę CzyMenu na true. */
	al_clear_to_color(al_map_rgb(255, 255, 255)); /**< Wypełnia tło kolorem białym. */
	al_draw_bitmap(tlo, 0, 0, 0); /**< Rysuje bitmapę tła na pozycji (0, 0). */
	al_draw_bitmap(tytul, 0, 0, 0); /**< Rysuje bitmapę tytułu na pozycji (0, 0). */
	al_draw_bitmap(graj, DisplayWidth / 2 - Gwidth / 2, DisplayHeight / 2 - Gheight / 2, 0); /**< Rysuje bitmapę przycisku "Graj" na wyśrodkowanej pozycji. */
	al_draw_bitmap(exit, DisplayWidth / 2 - Ewidth / 2, 410, 0); /**< Rysuje bitmapę przycisku "Wyjście" na pozycji (wyśrodkowana szerokość, 410). */
	al_draw_bitmap(jakgrac, 1117, 0, 0); /**< Rysuje bitmapę przycisku "Jak grać" na pozycji (1117, 0). */
}

/**
 * @brief Niszczy zasoby menu.
 */
void Menu::destroy() {
	this->CzyMenu = false; /**< Ustawia flagę CzyMenu na false. */
	al_destroy_bitmap(tytul); /**< Niszczy bitmapę tytułu. */
	al_destroy_bitmap(graj); /**< Niszczy bitmapę przycisku "Graj". */
	al_destroy_bitmap(exit); /**< Niszczy bitmapę przycisku "Wyjście". */
	al_destroy_bitmap(jakgrac); /**< Niszczy bitmapę przycisku "Jak grać". */
	al_destroy_bitmap(instrukcje); /**< Niszczy bitmapę z instrukcjami. */
	al_destroy_bitmap(tlo); /**< Niszczy bitmapę tła. */
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
	this->pole = al_load_bitmap(Pole); /**< Wczytuje bitmapę reprezentującą pole. */
	this->hit = al_load_bitmap(Hit); /**< Wczytuje bitmapę reprezentującą trafienie. */
	this->miss = al_load_bitmap(Miss); /**< Wczytuje bitmapę reprezentującą chybienie. */
	this->x = x; /**< Ustawia współrzędną x pola. */
	this->y = y; /**< Ustawia współrzędną y pola. */
	this->CzyStatek = statek; /**< Ustawia informację czy na polu znajduje się statek. */
	this->czyTrafione = trafione; /**< Ustawia informację czy pole zostało trafione. */
	this->wokolStatku = wokol; /**< Ustawia informację czy wokół pola znajduje się statek. */
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
		delete* tile; /**< Usuwa obiekt klasy Pole. */
	}
	Pola.clear(); /**< Czyści wektor Pola. */
}

/**
 * @brief Rysuje planszę gry.
 */
void PlanszaGry::drawplansza() {
	for (auto& tile : Pola) {
		if (tile->czyTrafione && tile->CzyStatek) /**< Jeśli pole zostało trafione i na nim znajduje się statek. */
			tile->pole = tile->hit; /**< Ustawia bitmapę trafienia dla pola. */
		else if (tile->czyTrafione && !tile->CzyStatek) /**< Jeśli pole zostało trafione i na nim nie ma statku. */
			tile->pole = tile->miss; /**< Ustawia bitmapę chybienia dla pola. */
		al_draw_bitmap(tile->pole, tile->x, tile->y, 0); /**< Rysuje bitmapę pola na określonej pozycji (x, y). */
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
	this->NapisObracanie = al_load_bitmap(Napis); /**< Wczytuje bitmapę reprezentującą napis. */
	this->SrodPanel = al_load_bitmap(Panel); /**< Wczytuje bitmapę reprezentującą panel. */
	this->Litery = al_load_bitmap(litery); /**< Wczytuje bitmapę reprezentującą litery. */
	this->Cyfry = al_load_bitmap(cyfry); /**< Wczytuje bitmapę reprezentującą cyfry. */
	this->Reset = al_load_bitmap(reset); /**< Wczytuje bitmapę reprezentującą przycisk reset. */
	this->Exit = al_load_bitmap(exit); /**< Wczytuje bitmapę reprezentującą przycisk wyjście. */
	this->Graj = al_load_bitmap(graj); /**< Wczytuje bitmapę reprezentującą przycisk "Graj". */
	this->Losuj = al_load_bitmap(losujustawianie); /**< Wczytuje bitmapę reprezentującą przycisk "Losuj ustawienie". */
	this->LosujWarning = al_load_bitmap(losujwarning); /**< Wczytuje bitmapę reprezentującą ostrzeżenie przy losowaniu. */
	this->GrajSound = al_load_sample(grajsound); /**< Wczytuje próbkę dźwiękową z pliku. */
}

/**
 * @brief Rysuje ekran ustawiania statków.
 * @param board Referencja do obiektu PlanszaGry.
 */
void Ustawianie::DrawUstawianie(PlanszaGry& board) {
	this->CzyUstawianie = true; /**< Ustawia flagę CzyUstawianie na true. */
	al_draw_bitmap(NapisObracanie, 700, 0, 0); /**< Rysuje bitmapę napisu na określonej pozycji. */
	al_draw_bitmap(SrodPanel, 500, 0, 0); /**< Rysuje bitmapę panelu na określonej pozycji. */
	al_draw_bitmap(Litery, 76, 44, 0); /**< Rysuje bitmapę liter na określonej pozycji. */
	al_draw_bitmap(Cyfry, 24, 94, 0); /**< Rysuje bitmapę cyfr na określonej pozycji. */
	al_draw_bitmap(Reset, 617, 461, 0); /**< Rysuje bitmapę przycisku reset na określonej pozycji. */
	al_draw_bitmap(Exit, 514, 461, 0); /**< Rysuje bitmapę przycisku wyjście na określonej pozycji. */
	al_draw_bitmap(Losuj, 508, 390, 0); /**< Rysuje bitmapę przycisku "Losuj ustawienie" na określonej pozycji. */

	if (ZajetePola == 20) /**< Jeśli wszystkie pola zostały zajęte. */
		al_draw_bitmap(Graj, 508, 235, 0); /**< Rysuje bitmapę przycisku "Graj" na określonej pozycji. */
}

/**
 * @brief Niszczy zasoby związane z klasą Ustawianie.
 */
void Ustawianie::destroy() {
	this->CzyUstawianie = false; /**< Ustawia flagę CzyUstawianie na false. */
	al_destroy_bitmap(NapisObracanie); /**< Niszczy bitmapę NapisObracanie. */
	al_destroy_bitmap(SrodPanel); /**< Niszczy bitmapę SrodPanel. */
	al_destroy_bitmap(Litery); /**< Niszczy bitmapę Litery. */
	al_destroy_bitmap(Cyfry); /**< Niszczy bitmapę Cyfry. */
	al_destroy_bitmap(Reset); /**< Niszczy bitmapę Reset. */
	al_destroy_bitmap(Exit); /**< Niszczy bitmapę Exit. */
	al_destroy_bitmap(Graj); /**< Niszczy bitmapę Graj. */
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

void Statek2::zaznaczwokol2(PlanszaGry &board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
		PolaWokolStatku2.push_back(Iczesc - 1);
	}
	if ((IIczesc + 1) % 10 != 0 && IIczesc != 99) {
		board.Pola[IIczesc + 1]->wokolStatku = true;     //dol statku
		PolaWokolStatku2.push_back(IIczesc + 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
		PolaWokolStatku2.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
		PolaWokolStatku2.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
		PolaWokolStatku2.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
		PolaWokolStatku2.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
		PolaWokolStatku2.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
		PolaWokolStatku2.push_back(IIczesc + 10);
	}
	if ((IIczesc - 9) >= 0 && (IIczesc - 9) % 10 != 0) {
		board.Pola[IIczesc - 9]->wokolStatku = true;    //lewo dol statku
		PolaWokolStatku2.push_back(IIczesc - 9);
	}
	if ((IIczesc + 11) <= 99 && (IIczesc + 11) % 10 != 0) {
		board.Pola[IIczesc + 11]->wokolStatku = true;    //prawo dol statku
		PolaWokolStatku2.push_back(IIczesc + 11);
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

void Statek3::zaznaczwokol3(PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
		PolaWokolStatku3.push_back(Iczesc - 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
		PolaWokolStatku3.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
		PolaWokolStatku3.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
		PolaWokolStatku3.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
		PolaWokolStatku3.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
		PolaWokolStatku3.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
		PolaWokolStatku3.push_back(IIczesc + 10);
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    //lewo III czesci
		PolaWokolStatku3.push_back(IIIczesc - 10);
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    //prawo III czesci
		PolaWokolStatku3.push_back(IIIczesc + 10);
	}
	if ((IIIczesc + 1) % 10 != 0 && IIIczesc != 99) {
		board.Pola[IIIczesc + 1]->wokolStatku = true;      //dol statku
		PolaWokolStatku3.push_back(IIIczesc + 1);
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    //lewo dol statku
		PolaWokolStatku3.push_back(IIIczesc - 9);
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    //prawo dol statku
		PolaWokolStatku3.push_back(IIIczesc + 11);
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

void Statek4::zaznaczwokol4(PlanszaGry& board) {
	if (Iczesc % 10 != 0) {
		board.Pola[Iczesc - 1]->wokolStatku = true;     //gora statku
		PolaWokolStatku4.push_back(Iczesc - 1);
	}
	if ((Iczesc - 11) >= 0 && (Iczesc - 10) % 10 != 0) {
		board.Pola[Iczesc - 11]->wokolStatku = true;    //lewo gora statku
		PolaWokolStatku4.push_back(Iczesc - 11);
	}
	if ((Iczesc + 9) < 99 && Iczesc % 10 != 0) {
		board.Pola[Iczesc + 9]->wokolStatku = true;    //prawo gora statku
		PolaWokolStatku4.push_back(Iczesc + 9);
	}
	if ((Iczesc - 10) >= 0) {
		board.Pola[Iczesc - 10]->wokolStatku = true;    //lewo I czesci 
		PolaWokolStatku4.push_back(Iczesc - 10);
	}
	if ((Iczesc + 10) < 99) {
		board.Pola[Iczesc + 10]->wokolStatku = true;    //prawo I czesci
		PolaWokolStatku4.push_back(Iczesc + 10);
	}
	if ((IIczesc - 10) >= 0) {
		board.Pola[IIczesc - 10]->wokolStatku = true;    //lewo II czesci 
		PolaWokolStatku4.push_back(IIczesc - 10);
	}
	if ((IIczesc + 10) <= 99) {
		board.Pola[IIczesc + 10]->wokolStatku = true;    //prawo II czesci
		PolaWokolStatku4.push_back(IIczesc + 10);
	}
	if ((IIIczesc - 10) >= 0 && (IIIczesc - 10) % 10 != 0) {
		board.Pola[IIIczesc - 10]->wokolStatku = true;    //lewo III czesci
		PolaWokolStatku4.push_back(IIIczesc - 10);
	}
	if ((IIIczesc + 10) <= 99 && (IIIczesc + 10) % 10 != 0) {
		board.Pola[IIIczesc + 10]->wokolStatku = true;    //prawo III czesci
		PolaWokolStatku4.push_back(IIIczesc + 10);
	}
	if ((IIIczesc - 9) >= 0 && (IIIczesc - 9) % 10 != 0) {
		board.Pola[IIIczesc - 9]->wokolStatku = true;    //lewo IVczesci
		PolaWokolStatku4.push_back(IIIczesc - 9);
	}
	if ((IIIczesc + 11) <= 99 && (IIIczesc + 11) % 10 != 0) {
		board.Pola[IIIczesc + 11]->wokolStatku = true;    //prawo IVczesci
		PolaWokolStatku4.push_back(IIIczesc + 11);
	}
	if ((IVczesc + 1) % 10 != 0 && IVczesc != 99) {
		board.Pola[IVczesc + 1]->wokolStatku = true;      //dol statku
		PolaWokolStatku4.push_back(IVczesc + 1);
	}
	if ((IVczesc - 9) >= 0 && (IVczesc - 9) % 10 != 0) {
		board.Pola[IVczesc - 9]->wokolStatku = true;    //lewo dol statku
		PolaWokolStatku4.push_back(IVczesc - 9);
	}
	if ((IVczesc + 11) <= 99 && (IVczesc + 11) % 10 != 0) {
		board.Pola[IVczesc + 11]->wokolStatku = true;    //prawo dol statku
		PolaWokolStatku4.push_back(IVczesc + 11);
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
		statki1[n]->zaznaczwokol1(board);
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
		statki2[n]->zaznaczwokol2(board);
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
		statki3[n]->zaznaczwokol3(board);
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
		statki4[0]->zaznaczwokol4(board);
		screen.ZajetePola += 4;
	}
	else if (!CzyMoznaLosowac)
		al_draw_bitmap(screen.LosujWarning, 500, 54, 0);
	else LosujPoczworny(event, board, screen);
}

void ArmiaGracz::LosujPlansze(ALLEGRO_EVENT event, PlanszaGry& board, Ustawianie& screen) {

	for (auto tile : board.Pola) {
		if (tile->CzyStatek)
			CzyMoznaLosowac = false;
	}

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

void ArmiaPrzeciwnik::init(){
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));
	this->statki1.push_back(new Statek1(statek1, 0, 0, 0, 0));

	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));
	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));
	this->statki2.push_back(new Statek2(statek2, statek2r, 0, 0, 0, 0));

	this->statki3.push_back(new Statek3(statek3, 0, 0, 0, 0));
	this->statki3.push_back(new Statek3(statek3, 0, 0, 0, 0));

	this->statki4.push_back(new Statek4(statek4, 0, 0, 0, 0));
}

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

void GamePlay::destroy() {
	this->CzyGameplay = false;
	al_destroy_bitmap(SrodPanel);
	al_destroy_bitmap(Litery);
	al_destroy_bitmap(Cyfry);
	al_destroy_bitmap(Exit);
}
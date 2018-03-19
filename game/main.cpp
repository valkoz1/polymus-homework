#include "curses.h"
int px = 1;
int py = 1;
int coins = 100000;
int next_inventory_obj = 0;
const char* inventory[1000];
chtype key;
class merchant {
public:
	int x = 0;
	int y = 0;
	chtype skin = 'M';
	void draw() {
		mvaddch(y, x, skin);
	}
	void say() {
		clear();
		move(0, 0);
		addstr("Hi");
		move(1, 0);
		addstr("What do you want to buy?(press key)");
		move(2, 0);
		addstr("1 - Little potion (10 coins)");
		move(3, 0);
		addstr("2 - Potion (20 coins)");
		move(4, 0);
		addstr("3 - Big potion (50 coins)");
		move(5, 0);
		addstr("4 - Super potion (120 coins)");
		move(6, 0);
		key=getch();
		if (key == '1' && coins >= 10) {
			coins -= 10;
			inventory[next_inventory_obj] = "Little potion";
			next_inventory_obj += 1;
		}
		if (key == '2' && coins >= 20) {
			coins -= 20;
			inventory[next_inventory_obj] = "Potion";
			next_inventory_obj += 1;
		}
		if (key == '3' && coins >= 50) {
			coins -= 50;
			inventory[next_inventory_obj] = "Big potion";
			next_inventory_obj += 1;
		}
		if (key == '4' && coins >= 120) {
			coins -= 120;
			inventory[next_inventory_obj] = "Super potion";
			next_inventory_obj += 1;
		}
		return;
	}
};
void inventory_open() {
	clear();
	move(0, 0);
	addstr("Inventory:");
	for (int i = 0; i <= next_inventory_obj; i++) {
		mvaddstr(i + 1, 0, inventory[i]);
	}
	getch();
}
void map_draw(int width, int height) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			mvaddch(y, x, '0' | COLOR_PAIR(2));
		}
	}
	for (int x = 1; x < (width-1); x++) {
		for (int y = 1; y < (height-1); y++) {
			mvaddch(y, x, ' ');
		}
	}
	if (px < 1) px = 1;
	if (py < 1) py = 1;
	if (px > (width - 2)) px = (width - 2);
	if (py > (height - 2)) py = (height - 2);

}
void initmass() {
	for (int i = 0; i < sizeof(inventory); i++) {
		inventory[i] = "";
	}
}

int main(){
	initscr();
	initmass();
	noecho();
	merchant petya;
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_CYAN);
	curs_set(0);
	petya.x = 10;
	petya.y = 1;
	while (1) {
		if ((petya.x == px) && (petya.y == py)) {
			petya.say();
		}
		map_draw(120, 29);
		mvaddstr(29, 0, "Coins: ");
		move(29, 7);
		printw("%d", coins);
		petya.draw();
		move(py, px); 
		addch('Y' | COLOR_PAIR(1));
		refresh();
		key = getch();
		if (key == 'w') py--;
		if (key == 'a') px--;
		if (key == 's') py++;
		if (key == 'd') px++;
		if (key == 'i') inventory_open();
		clear();
	}
	endwin();
	return 0;
}
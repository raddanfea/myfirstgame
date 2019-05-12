#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <linux/input.h>
#include <fstream>
#include <cstring>

using namespace std;

	int lvl = 0;
	int pont = 0;
	int x = 1;
	int y = 1;
	const int xmax = 20;
	const int ymax = 20;
	int wait;
	float draw;
	bool session = true;


	const char* const mapdata []={
 		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",
		"|"," ","X"," "," "," ","X","X","X"," ","X"," "," "," "," "," ","X","*"," ","|",
		"|"," "," "," ","X"," "," ","X"," "," ","X"," ","X"," ","X"," ","X","X"," ","|",
		"|","X","X","X","X","X"," ","X"," "," "," "," ","X"," ","X"," "," ","X"," ","|",
		"|"," ","X"," "," ","X"," ","X"," ","X"," "," ","X"," ","X","X"," "," "," ","|",
		"|"," ","X"," ","X","X"," ","X"," ","X"," "," "," "," "," ","X"," "," "," ","|",
		"|"," "," "," "," "," "," ","X"," ","X","X","X","X"," ","X","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," ","X"," "," "," "," ","X"," "," ","X"," ","X","X","|",
		"|"," ","X"," ","X","X"," ","X","X","X","X"," ","X","X"," ","X"," ","X"," ","|",
		"|"," ","X"," "," ","X"," ","X"," "," "," "," "," ","X"," ","X"," ","X"," ","|",
		"|"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","X"," "," "," ","|",
		"|"," "," "," ","X"," "," ","X"," ","X","X","X"," ","X"," ","X"," ","X","X","|",
		"|"," ","X"," ","X"," ","X","X"," "," "," ","X"," "," "," ","X","X","X"," ","|",
		"|"," ","X"," ","X"," "," "," "," "," "," ","X","X","X"," ","X"," "," "," ","|",
		"|"," ","X"," ","X"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," "," "," ","X"," ","|",
		"|"," ","X","X","X","X"," ","X"," ","X","X","X"," "," ","X","X"," ","X","X","|",
		"|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," ","X"," "," "," ","|",
		"|"," "," "," ","X","X","X","X"," "," "," ","X"," "," "," ","X"," ","X","W","|",
		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",

		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",
		"|"," ","X"," ","X"," ","X","X"," "," ","X"," ","X"," "," "," "," "," ","W","|",
		"|"," "," "," ","X"," "," ","X"," ","X","X"," ","X"," ","X","X","X","X"," ","|",
		"|","X","X"," ","X","X"," ","X"," "," "," "," ","X"," "," "," "," ","X","X","|",
		"|"," ","X"," "," "," "," ","X"," ","X"," ","X","X","X","X","X"," "," "," ","|",
		"|"," ","X"," ","X","X","X","X"," ","X"," "," "," "," "," ","X"," "," "," ","|",
		"|"," "," "," "," "," "," ","X"," ","X","X","X","X"," ","X","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," ","X"," ","X"," "," ","X"," "," ","X"," ","X"," ","|",
		"|"," ","X"," ","X","X"," ","X"," ","X","X"," ","X","X"," ","X"," ","X"," ","|",
		"|"," ","X"," "," ","X","X","X"," "," "," "," "," ","X"," ","X"," ","X","X","|",
		"|"," ","X","X","X","X"," ","X"," "," "," ","X"," "," "," ","X"," "," "," ","|",
		"|"," "," "," ","X"," "," ","X"," ","X","X","X"," ","X"," ","X"," ","X"," ","|",
		"|"," ","X"," "," "," ","X","X"," "," "," ","X"," ","X"," ","X","X","X"," ","|",
		"|"," ","X"," ","X","X"," "," "," "," "," ","X","X","X"," ","X"," "," "," ","|",
		"|","X","X"," ","X"," "," ","X","X","X"," ","X"," "," "," ","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," "," "," ","X","*","|",
		"|"," ","X"," ","X","X"," ","X"," ","X","X","X"," ","X","X","X"," ","X","X","|",
		"|"," ","X"," "," "," "," ","X"," "," "," ","X"," "," "," ","X"," "," "," ","|",
		"|"," "," "," ","X","X","X","X"," "," "," ","X"," "," "," ","X"," ","X","X","|",
		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",

		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",
		"|"," ","X"," "," "," ","X","X","X"," ","X"," "," "," "," "," ","X","*"," ","|",
		"|"," "," "," ","X"," "," ","X"," "," ","X"," ","X"," ","X"," ","X","X"," ","|",
		"|","X","X","X","X","X"," ","X"," "," "," "," ","X"," ","X"," "," ","X"," ","|",
		"|"," ","X"," "," ","X"," ","X"," ","X"," "," ","X"," ","X","X"," "," "," ","|",
		"|"," ","X"," ","X","X"," ","X"," ","X"," "," "," ","X"," ","X","X"," "," ","|",
		"|"," "," "," "," "," "," "," "," ","X","X","X","X"," ","X","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," ","X"," "," "," "," ","X"," "," ","X"," ","X","X","|",
		"|"," ","X"," ","X","X"," ","X","X","X","X","X","X","X"," ","X"," ","X"," ","|",
		"|"," ","X"," "," ","X"," "," ","X"," "," "," "," ","X"," ","X"," ","X"," ","|",
		"|"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","X"," "," "," ","|",
		"|"," "," "," ","X"," "," ","X"," ","X","X"," "," ","X"," "," "," ","X"," ","|",
		"|"," ","X"," ","X"," ","X","X"," "," "," ","X"," ","X"," ","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," "," "," "," "," ","X"," "," "," ","X"," ","X"," ","|",
		"|"," ","X"," ","X"," ","X","X","X","X"," ","X","X","X","X","X","X"," "," ","|",
		"|","X","X"," ","X"," ","X"," "," "," "," ","X"," "," "," "," "," "," ","X","|",
		"|","W","X","X","X","X","X","X","X","X","X","X"," ","X","X","X"," ","X"," ","|",
		"|"," ","X"," ","X"," "," "," "," "," "," ","X"," ","X"," "," "," "," "," ","|",
		"|"," "," "," "," "," ","X","X"," ","X"," "," "," ","X"," ","X"," ","X"," ","|",
		"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|"
	
	};

int iskiss(int ax, int bx)
{
int mpos=0;
int ret=1;
int m1pos = ((ymax*bx)+ax)+lvl*(xmax*ymax);
int m2pos = ((ymax*y)+x)+lvl*(xmax*ymax);

	switch (m2pos-m1pos){
		case -1:{ret=1; break;}
		case ymax:{ret=1; break;}
		case -ymax:{ret=1; break;}
		case 1:{ret=1; break;}
		default: {ret=0; break;}
	}

return ret;
}

void dram ()
{


	if ( x>xmax-2) {--x;}
	if ( x<=0 ) {++x;}
        if ( y<=0 ) {++y;}
        if ( y>ymax-2) {--y;}

	WINDOW *ablak;
    	ablak = initscr ();

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	
	for(int la = 0; la < ymax; la++)
		{
		int kla= 0;
		for(kla = 0; kla < xmax; kla++)
			{	
				//cout << "debugvonal------" << endl;
				if(iskiss(kla,la)==1)
				{
					switch(*mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]){
					
					case 'W': 
						{
							attron(COLOR_PAIR(4));
							mvprintw (la, kla, mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]);
							break;
						}

					case '|': case '-':
						{
							attron(COLOR_PAIR(5));
							mvprintw (la, kla, mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]);
							break;
						}

					case '*':
						{
							attron(COLOR_PAIR(6));
							mvprintw (la, kla, mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]);
							break;
						}

					default:
						{
							attron(COLOR_PAIR(3));
							mvprintw (la, kla, mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]);
							break;
						}
					}
				}
			}
		}

	
	attron(COLOR_PAIR(1));
	mvprintw ( y, x, "O" );
	attron(COLOR_PAIR(2));
	mvprintw ( 5, xmax+5, "X: %i",x );
	mvprintw ( 6, xmax+5, "Y: %i",y );
	mvprintw ( 8, xmax+5, "Szint: %i",lvl+1 );
	attron(COLOR_PAIR(6));
	mvprintw ( 9, xmax+5, "Pont: %i",lvl+pont );
	attron(COLOR_PAIR(3));
	mvprintw ( 2, 30, " ");
        refresh ();
        usleep (40000);
	clear();
}


void inpt ()
{


struct input_event event;

ifstream file("/dev/input/event2");
    
    char data[sizeof(event)];
	
    if(file.is_open()) {
        
        while(session) {
		dram();
            
            	file.read(data, sizeof(event));

            	memcpy(&event, data, sizeof(event));

            	if(event.type == EV_KEY) {
		if(event.code == KEY_D) {if (mapdata[(ymax*y)+x+1+lvl*(xmax*ymax)] != "X") {++x;}; usleep (100000);  break;}
		if(event.code == KEY_W) {if (mapdata[(ymax*(y-1))+x+lvl*(xmax*ymax)] != "X") {--y;}; usleep (100000);  break;}
		if(event.code == KEY_S) {if (mapdata[(ymax*(y+1))+x+lvl*(xmax*ymax)] != "X") {++y;}; usleep (100000);  break;}
		if(event.code == KEY_A) {if (mapdata[(ymax*y)+x-1+lvl*(xmax*ymax)] != "X") {--x;}; usleep (100000);  break;}
		        else 	{ break; }
	    	}
		if (mapdata[(ymax*y)+x+lvl*(xmax*ymax)] == "W")
			{
				if(lvl < 2){lvl++; x=1;y=1;break;}
				else{session = false; lvl++; break;};

			}
		if (mapdata[(ymax*y)+x+lvl*(xmax*ymax)] == "*"){pont++;}
        }
        file.close();
    }
    else {
        
        cout << "Unable to open file!" << endl;
    }

}


int
main ( void )
{
	while (lvl != 3) 
		{
			inpt ();
		}
	endwin();

const std::string yellow("\033[1;33m");
const std::string red("\033[0;31m");
const std::string reset("\033[0m");

cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" <<
"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
cout << yellow << " _________" << endl;
cout << " |       |" << endl;
cout << "(|       |)" << endl;
cout << " |       |" << endl;
cout << "  \\     /" << endl;
cout << "   `---'" << endl;
cout << "   _|_|_" << endl << endl << endl;
cout << red << "  Nyertél!" << reset << endl << endl << endl;
cout << "  Pontok:" << lvl+pont << endl << endl << endl;
return 0;
}

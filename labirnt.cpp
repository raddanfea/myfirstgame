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
	bool p1 = false;
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
				//if(iskiss(kla,la)!=100000000) //fullscreen nézet csalás
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
							if (p1==false){
								attron(COLOR_PAIR(6));
								mvprintw (la, kla, mapdata[(ymax*la)+kla+lvl*(xmax*ymax)]);
								break;
							}
							else {mvprintw (la, kla, " ");break;}
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
	//mvprintw ( 5, xmax+5, "X: %i",x );
	//mvprintw ( 6, xmax+5, "Y: %i",y );
	mvprintw ( 8, xmax+5, "Szint: %i",lvl+1 );
	attron(COLOR_PAIR(6));
	mvprintw ( 9, xmax+5, "Pont: %i",lvl+pont );
	attron(COLOR_PAIR(3));
	mvprintw ( 2, xmax+5, " ");
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
				p1=false;
				if(lvl < 2){lvl++; x=1;y=1; break;}
				else{session = false; lvl++; break;};

			}
		if (mapdata[(ymax*y)+x+lvl*(xmax*ymax)] == "*" && p1 == false){pont++; p1=true;}
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
Skip to content
Pull requests
Issues
Marketplace
Explore
@raddanfea

0
0

    0

raddanfea/myfirstgame
Code
Issues 0
Pull requests 0
Projects 0
Wiki
Insights
Settings
myfirstgame/

1

#include <stdio.h>

2

#include <curses.h>

3

#include <unistd.h>

4

#include <iostream>

5

#include <linux/input.h>

6

#include <fstream>

7

#include <cstring>

8

​

9

using namespace std;

10

​

11

        int lvl = 0;

12

        int pont = 0;

13

        int x = 1;

14

        int y = 1;

15

        const int xmax = 20;

16

        const int ymax = 20;

17

        int wait;

18

        float draw;

19

        bool session = true;

20

​

21

​

22

        const char* const mapdata []={

23

                "|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",

24

                "|"," ","X"," "," "," ","X","X","X"," ","X"," "," "," "," "," ","X","*"," ","|",

25

                "|"," "," "," ","X"," "," ","X"," "," ","X"," ","X"," ","X"," ","X","X"," ","|",

26

                "|","X","X","X","X","X"," ","X"," "," "," "," ","X"," ","X"," "," ","X"," ","|",

27

                "|"," ","X"," "," ","X"," ","X"," ","X"," "," ","X"," ","X","X"," "," "," ","|",

28

                "|"," ","X"," ","X","X"," ","X"," ","X"," "," "," "," "," ","X"," "," "," ","|",

29

                "|"," "," "," "," "," "," ","X"," ","X","X","X","X"," ","X","X"," ","X"," ","|",

30

                "|"," ","X"," ","X"," "," ","X"," "," "," "," ","X"," "," ","X"," ","X","X","|",

31

                "|"," ","X"," ","X","X"," ","X","X","X","X"," ","X","X"," ","X"," ","X"," ","|",

32

                "|"," ","X"," "," ","X"," ","X"," "," "," "," "," ","X"," ","X"," ","X"," ","|",

33

                "|"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","X"," "," "," ","|",

34

                "|"," "," "," ","X"," "," ","X"," ","X","X","X"," ","X"," ","X"," ","X","X","|",

35

                "|"," ","X"," ","X"," ","X","X"," "," "," ","X"," "," "," ","X","X","X"," ","|",

36

                "|"," ","X"," ","X"," "," "," "," "," "," ","X","X","X"," ","X"," "," "," ","|",

37

                "|"," ","X"," ","X"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","|",

38

                "|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," "," "," ","X"," ","|",

39

                "|"," ","X","X","X","X"," ","X"," ","X","X","X"," "," ","X","X"," ","X","X","|",

40

                "|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," ","X"," "," "," ","|",

41

                "|"," "," "," ","X","X","X","X"," "," "," ","X"," "," "," ","X"," ","X","W","|",

42

                "|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",

43

​

44

                "|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|",

45

                "|"," ","X"," ","X"," ","X","X"," "," ","X"," ","X"," "," "," "," "," ","W","|",

46

                "|"," "," "," ","X"," "," ","X"," ","X","X"," ","X"," ","X","X","X","X"," ","|",

47

                "|","X","X"," ","X","X"," ","X"," "," "," "," ","X"," "," "," "," ","X","X","|",

48

                "|"," ","X"," "," "," "," ","X"," ","X"," ","X","X","X","X","X"," "," "," ","|",

49

                "|"," ","X"," ","X","X","X","X"," ","X"," "," "," "," "," ","X"," "," "," ","|",

50

                "|"," "," "," "," "," "," ","X"," ","X","X","X","X"," ","X","X"," ","X"," ","|",

@raddanfea
Commit changes
Commit summary
Optional extended description
Commit directly to the master branch.
Create a new branch for this commit and start a pull request. Learn more about pull requests.

    © 2019 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    Pricing
    API
    Training
    Blog
    About


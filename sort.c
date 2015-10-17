#include <stdlib.h>
#include <time.h>
#include <curses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 

int row,col;				/* to store the number of rows and columns */
 
int compFunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void printList(int *list) 
{
    int loop, loop2;
    int currRow, currCol;
	getyx(stdscr,currRow,currCol);
    mvprintw(currRow++,col/3,"-------------------------------\n");

    for (loop = 0; loop < 5; loop++) 
    {
        mvprintw(currRow,col/3+5,"|");
		
        for (loop2 = 0; loop2 < 5; loop2++) 
        {
            getyx(stdscr,currRow,currCol);
			mvprintw(currRow,currCol,"%hd ",*(list + (5 * loop) + loop2));
        }
       getyx(stdscr,currRow,currCol);
		mvprintw(currRow++,currCol,"|\n");
    }
	getyx(stdscr,currRow,currCol);
	mvprintw(currRow,col/3,"-------------------------------\n");
}

void fillList(int *list) 
{
    int loop;

    for (loop = 0; loop < 25; loop++) 
    {
        *(list + loop) = (rand() % 900) + 100;  // find numbers between 100 and 999
    }
}

void main(int argc, char **argv) 
{
	int currRow,currCol;
    int list[25];
    char *msg1 = "Random List of Integers\n";
    char *msg2 = "Press any key to sort...\n";
    char *msg3 = "Sorted List of Integers\n";
    char *msg4 = "Press \"q\" to quit, anything else to continue\n";
    
    // seed the random number generator
	srand(time(NULL));
    initscr();
    while(1)
    {
		refresh();
		getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
		fillList(list);
		getyx(stdscr,currRow,currCol);
		mvprintw(currRow,col/3,"%s",msg1);
		refresh();
		printList(list);
		getyx(stdscr,currRow,currCol);
		mvprintw(currRow,col/3,"%s",msg2);
		refresh();
		getchar();

		qsort(list,25,sizeof(int),compFunc);

		getyx(stdscr,currRow,currCol);
		mvprintw(currRow,col/3,"%s",msg3);
		printList(list);
		getyx(stdscr,currRow,currCol);
		mvprintw(currRow,col/3,"%s",msg4);
		refresh();
		int c = getchar();
		if (c == 'q')
			break;
		clear();
	}
    endwin();
}

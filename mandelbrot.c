#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 900
#define GRAPHSIZE 2
#define STARTX -GRAPHSIZE
#define STARTY -GRAPHSIZE
#define SIDELENGTH SIZE*GRAPHSIZE*2

int is_in_set(float c_real, float c_imag) {
    float z_real = 0;
    float z_imag = 0;

    int iters = 0;

    float i_term;
    // This is where the check for whether a point is in the set occurs
    // The number of iterations it takes to leave the box [(-2, -2), (-2, 2), (2, 2), (2, -2)]
    // is what determines the color of the point
    do {
        i_term = z_real*z_imag;
        z_real = z_real*z_real - z_imag*z_imag + c_real;
        z_imag = 2*i_term + c_imag;
        iters++;
    } while ((iters < 255) && (z_real * z_real + z_imag * z_imag) < 4);

    return iters;

}


int main() {
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("No color support! :C\n");
        exit(1);
    }
    start_color();
    float x0 = STARTX;
    float y0 = STARTY;
    // There's probably a better way to make colors!
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    if (maxx < maxy) {
        maxy = maxx;
    } else {
        maxx = maxy;
    }

    for (int i=0; i<SIDELENGTH; i++) {
        for (int j=0; j<SIDELENGTH; j++) {
            float y = y0 + (float) j / SIZE;
            float x = x0 + (float) i / SIZE;
            int color = is_in_set(x, y);
            int scr_y = (y - y0) * (SIZE / maxy); // displacment = fractions of SIZE, gotta convert to fractions of MAXY/MAXX
            int scr_x = (x - x0) * (SIZE / maxx);

            // There's definitely a better way to do this
            switch(color) {
                case 1:
                    attron(COLOR_PAIR(1));
                    mvaddch(scr_y, scr_x, '.');
                    attroff(COLOR_PAIR(1));
                    break;
                case 2:
                    attron(COLOR_PAIR(2));
                    mvaddch(scr_y, scr_x, '1');
                    attroff(COLOR_PAIR(2));
                    break;
                case 3:
                    attron(COLOR_PAIR(3));
                    mvaddch(scr_y, scr_x, '2');
                    attroff(COLOR_PAIR(3));
                    break;
                case 4:
                    attron(COLOR_PAIR(4));
                    mvaddch(scr_y, scr_x, '3');
                    attroff(COLOR_PAIR(4));
                    break;
                case 5:
                    attron(COLOR_PAIR(5));
                    mvaddch(scr_y, scr_x, '4');
                    attroff(COLOR_PAIR(5));
                    break;
                case 6:
                    attron(COLOR_PAIR(6));
                    mvaddch(scr_y, scr_x, '5');
                    attroff(COLOR_PAIR(6));
                    break;
                case 7:
                    attron(COLOR_PAIR(7));
                    mvaddch(scr_y, scr_x, '8');
                    attroff(COLOR_PAIR(7));
                    break;
                default:
                    if (color >= 255) {
                        attron(A_BOLD);
                        attron(COLOR_PAIR(8));
                        mvaddch(scr_y, scr_x, 'x' );
                        attroff(COLOR_PAIR(8));
                        attroff(A_BOLD);
                        break;
                    } else {
                        attron(COLOR_PAIR(8));
                        mvaddch(scr_y, scr_x, 'A');
                        attroff(COLOR_PAIR(8));
                        break;
                    }
            }
        }
    }

    refresh();
    getch();
    endwin();
    return 0;
}

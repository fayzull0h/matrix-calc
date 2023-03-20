#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

struct vector {
    int n;
    int *vec;
};

int ch_to_int(char c) {
    return c - 48;
}

void vector_move(int y, int x) {
    if (x == 1) {
        x = 2;
    } else if (x == 2) {
        x = 9;
    }
    move(y, x);
}

void draw_vector(struct vector *v, bool is_blank, char left, char right, int select, bool is_highlighted) {
    int vsize = v->n;
    int x = getcurx(stdscr);
    int y = getcury(stdscr) + 1;

    if (vsize == 1) {
        printw("%c", left);
        if (is_blank) printw("___");
        else printw("%3d", v->vec[0]);
        printw("%c", right);
        return;
    }

    for (int i = 0; i < vsize; ++i) {
        mvprintw(y + i, x, "%c", left);
        if (select == i) {
            attron(A_STANDOUT);
            if (is_highlighted) {
                attroff(A_STANDOUT);
                attron(COLOR_PAIR(1));
            }
        }
        
        if (is_blank && v->vec[i] == 0) printw("___");
        else printw("%3d", v->vec[i]);

        attroff(COLOR_PAIR(1));
        attroff(A_STANDOUT);
        printw("%c", right);
    }
}

void draw_both(struct vector *v1, struct vector *v2, int highlight, bool is_highlighted) {
    move(0, 0);
    int vsize = v1->n;
    bool overlap;
    if (highlight >= vsize) {
        highlight -= vsize;
        draw_vector(v1, true, '|', '|', -1, is_highlighted);
        move(0, 7);
        draw_vector(v2, true, '|', '|', highlight, is_highlighted);
        return;
    }
    draw_vector(v1, true, '|', '|', highlight, is_highlighted);
    move(0, 7);
    draw_vector(v2, true, '|', '|', -1, is_highlighted);
}

void input_number(struct vector *v, int which) {
    int vsize = v->n;
    int x = 2;
    int y = which + 1;

    if (which >= vsize) {
        x += 7;
        y -= vsize;
        which -= vsize;
    }

    move(y, x);
    echo();
    
    int first = 0;
    int second = 0;
    int third = 0;

    while (1) {
        first = getch();
        refresh();
        if (first == 10) {
            v->vec[which] = 0;
            break;
        }
        second = getch();
        refresh();
        if (second == 10) {
            v->vec[which] = ch_to_int(first);
            break;
        }
        third = getch();
        refresh();
        if (third == 10) {
            if (first == '-') {
                v->vec[which] = -1 * ch_to_int(second);
            } else {
                v->vec[which] = 10 * ch_to_int(first) + ch_to_int(second);
            }
            break;
        }
    }
    noecho();
}

void get_input(struct vector *v1, struct vector *v2) {
    int vsize = v1->n;
    int ch;
    bool is_highlighted;

    int posx = 1;
    int posy = 1;

    int highlight = 0;
    draw_both(v1, v2, highlight, false);
    while (1) {
        vector_move(posy, posx);
        ch = getch();
        
        if (ch == 'k' || ch == KEY_UP) {
            if (highlight != 0 && highlight != vsize) {
                highlight--;
                posy--;
            }
        } else if (ch == 'j' || ch == KEY_DOWN) {
            if (highlight != vsize - 1 && highlight != vsize * 2 - 1) {
                highlight++;
                posy++;
            }
        } else if (ch == 'h' || ch == KEY_LEFT) {
            if (highlight >= vsize) {
                highlight -= v1->n;
                posx--;
            }
        } else if (ch == 'l' || ch == KEY_RIGHT) {
            if (highlight < vsize) {
                highlight += v1->n;
                posx++;
            }
        } else if (ch == 10) {
            is_highlighted = true;
            draw_both(v1, v2, highlight, is_highlighted);
            refresh();
            if (posx == 1) {
                input_number(v1, highlight);
            } else {
                input_number(v2, highlight);
            }
            is_highlighted = false;
        } else if (ch == 'q') {
            break;
        }
        draw_both(v1, v2, highlight, is_highlighted);
        refresh();
    }
}

int dot_product(struct vector *v1, struct vector *v2) {
    int vsize = v1->n;
    int result = 0;
    for (int i = 0; i < vsize; ++i) {
        result += v1->vec[i] * v2->vec[i];
    }
    return result;
}

int main(void) {
    struct vector myvec1 = {0, NULL};
    struct vector myvec2 = {0, NULL};
    printf("How many elements in vector? ");
    int temp = 0;
    scanf(" %d", &temp);
    myvec1.n = temp;
    myvec1.vec = (int *) calloc(temp, sizeof(int));
    myvec2.n = temp;
    myvec2.vec = (int *) calloc(temp, sizeof(int));

    initscr();
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_GREEN);
    mvprintw(0, 0, "Enter numbers:");
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    move(0,0);
    get_input(&myvec1, &myvec2);

    clear();
    move(0,0);
    printw("Final:");
    draw_both(&myvec1, &myvec2, -1, 0);
    move(myvec1.n + 2, 0);
    printw("Dot product: %d", dot_product(&myvec1, &myvec2));
    refresh();
    getch();

    endwin();

    free(myvec1.vec);
    free(myvec2.vec);
    return 0;
}

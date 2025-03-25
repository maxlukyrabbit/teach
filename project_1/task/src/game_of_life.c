#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define STATIC_GENERATIONS 5

void run_game();
int alive_or_dead(int matrix[HEIGHT][WIDTH], int x, int y);
int input_matrix(int matrix[HEIGHT][WIDTH]);
void draw(int matrix[HEIGHT][WIDTH]);
void draw_content(int matrix[HEIGHT][WIDTH]);
void handle_input(int *speed, int *temp_speed, char *input);
void checking_input(char input, int *speed, int *temp_speed);
void update_matrix(int matrix[HEIGHT][WIDTH], int *f);
void ending(int flag_out);
void eror_ending();

int main() {
    run_game();
    return 0;
}

void run_game() {
    int new_matrix[HEIGHT][WIDTH];
    int speed = 500, temp_speed = speed, flag_out = 1;
    char input = 'o';

    if (input_matrix(new_matrix)) {
        setlocale(LC_CTYPE, "");
        if (freopen("/dev/tty", "r", stdin)) initscr();
        noecho();
        cbreak();
        curs_set(0);
        nodelay(stdscr, TRUE);
        draw(new_matrix);

        while (input != 'q' && input != 'Q' && flag_out) {
            handle_input(&speed, &temp_speed, &input);
            if (speed != 0) {
                update_matrix(new_matrix, &flag_out);
                draw(new_matrix);
            }
            napms(speed);
        }
        ending(flag_out);
    } else {
        printf("n/a");
    }
}

int input_matrix(int matrix[HEIGHT][WIDTH]) {
    int temp, f = 1, k = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (scanf("%1d", &temp) == 1) {
                if (temp == 1) {
                    k++;
                    matrix[i][j] = 1;
                } else if (temp == 0) {
                    k++;
                    matrix[i][j] = 0;
                } else {
                    f = 0;
                }
            }
        }
    }
    if (k != 2000) {
        f = 0;
    }
    return f;
}

void draw(int matrix[HEIGHT][WIDTH]) {
    clear();
    printw("┌");
    for (int j = 0; j < WIDTH; j++) {
        printw("─");
        if (j < WIDTH - 1) printw("┼");
    }
    printw("┐\n");
    draw_content(matrix);
    printw("└");
    for (int j = 0; j < WIDTH; j++) {
        printw("─");
        if (j < WIDTH - 1) printw("┼");
    }
    printw("┘\n");
    refresh();
}

void draw_content(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        printw("│");
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j] == 1) {
                printw("●");
            } else {
                printw(" ");
            }
            if (j < WIDTH - 1) printw("│");
        }
        printw("│\n");

        if (i < HEIGHT - 1) {
            printw("┼");
            for (int j = 0; j < WIDTH; j++) {
                printw("─");
                if (j < WIDTH - 1) printw("┼");
            }
            printw("┼\n");
        }
    }
}

void handle_input(int *speed, int *temp_speed, char *input) {
    *input = getch();
    if (*speed != 0) {
        checking_input(*input, speed, temp_speed);
    } else if (*input == 'Q' || *input == 'q' || *input == ' ') {
        checking_input(*input, speed, temp_speed);
    }
}

void checking_input(char input, int *speed, int *temp_speed) {
    if (input == 'a' && *speed <= 2500) {
        *speed += 100;
    } else if (input == 'z' && *speed >= 200) {
        *speed -= 100;
    } else if (input == ' ' && *speed == 0) {
        *speed = *temp_speed;
    } else if (input == ' ') {
        *temp_speed = *speed;
        *speed = 0;
    }
}

int alive_or_dead(int matrix[HEIGHT][WIDTH], int x, int y) {
    int neighbours = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = (y + i + HEIGHT) % HEIGHT;
            int nj = (x + j + WIDTH) % WIDTH;
            neighbours += matrix[ni][nj];
        }
    }

    return neighbours;
}

void update_matrix(int new_matrix[HEIGHT][WIDTH], int *flag_out) {
    int old_matrix[HEIGHT][WIDTH], flag_in = 1;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            old_matrix[i][j] = new_matrix[i][j];
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbours = alive_or_dead(old_matrix, j, i);
            if ((neighbours == 2 || neighbours == 3) && old_matrix[i][j] == 1) {
                new_matrix[i][j] = 1;
            } else if (neighbours == 3 && old_matrix[i][j] == 0) {
                new_matrix[i][j] = 1;
            } else {
                new_matrix[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (old_matrix[i][j] != new_matrix[i][j]) {
                flag_in = 0;
            }
        }
    }
    if (flag_in) {
        napms(1000);
        *flag_out = 0;
    }
}

void ending(int flag_out) {
    if (flag_out) {
        printw("Эволюция завершена");
        refresh();
        napms(1500);
        endwin();
    } else {
        printw("Эволюция завершена");
        char input;
        do {
            input = getch();
        } while (input != 'q' && input != 'Q');
    }
}
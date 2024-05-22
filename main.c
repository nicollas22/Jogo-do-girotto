#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define ROWS_PHASE_1 10
#define COLS_PHASE_1 10
#define ROWS_PHASE_2 20
#define COLS_PHASE_2 20
#define ROWS_PHASE_3 40
#define COLS_PHASE_3 40

enum Phase {
    MAIN_MENU,
    TUTORIAL,
    PHASE_1,
    PHASE_2,
    PHASE_3,
    VICTORY,
    DEFEAT
};

struct Player {
    int row;
    int col;
};

struct Enemy {
    int row;
    int col;
};

struct Key {
    int row;
    int col;
    int collected;
    int visible;
};

struct Door {
    int row;
    int col;
    int opened;
};

struct Spike {
    int row;
    int col;
};

struct Button {
    int row;
    int col;
    int pressed;
};

void clearScreen() {
    system("cls");
}

void displayMainMenu() {
    clearScreen();
    printf("MENU PRINCIPAL\n");
    printf("1. Jogar\n");
    printf("2. Tutorial\n");
    printf("3. Sair\n");
}

void displayPhase1(struct Player player, struct Enemy enemy, struct Key key, struct Door door, struct Spike spike, struct Button button) {
    clearScreen();
    printf("FASE 1\n");
    int i, j;
    for (i = 0; i < ROWS_PHASE_1; i++) {
        for (j = 0; j < COLS_PHASE_1; j++) {
            if (i == 0 || i == ROWS_PHASE_1 - 1 || j == 0 || j == COLS_PHASE_1 - 1) {
                printf("* ");
            } else if (i == player.row && j == player.col) {
                printf("& ");
            } else if (i == enemy.row && j == enemy.col) {
                printf("x ");
            } else if (i == key.row && j == key.col && key.visible && !key.collected) {
                printf("@ ");
            } else if (i == door.row && j == door.col && !door.opened) {
                printf("D ");
            } else if (i == door.row && j == door.col && door.opened) {
                printf("= ");
            } else if (i == spike.row && j == spike.col) {
                printf("# ");
            } else if (i == button.row && j == button.col) {
                if (button.pressed)
                    printf("O ");
                else
                    printf("o ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void displayPhase2(struct Player player, struct Enemy enemy1, struct Enemy enemy2, struct Enemy chasingEnemy, struct Key key, struct Door door, struct Spike spikes[], int spikeCount, struct Button button) {
    clearScreen();
    printf("FASE 2\n");
    int i, j, k;
    for (i = 0; i < ROWS_PHASE_2; i++) {
        for (j = 0; j < COLS_PHASE_2; j++) {
            if (i == 0 || i == ROWS_PHASE_2 - 1 || j == 0 || j == COLS_PHASE_2 - 1) {
                printf("* ");
            } else if (i == player.row && j == player.col) {
                printf("& ");
            } else if (i == enemy1.row && j == enemy1.col) {
                printf("x ");
            } else if (i == enemy2.row && j == enemy2.col) {
                printf("x ");
            } else if (i == chasingEnemy.row && j == chasingEnemy.col) {
                printf("X ");
            } else if (i == key.row && j == key.col && key.visible && !key.collected) {
                printf("@ ");
            } else if (i == door.row && j == door.col && !door.opened) {
                printf("D ");
            } else if (i == door.row && j == door.col && door.opened) {
                printf("= ");
            } else {
                int printed = 0;
                for (k = 0; k < spikeCount; k++) {
                    if (i == spikes[k].row && j == spikes[k].col) {
                        printf("# ");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    if (i == button.row && j == button.col) {
                        if (button.pressed)
                            printf("O ");
                        else
                            printf("o ");
                    } else {
                        printf("  ");
                    }
                }
            }
        }
        printf("\n");
    }
}

void displayPhase3(struct Player player, struct Enemy enemies[], int enemyCount, struct Enemy chasingEnemy, struct Key key, struct Door door, struct Spike spikes[], int spikeCount, struct Button button) {
    clearScreen();
    printf("FASE 3\n");
    int i, j, k, l;
    for (i = 0; i < ROWS_PHASE_3; i++) {
        for (j = 0; j < COLS_PHASE_3; j++) {
            if (i == 0 || i == ROWS_PHASE_3 - 1 || j == 0 || j == COLS_PHASE_3 - 1) {
                printf("* ");
            } else if (i == player.row && j == player.col) {
                printf("& ");
            } else if (i == chasingEnemy.row && j == chasingEnemy.col) {
                printf("X ");
            } else {
                int printed = 0;
                for (k = 0; k < enemyCount; k++) {
                    if (i == enemies[k].row && j == enemies[k].col) {
                        printf("x ");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    for (l = 0; l < spikeCount; l++) {
                        if (i == spikes[l].row && j == spikes[l].col) {
                            printf("# ");
                            printed = 1;
                            break;
                        }
                    }
                }
                if (!printed) {
                    if (i == key.row && j == key.col && key.visible && !key.collected) {
                        printf("@ ");
                    } else if (i == door.row && j == door.col && !door.opened) {
                        printf("D ");
                    } else if (i == door.row && j == door.col && door.opened) {
                        printf("= ");
                    } else if (i == button.row && j == button.col) {
                        if (button.pressed)
                            printf("O ");
                        else
                            printf("o ");
                    } else {
                        printf("  ");
                    }
                }
            }
        }
        printf("\n");
    }
}

void initializePhase1() {
    struct Player player = {1, 1};
    struct Enemy enemy = {ROWS_PHASE_1 - 2, COLS_PHASE_1 - 2};
    struct Key key = {rand() % (ROWS_PHASE_1 - 2) + 1, rand() % (COLS_PHASE_1 - 2) + 1, 0, 0};
    struct Door door = {ROWS_PHASE_1 - 2, 1, 0};
    struct Spike spike = {rand() % (ROWS_PHASE_1 - 2) + 1, rand() % (COLS_PHASE_1 - 2) + 1};
    struct Button button;
    int restartCount = 0;

    // Define a posição do botão dentro da matriz 10x10
    do {
        button.row = rand() % (ROWS_PHASE_1 - 2) + 1;
        button.col = rand() % (COLS_PHASE_1 - 2) + 1;
    } while (button.row == player.row && button.col == player.col ||
             button.row == enemy.row && button.col == enemy.col ||
             button.row == door.row && button.col == door.col ||
             button.row == spike.row && button.col == spike.col);

    button.pressed = 0;

    char input;
    while (1) {
        displayPhase1(player, enemy, key, door, spike, button);
        input = getch();
        switch (input) {
            case 'w':
            case 'W':
                if (player.row > 1)
                    player.row--;
                break;
            case 'a':
            case 'A':
                if (player.col > 1)
                    player.col--;
                break;
            case 's':
            case 'S':
                if (player.row < ROWS_PHASE_1 - 2)
                    player.row++;
                break;
            case 'd':
            case 'D':
                if (player.col < COLS_PHASE_1 - 2)
                    player.col++;
                break;
            case 'q':
            case 'Q':
                return;
            case 'i':
            case 'I':
                if (player.row == button.row && player.col == button.col) {
                    button.pressed = 1;
                    key.visible = 1;
                }
                break;
            default:
                break;
        }

        // Movimentação aleatória do inimigo
        int randomMove = rand() % 4; // 0 para cima, 1 para baixo, 2 para esquerda, 3 para direita
        switch (randomMove) {
            case 0:
                if (enemy.row > 1)
                    enemy.row--;
                break;
            case 1:
                if (enemy.row < ROWS_PHASE_1 - 2)
                    enemy.row++;
                break;
            case 2:
                if (enemy.col > 1)
                    enemy.col--;
                break;
            case 3:
                if (enemy.col < COLS_PHASE_1 - 2)
                    enemy.col++;
                break;
            default:
                break;
        }

        if (player.row == key.row && player.col == key.col && key.visible && !key.collected) {
            key.collected = 1;
            door.opened = 1;
            key.visible = 0;
        }

        if (player.row == door.row && player.col == door.col && door.opened) {
            // Vá para a fase 2
            printf("Você passou para a próxima fase!\n");
            getch();
            initializePhase2(); // Chamada para a fase 2
            return;
        }

        if (player.row == enemy.row && player.col == enemy.col) {
            printf("Game Over!\n");
            getch();
            return;
        }

        if (player.row == spike.row && player.col == spike.col) {
            printf("Você tocou em um espinho!\n");
            restartCount++;
            if (restartCount >= 3) {
                printf("Você tocou em espinhos 3 vezes. Reiniciando o jogo...\n");
                getch();
                return;
            }
        }
    }
}

void initializePhase2() {
    struct Player player = {1, 1};
    struct Enemy enemy1 = {ROWS_PHASE_2 - 2, COLS_PHASE_2 - 2};
    struct Enemy enemy2 = {ROWS_PHASE_2 - 3, COLS_PHASE_2 - 3};
    struct Enemy chasingEnemy = {ROWS_PHASE_2 - 4, COLS_PHASE_2 - 4};
    struct Key key = {rand() % (ROWS_PHASE_2 - 2) + 1, rand() % (COLS_PHASE_2 - 2) + 1, 0, 0};
    struct Door door = {ROWS_PHASE_2 - 2, 1, 0};
    struct Spike spikes[8];
    struct Button button;
    int i;
    int restartCount = 0;

    // Define a posição dos espinhos dentro da matriz 20x20
    for (i = 0; i < 8; i++) {
        do {
            spikes[i].row = rand() % (ROWS_PHASE_2 - 2) + 1;
            spikes[i].col = rand() % (COLS_PHASE_2 - 2) + 1;
        } while (spikes[i].row == player.row && spikes[i].col == player.col ||
                 spikes[i].row == enemy1.row && spikes[i].col == enemy1.col ||
                 spikes[i].row == enemy2.row && spikes[i].col == enemy2.col ||
                 spikes[i].row == chasingEnemy.row && spikes[i].col == chasingEnemy.col ||
                 spikes[i].row == door.row && spikes[i].col == door.col ||
                 spikes[i].row == key.row && spikes[i].col == key.col);
    }

    // Define a posição do botão dentro da matriz 20x20
    do {
        button.row = rand() % (ROWS_PHASE_2 - 2) + 1;
        button.col = rand() % (COLS_PHASE_2 - 2) + 1;
    } while (button.row == player.row && button.col == player.col ||
             button.row == enemy1.row && button.col == enemy1.col ||
             button.row == enemy2.row && button.col == enemy2.col ||
             button.row == chasingEnemy.row && button.col == chasingEnemy.col ||
             button.row == door.row && button.col == door.col ||
             button.row == key.row && button.col == key.col);

    button.pressed = 0;

    char input;
    while (1) {
        displayPhase2(player, enemy1, enemy2, chasingEnemy, key, door, spikes, 8, button);
        input = getch();
        switch (input) {
            case 'w':
            case 'W':
                if (player.row > 1)
                    player.row--;
                break;
            case 'a':
            case 'A':
                if (player.col > 1)
                    player.col--;
                break;
            case 's':
            case 'S':
                if (player.row < ROWS_PHASE_2 - 2)
                    player.row++;
                break;
            case 'd':
            case 'D':
                if (player.col < COLS_PHASE_2 - 2)
                    player.col++;
                break;
            case 'q':
            case 'Q':
                return;
            case 'i':
            case 'I':
                if (player.row == button.row && player.col == button.col) {
                    button.pressed = 1;
                    key.visible = 1;
                }
                break;
            default:
                break;
        }

        // Movimentação aleatória dos inimigos
        int randomMove1 = rand() % 4;
        switch (randomMove1) {
            case 0:
                if (enemy1.row > 1)
                    enemy1.row--;
                break;
            case 1:
                if (enemy1.row < ROWS_PHASE_2 - 2)
                    enemy1.row++;
                break;
            case 2:
                if (enemy1.col > 1)
                    enemy1.col--;
                break;
            case 3:
                if (enemy1.col < COLS_PHASE_2 - 2)
                    enemy1.col++;
                break;
            default:
                break;
        }

        int randomMove2 = rand() % 4;
        switch (randomMove2) {
            case 0:
                if (enemy2.row > 1)
                    enemy2.row--;
                break;
            case 1:
                if (enemy2.row < ROWS_PHASE_2 - 2)
                    enemy2.row++;
                break;
            case 2:
                if (enemy2.col > 1)
                    enemy2.col--;
                break;
            case 3:
                if (enemy2.col < COLS_PHASE_2 - 2)
                    enemy2.col++;
                break;
            default:
                break;
        }

        // Movimentação do inimigo que persegue o jogador
        if (chasingEnemy.row < player.row) {
            chasingEnemy.row++;
        } else if (chasingEnemy.row > player.row) {
            chasingEnemy.row--;
        } else if (chasingEnemy.col < player.col) {
            chasingEnemy.col++;
        } else if (chasingEnemy.col > player.col) {
            chasingEnemy.col--;
        }

        if (player.row == key.row && player.col == key.col && key.visible && !key.collected) {
            key.collected = 1;
            door.opened = 1;
            key.visible = 0;
        }

        if (player.row == door.row && player.col == door.col && door.opened) {
            // Vá para a fase 3
            printf("Você passou para a próxima fase!\n");
            getch();
            initializePhase3(); // Chamada para a fase 3
            return;
        }

        for (i = 0; i < 8; i++) {
            if (player.row == spikes[i].row && player.col == spikes[i].col) {
                printf("Você tocou em um espinho!\n");
                restartCount++;
                if (restartCount >= 3) {
                    printf("Você tocou em espinhos 3 vezes. Reiniciando o jogo...\n");
                    getch();
                    return;
                }
            }
        }

        if (player.row == enemy1.row && player.col == enemy1.col ||
            player.row == enemy2.row && player.col == enemy2.col ||
            player.row == chasingEnemy.row && player.col == chasingEnemy.col) {
            printf("Game Over!\n");
            getch();
            return;
        }
    }
}

void initializePhase3() {
    struct Player player = {1, 1};
    struct Enemy enemies[8];
    struct Enemy chasingEnemy = {ROWS_PHASE_3 - 4, COLS_PHASE_3 - 4};
    struct Key key = {rand() % (ROWS_PHASE_3 - 2) + 1, rand() % (COLS_PHASE_3 - 2) + 1, 0, 0};
    struct Door door = {ROWS_PHASE_3 - 2, 1, 0};
    struct Spike spikes[20];
    struct Button button;
    int i, j;
    int restartCount = 0;

    // Define a posição dos espinhos dentro da matriz 40x40
    for (i = 0; i < 20; i++) {
        do {
            spikes[i].row = rand() % (ROWS_PHASE_3 - 2) + 1;
            spikes[i].col = rand() % (COLS_PHASE_3 - 2) + 1;
        } while (spikes[i].row == player.row && spikes[i].col == player.col ||
                 spikes[i].row == chasingEnemy.row && spikes[i].col == chasingEnemy.col ||
                 spikes[i].row == door.row && spikes[i].col == door.col ||
                 spikes[i].row == key.row && spikes[i].col == key.col);
    }

    // Define a posição dos inimigos dentro da matriz 40x40
    for (i = 0; i < 8; i++) {
        do {
            enemies[i].row = rand() % (ROWS_PHASE_3 - 2) + 1;
            enemies[i].col = rand() % (COLS_PHASE_3 - 2) + 1;
        } while (enemies[i].row == player.row && enemies[i].col == player.col ||
                 enemies[i].row == chasingEnemy.row && enemies[i].col == chasingEnemy.col ||
                 enemies[i].row == door.row && enemies[i].col == door.col ||
                 enemies[i].row == key.row && enemies[i].col == key.col ||
                 enemies[i].row == button.row && enemies[i].col == button.col);
    }

    // Define a posição do botão dentro da matriz 40x40
    do {
        button.row = rand() % (ROWS_PHASE_3 - 2) + 1;
        button.col = rand() % (COLS_PHASE_3 - 2) + 1;
    } while (button.row == player.row && button.col == player.col ||
             button.row == chasingEnemy.row && button.col == chasingEnemy.col ||
             button.row == door.row && button.col == door.col ||
             button.row == key.row && button.col == key.col);

    button.pressed = 0;

    char input;
    while (1) {
        displayPhase3(player, enemies, 8, chasingEnemy, key, door, spikes, 20, button);
        input = getch();
        switch (input) {
            case 'w':
            case 'W':
                if (player.row > 1)
                    player.row--;
                break;
            case 'a':
            case 'A':
                if (player.col > 1)
                    player.col--;
                break;
            case 's':
            case 'S':
                if (player.row < ROWS_PHASE_3 - 2)
                    player.row++;
                break;
            case 'd':
            case 'D':
                if (player.col < COLS_PHASE_3 - 2)
                    player.col++;
                break;
            case 'q':
            case 'Q':
                return;
            case 'i':
            case 'I':
                if (player.row == button.row && player.col == button.col) {
                    button.pressed = 1;
                    key.visible = 1;
                }
                break;
            default:
                break;
        }

        // Movimentação aleatória dos inimigos
        for (i = 0; i < 8; i++) {
            int randomMove = rand() % 4;
            switch (randomMove) {
                case 0:
                    if (enemies[i].row > 1)
                        enemies[i].row--;
                    break;
                case 1:
                    if (enemies[i].row < ROWS_PHASE_3 - 2)
                        enemies[i].row++;
                    break;
                case 2:
                    if (enemies[i].col > 1)
                        enemies[i].col--;
                    break;
                case 3:
                    if (enemies[i].col < COLS_PHASE_3 - 2)
                        enemies[i].col++;
                    break;
                default:
                    break;
            }
        }

        // Movimentação do inimigo que persegue o jogador
        if (chasingEnemy.row < player.row) {
            chasingEnemy.row++;
        } else if (chasingEnemy.row > player.row) {
            chasingEnemy.row--;
        } else if (chasingEnemy.col < player.col) {
            chasingEnemy.col++;
        } else if (chasingEnemy.col > player.col) {
            chasingEnemy.col--;
        }

        if (player.row == key.row && player.col == key.col && key.visible && !key.collected) {
            key.collected = 1;
            door.opened = 1;
            key.visible = 0;
        }

        if (player.row == door.row && player.col == door.col && door.opened) {
            // Jogador venceu o jogo
            printf("Você venceu o jogo!\n");
            getch();
            return;
        }

        for (i = 0; i < 20; i++) {
            if (player.row == spikes[i].row && player.col == spikes[i].col) {
                printf("Você tocou em um espinho!\n");
                restartCount++;
                if (restartCount >= 3) {
                    printf("Você tocou em espinhos 3 vezes. Reiniciando o jogo...\n");
                    getch();
                    return;
                }
            }
        }

        for (i = 0; i < 8; i++) {
            if (player.row == enemies[i].row && player.col == enemies[i].col) {
                printf("Game Over!\n");
                getch();
                return;
            }
        }

        if (player.row == chasingEnemy.row && player.col == chasingEnemy.col) {
            printf("Game Over!\n");
            getch();
            return;
        }
    }
}

void displayTutorial() {
    clearScreen();
    printf("TUTORIAL\n");
    printf("W - Mover para cima\n");
    printf("A - Mover para esquerda\n");
    printf("S - Mover para baixo\n");
    printf("D - Mover para direita\n");
    printf("Q - Sair do jogo\n");
    printf("I - Interagir com objetos\n");
    printf("Pressione qualquer tecla para voltar ao menu principal.\n");
    getch();
}

int main() {
    srand(time(0));
    enum Phase currentPhase = MAIN_MENU;

    while (1) {
        switch (currentPhase) {
            case MAIN_MENU:
                displayMainMenu();
                char choice = getch();
                if (choice == '1') {
                    currentPhase = PHASE_1;
                } else if (choice == '2') {
                    displayTutorial();
                } else if (choice == '3') {
                    return 0;
                }
                break;
            case PHASE_1:
                initializePhase1();
                currentPhase = MAIN_MENU;
                break;
            case PHASE_2:
                initializePhase2();
                currentPhase = MAIN_MENU;
                break;
            case PHASE_3:
                initializePhase3();
                currentPhase = MAIN_MENU;
                break;
            default:
                break;
        }
    }

    return 0;
}

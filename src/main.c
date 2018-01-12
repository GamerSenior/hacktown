#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <menu.h>
#include <pthread.h>

#define WIDTH 30
#define HEIGHT 10
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void configuracoes();
void inicializaTela();
void menuInicial(WINDOW *menu_win, int selecao);
void *inputControl(void *data);

int startx = 0;
int starty = 0;

char *opcoesMenu[] = {
    "Novo Jogo",
    "Continuar",
    "Creditos",
    "Sair",
};

int main(){
    //WINDOW* menu_win;
    ITEM **itens;
    int c;
    MENU *menu;
    int n_escolhas, i;
    ITEM *item_atual;
    bool gameRunning = false;
    pthread_t tid;

    inicializaTela();

    n_escolhas = ARRAY_SIZE(opcoesMenu);
    itens = (ITEM **)calloc(n_escolhas, sizeof(ITEM *));

    for(i = 0; i < n_escolhas; ++i){
        itens[i] = new_item(opcoesMenu[i], "");
    }
    itens[n_escolhas] = (ITEM *)NULL;

    menu = new_menu((ITEM **) itens);
    mvprintw(LINES - 2, 0, "Q para Sair");
    post_menu(menu);
    refresh();

    while((c = getch()) != 'q' && !gameRunning){
        switch(c){
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                if(current_item(menu) == itens[0]){
                    gameRunning = true;
                }            
                break;
            case KEY_LEFT:
                set_current_item(menu, itens[0]);
                break;
        }
    }

    pthread_create(&tid, NULL, inputControl,(void*)c);
    while(gameRunning){
        clear();
        
        mvprintw(LINES - 2, 0, "%c Wubba Lubba Dub Dub", c);
        refresh();
    }

    //Libera a memoria alocada pelo menu
    unpost_menu(menu);
    free_menu(menu);
    for(i = 0; i < n_escolhas; ++i){
        free_item(itens[i]);
    }

    //Finaliza o modo curses e libera a memoria
    endwin();
    
    return 0;
}

void configuracoes(){
    FILE *config;

    config = fopen("game.conf", "r");
    //Se não foi possivel ler as configurações
    if(!config){
        //Cria arquivo configurações
        config = fopen("game.conf", "w+");
        if(!config){
            printw("Não foi possivel criar o arquivo de configuração!");
        }else{
            printw("Arquivo de configurações criado com sucesso!");
        }
    }else{
        printw("Arquivo de configurações lido com sucesso!");
    }
    refresh();
    getch();
    clear();
}

void inicializaTela(){
    //Inicializa o terminal no modo curses.    
    initscr();
    configuracoes();
    //raw();
    noecho();

    //Buffer de linha desligado
    cbreak();
    
    //Libera a utilização de teclas funcionais como F1, F2 e setas
    keypad(stdscr, TRUE);
}

void *inputControl(void *data){
    int c = (intptr_t) data;
    printw("%c", c);
}
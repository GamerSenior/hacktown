#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 30
#define HEIGHT 10

void configuracoes();
void inicializaTela();
void menuInicial(WINDOW *menu_win, int selecao);
void inputControl();

char *opcoesMenu[] = {
    "Novo Jogo",
    "Continuar",
    "Créditos",
    "Sair",
};
int n_opcoes = sizeof(opcoesMenu) / sizeof( char *);

int main(){
    WINDOW* menu_win;
    int selecao = 1;
    int escolha = 0;
    int c;

    menu_win = newwin(HEIGHT, WIDTH, 0, 0);

    inicializaTela(); 
    menuInicial(menu_win, selecao);
    getch();

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
    sleep(5);
}

void inicializaTela(){
    //Inicializa o terminal no modo curses.    
    initscr();
    configuracoes();
    //raw();
    //noecho();
    cbreak();
    
    //Libera a utilização de teclas funcionais como F1, F2 e setas
    keypad(stdscr, TRUE);
}

void menuInicial(WINDOW *menu_win, int selecao){
    clear();
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);

    mvwprintw(menu_win, 0, 2, "HackTown version 0.1\n");
    
    for(i = 0; i < n_opcoes; ++i){
        if(selecao == i + 1){
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", opcoesMenu[i]);
            wattroff(menu_win, A_REVERSE);
        }else{
            mvwprintw(menu_win, y, x, "%s", opcoesMenu[i]);
        }
        ++y;
    }
    wrefresh(menu_win);



    //Atualiza a tela (stdscr) com novos dados    
    refresh();
    getch();
}

void inputControl(){

}
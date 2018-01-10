#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void configuracoes();
void inicializaTela();
void menuInicial();

int main(){
    inicializaTela();    
    menuInicial();
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
    
    //Libera a utilização de teclas funcionais como F1, F2 e setas
    keypad(stdscr, TRUE);
}

void menuInicial(){
    clear();

    printw("HackTown version 0.1\n");

    //Atualiza a tela (stdscr) com novos dados    
    refresh();
    getch();
}
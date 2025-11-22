#include "menu.h"
#include <locale>
#include <iostream>

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");

    menuPrincipal();

    delete p1;
    delete inimigo;

    return 0;
}
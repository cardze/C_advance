#include "ui.h"
#include "list.h"

int main(void){
    tNumStorHead *list;
    list = init_list();
    while (1)
    {
        ui_main_menu(list);
    }
}
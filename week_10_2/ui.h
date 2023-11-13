#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void ui_main_menu(tNumStorHead *list);
void add_number_to_list(tNumStorHead *list);
void delete_number_on_list(tNumStorHead *list);
void print_list(tNumStorHead *list);


// not implemented
void ui_add_menu();
void ui_get_add_lacation();
void ui_del_menu();
int ui_get_del_location();

#endif
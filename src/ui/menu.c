//
//  menu.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "menu.h"

#ifndef IGNOREINTESTS
#include "../../src-lib/lcd/lcd.h"
#endif

/**
 * initialize the menu
 */
void ui_menu_init(void){
    menu = malloc(sizeof(menu_t));
    menuentry_t *entry = malloc(sizeof (menuentry_t));
    entry->position = -1;
    
    entry->data = "NO ENTRY";

    // loop around
    entry->next = entry;
    
    menu->firstentry = entry;
    menu->lastentry = entry;
    
    active = entry;
}

/**
 * add a item to the bottom of the menu
 */
menuentry_t *ui_menu_add(char* data, void* fn){
    // get the last entry number
    menuentry_t *last = menu->lastentry;
    int lastposition = last->position;

    if( lastposition > -1){
        // if this should be a sub item
        // create a new item
        menuentry_t *entry = malloc(sizeof (menuentry_t));
        
        entry->position = ++lastposition;
        entry->data = data;
        entry->fn = fn;
        entry->next = menu->firstentry;
        
        last->next = entry;
        menu->lastentry = entry;
        
        return entry;
    } else {
        // if this should be the first item?
        last->data = data;
        last->fn = fn;
        last->position = 0;
        return last;
    }
}

/**
 * add a sub item to the bottom of the submenu
 */
menuentry_t *ui_menu_add_sub(menuentry_t *parent, char* data, void* fn){
    menuentry_t *this;
    menuentry_t *last;

    this = (menuentry_t *)parent->submenu;
    last = this;
    
    while(this != NULL){
        last = this;
        this = this->submenu;
    }

    this = malloc(sizeof (menuentry_t));
    this->data = data;
    this->fn = fn;
    this->next = parent->submenu;
    if(this->next == NULL){ this->next = this; }
    this->parent = parent;
    
    if(last == NULL){
        memcpy(&parent->submenu, &this, sizeof(this));
    } else {
        memcpy(&last->next, &this, sizeof(this));
    }
    return this;
}


/**
 * Move down the menu and set the next element active
 */
void ui_menu_next(void){
    active = active->next;
}

/**
 * returns TRUE if this item hast a submenu
 */
bool ui_menu_has_submenu(void){
    if(active->submenu != NULL){
        return true;
    }
    return false;
}

/**
 * going into a submenu of the current entry
 */
void ui_menu_enter_submenu(void){
    if(active->submenu != NULL){
        active = active->submenu;
    }
}

/**
 * Leaving the current submenu and go back to the parent entry
 */
void ui_menu_leave_submenu(void){
    if(active->parent != NULL){
        active = active->parent;
    }
}

/**
 * Show the current active item on the lcd
 */
void ui_menu_show(void){
#ifndef IGNOREINTESTS
    lcd_clrscr();
    lcd_puts(active->data);
#endif
}

void ui_menu_run(void){
#ifndef IGNOREINTESTS
    LIGHT_TOGGLE(LED_GREEN);
    lcd_clrscr();
    active->fn();
#endif
}




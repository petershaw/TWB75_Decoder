//
//  menu.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#ifndef AnalyserDude_menu_h
#define AnalyserDude_menu_h

/**
 * Represents a single element in the menu.
 */
typedef struct menuentry {
    int position;
    struct menuentry *next;     // pointer to the next entry
    struct menuentry *parent;   // pointer to the parent entry
    struct menuentry *submenu;  // submenu of this item
    char *data;                 // the raw data string to show
    void (*fn)();               // function to execute at startup
} menuentry_t;

/**
 * Represents a menu.
 */
typedef struct menustruc {
    menuentry_t *firstentry;
    menuentry_t *lastentry;
} menu_t;

menu_t *menu;

menuentry_t *active;

void ui_menu_init(void);
menuentry_t *ui_menu_add(char*, void*);
menuentry_t *ui_menu_add_sub(menuentry_t *parent, char*, void*);
void ui_menu_next(void);
bool ui_menu_has_submenu(void);
void ui_menu_enter_submenu(void);
void ui_menu_leave_submenu(void);
void ui_menu_show(void);
void ui_menu_run(void);

#endif

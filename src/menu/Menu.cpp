#include "Menu.hpp"
#include "Orange.h"

Menu *Menu::menu = NULL;
Menu *Menu::getMenu() {
	if (menu == NULL) {
		menu = new Menu();
	}
	return menu;
}

Menu::Menu() {
    lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_tabview_set_sliding(tabview, false);

    tabInfo = lv_tabview_add_tab(tabview, "Info");
    tabDebug = lv_tabview_add_tab(tabview, "Debug");
    tabYus = lv_tabview_add_tab(tabview, "yus");
    
    lv_obj_t *label = lv_label_create(tabInfo, NULL);
    lv_label_set_text(label, "help");

    lv_obj_t * yus = lv_img_create(tabYus, NULL);
    lv_img_set_src(yus, &orange);
}
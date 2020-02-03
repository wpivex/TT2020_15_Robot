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
    constructTabview();
    constructDebugPage();

    
    lv_obj_t *label = lv_label_create(tabInfo, NULL);
    lv_label_set_text(label, "help");
    #ifdef BLUE
    lv_label_set_text(label, "You are on blue.");
    #endif
    #ifdef RED
    lv_label_set_text(label, "You are on red.");
    #endif
}

void Menu::printTerminal(const char* str, const char end) {

}


void Menu::addYus() {
    tabYus = lv_tabview_add_tab(tabview, "yus");
    // lv_obj_t *yus = lv_img_create(tabYus, NULL);
    // lv_img_set_src(yus, &orange);
}

void Menu::constructTabview() {
    lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_tabview_set_sliding(tabview, false);

    // Create tabs
    tabInfo = lv_tabview_add_tab(tabview, "Info");
    tabDebug = lv_tabview_add_tab(tabview, "Debug");
    tabTerminal = lv_tabview_add_tab(tabview, "Terminal");


    tabYus = lv_tabview_add_tab(tabview, "yus");
    lv_obj_t *yus = lv_img_create(tabYus, NULL);
    lv_img_set_src(yus, &orange);

    // Style the tab buttons
    static lv_style_t tabButtonStyle;
    lv_style_copy(&tabButtonStyle, &lv_style_btn_tgl_rel);
    tabButtonStyle.body.padding.ver = 8;
    tabButtonStyle.body.radius = 0;
    tabButtonStyle.body.main_color = LV_COLOR_MAKE(0x72,0x72,0x72);
    tabButtonStyle.body.grad_color = LV_COLOR_MAKE(0x72,0x72,0x72);
    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &tabButtonStyle);
    static lv_style_t highlightedTabButtonStyle;
    lv_style_copy(&highlightedTabButtonStyle, &lv_style_plain_color);
    highlightedTabButtonStyle.body.padding.inner = 2;
    highlightedTabButtonStyle.body.main_color = LV_COLOR_ORANGE;
    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_INDIC, &highlightedTabButtonStyle);
}

void Menu::constructDebugPage() {
    debugTextArea = lv_ta_create(tabTerminal, NULL);
    lv_ta_set_cursor_type(debugTextArea, LV_CURSOR_NONE);
    lv_ta_add_text(debugTextArea, "line 1\n");
    lv_ta_add_text(debugTextArea, "line 2\n");
    lv_ta_add_text(debugTextArea, "line 3\n");
}
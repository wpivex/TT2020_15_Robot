#pragma once
#include "main.h"

class Menu {
    private:
        Menu();
        static Menu* menu;
        lv_obj_t *tabview;
        
        lv_obj_t *tabInfo;
        lv_obj_t *tabDebug;
        lv_obj_t *tabYus;
    public:
        static Menu* getMenu();
};
#pragma once
#include "main.h"

class Menu {
    private:
        Menu();
        static Menu* menu;
        lv_obj_t *tabview;
        
        lv_obj_t *tabInfo;
        lv_obj_t *tabDebug;
        lv_obj_t *tabTerminal;
        lv_obj_t *tabYus;

        lv_obj_t *debugTextArea;
        int numTerminalLines = 0;
        void constructTerminalPage();
        void constructYusPage();
        void constructTabview();
    public:
        static Menu* getMenu();
        void printTerminal(const char* str, const char end='\n');
        void addDebugListener(int id, const char* str);
};
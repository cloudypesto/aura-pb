#pragma once
#include "liblvgl/llemu.hpp"

// ================= AUTON ENUM =================

enum class Auton {
    NONE,
    LEFT_HIGH_SCORE,
    LEFT_RUSH,
    RIGHT_SCORE,
    SKILLS
};

// ================= COLOR CONFIGURATION =================

struct AutonColors {
    lv_color_t bg_color;           // Background color
    lv_color_t btn_normal;         // Normal button color
    lv_color_t btn_selected;       // Selected button color
    lv_color_t btn_text_normal;    // Normal text color
    lv_color_t btn_text_selected;  // Selected text color
};

//call once in initialize()
void auton_selector_init();

//initialize with custom colors
void auton_selector_init_colors(const AutonColors& colors);

//get the selected auton
Auton auton_selector_get();

//get name for printing/logging
const char* auton_selector_get_name();

// Change colors at runtime
void auton_selector_set_bg_color(lv_color_t color);
void auton_selector_set_btn_color(lv_color_t normal, lv_color_t selected);
void auton_selector_set_text_color(lv_color_t normal, lv_color_t selected);
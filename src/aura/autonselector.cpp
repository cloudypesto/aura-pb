#include "autonselector.hpp"
#include <cstring>
#include <cstdint>

#include "aura/devices.hpp"


//how to use auto selector

//option 1 
//auton_selector_init(); 
//this uses the all of the basic colours

//option 2
//define the colours first
// AutonColors custom = {
//     .bg_color = lv_color_hex(0x000033),        // Dark blue
//     .btn_normal = lv_color_hex(0x666666),      // Gray
//     .btn_selected = lv_color_hex(0xff6600),    // Orange
//     .btn_text_normal = lv_color_hex(0xffffff), // White
//     .btn_text_selected = lv_color_hex(0x000000) // Black
// };
// auton_selector_init_colors(custom);

//option 3
//change the colours after
// auton_selector_set_bg_color(lv_color_hex(0x1a0033)); // Purple bg
// auton_selector_set_btn_color(
//     lv_color_hex(0x404040),  // Normal: gray
//     lv_color_hex(0xff0000)   // Selected: red
// );








// ================= INTERNAL STATE =================

static constexpr int AUTON_COUNT = 5;

static const char* auton_names[AUTON_COUNT] = {
    "NONE",
    "LEFT HIGH SCORE",
    "RIGHT RUSH",
    "LEFT ",
    "SKILLS"
};

static Auton selected_auton = Auton::LEFT_HIGH_SCORE;
static int selected_index = 1;

static lv_obj_t* auton_screen = nullptr;
static lv_obj_t* auton_buttons[AUTON_COUNT] = {nullptr};

// Default color scheme
static AutonColors current_colors = {
    .bg_color = lv_color_hex(0x1a1a1a),           // Dark gray background
    .btn_normal = lv_color_hex(0x404040),         // Medium gray
    .btn_selected = lv_color_hex(0x00aa00),       // Green
    .btn_text_normal = lv_color_hex(0xffffff),    // White
    .btn_text_selected = lv_color_hex(0xffffff)   // White
};

// ================= HELPER FUNCTIONS =================

static void update_button_styles() {
    for (int i = 0; i < AUTON_COUNT; i++) {
        if (auton_buttons[i] == nullptr) continue;
        
        bool is_selected = (i == selected_index);
        
        // Update button background color
        lv_obj_set_style_bg_color(
            auton_buttons[i],
            is_selected ? current_colors.btn_selected : current_colors.btn_normal,
            LV_PART_MAIN
        );
        
        // Update text color
        lv_obj_t* label = lv_obj_get_child(auton_buttons[i], 0);
        if (label) {
            lv_obj_set_style_text_color(
                label,
                is_selected ? current_colors.btn_text_selected : current_colors.btn_text_normal,
                LV_PART_MAIN
            );
        }
    }
}

// ================= EVENT HANDLER =================

static void auton_btn_event(lv_event_t* e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;

    int btn_index = reinterpret_cast<intptr_t>(lv_event_get_user_data(e));
    
    selected_index = btn_index;
    selected_auton = static_cast<Auton>(btn_index);
    
    update_button_styles();

    Controller.clear_line(0); 
    pros::delay(50); // Required delay for controller message queue
    
    // Print the name of the selected auton
    Controller.print(0, 0, "Auton: %s", auton_names[selected_index]);
    
    pros::delay(50); 
    Controller.rumble(".");
}

// ================= UI CREATION =================

static lv_obj_t* create_auton_button(
    lv_obj_t* parent,
    const char* text,
    int x,
    int y,
    int width,
    int height,
    int index
) {
    lv_obj_t* btn = lv_button_create(parent);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_pos(btn, x, y);
    
    // Set rounded corners
    lv_obj_set_style_radius(btn, 8, LV_PART_MAIN);
    
    // Add event callback
    lv_obj_add_event_cb(
        btn,
        auton_btn_event,
        LV_EVENT_CLICKED,
        reinterpret_cast<void*>(static_cast<intptr_t>(index))
    );

    // Create label
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_center(label);
    
    // Enable text wrapping for long names
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, width - 10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    return btn;
}

static void create_grid_layout() {
    // Grid configuration
    const int btn_width = 140;
    const int btn_height = 60;
    const int spacing_x = 20;
    const int spacing_y = 20;
    const int start_x = 20;
    const int start_y = 60;
    const int cols = 3;
    
    // Create title label
    lv_obj_t* title = lv_label_create(auton_screen);
    lv_label_set_text(title, "Select Autonomous");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // Create buttons in grid
    for (int i = 0; i < AUTON_COUNT; i++) {
        int row = i / cols;
        int col = i % cols;
        
        int x = start_x + col * (btn_width + spacing_x);
        int y = start_y + row * (btn_height + spacing_y);
        
        auton_buttons[i] = create_auton_button(
            auton_screen,
            auton_names[i],
            x,
            y,
            btn_width,
            btn_height,
            i
        );
    }
}

// ================= PUBLIC FUNCTIONS =================

void auton_selector_init() {
    auton_selector_init_colors(current_colors);
}

void auton_selector_init_colors(const AutonColors& colors) {
    current_colors = colors;
    
    auton_screen = lv_screen_active();
    
    // Set background color
    lv_obj_set_style_bg_color(auton_screen, current_colors.bg_color, LV_PART_MAIN);
    
    // Create the grid layout
    create_grid_layout();
    
    // Apply initial styles
    update_button_styles();
}

Auton auton_selector_get() {
    return selected_auton;
}

const char* auton_selector_get_name() {
    return auton_names[static_cast<int>(selected_auton)];
}

void auton_selector_set_bg_color(lv_color_t color) {
    current_colors.bg_color = color;
    if (auton_screen) {
        lv_obj_set_style_bg_color(auton_screen, color, LV_PART_MAIN);
    }
}

void auton_selector_set_btn_color(lv_color_t normal, lv_color_t selected) {
    current_colors.btn_normal = normal;
    current_colors.btn_selected = selected;
    update_button_styles();
}

void auton_selector_set_text_color(lv_color_t normal, lv_color_t selected) {
    current_colors.btn_text_normal = normal;
    current_colors.btn_text_selected = selected;
    update_button_styles();
}
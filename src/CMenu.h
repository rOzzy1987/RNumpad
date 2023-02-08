#ifndef C_MENU
#define C_MENU

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C

#define KNOB_MEDIA 0
#define KNOB_VOLUME 1
#define KNOB_BACKLIGHT 2 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

struct MenuDisplayConfig {
    char lineHeight;
    char lineCount;
    char yOffset;
    GFXfont* font;
    char* displayName;
};

struct MenuDisplayMenu {
    char count;
    char* items[6];
};

class CMenu {
    public:
        int brightness = 255;
        char backlightEnabled = 1;
        char knobBehavior = 0;
        char backlightSleepMinutes = 10;

        void setKeyboardStatus(char leds) { this->_ledState = leds; this->renderScreen(); };
        CMenu();
        void initMenu(){
            this->_display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
            this->renderScreen();
        };
        void tick(char rotation, char buttonPress);
        bool isActive() { return _menuScreen != -1; };
    private:
        Adafruit_SSD1306* _display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

        // -1 - Logo screen
        // 0 - Main Menu
        // 1 - Knob
        // 2 - Backlight
        // 3 - Font
        char _menuScreen = -1;
        char _menuItem = 0;
        char _scroll = 0;
        char _settingItem = -1;
        MenuDisplayMenu __menu0, __menu1, __menu2, __menu3;
        MenuDisplayMenu _menu[4];

        unsigned long _lastActivity;

        MenuDisplayConfig _config[6];
        char _activeConfig = 0;

        char _ledState = 7;

        void renderScreen();
        void menuNavigation(char rot, char btn);
        void renderMenu() { this->renderMenu(1); };
        void renderMenu(char draw);
        void jumpToScreen(char screen) { this->jumpToScreen(screen, 0); };
        void jumpToScreen(char screen, char item);
        void drawLogo();
        void drawBacklightMenu();
        char getTextWidth(char* text);
};

#endif
#include "CMenu.h"
#include "bitmaps.h"
#include "DefaultFont.h"
#include "LargeFont.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

CMenu::CMenu()  {
//////// DISPLAY CONFIG ////////
    MenuDisplayConfig cfg0 = *(new MenuDisplayConfig());
    cfg0.displayName = "Default";
    cfg0.lineHeight = 11;
    cfg0.lineCount = SCREEN_HEIGHT / cfg0.lineHeight;
    cfg0.yOffset = 9;
    cfg0.font = &DefaultFont;
    
    MenuDisplayConfig cfg1;
    cfg1.displayName = "Large";
    cfg1.lineHeight = 14;
    cfg1.lineCount = SCREEN_HEIGHT / cfg1.lineHeight;
    cfg1.yOffset = 10;
    cfg1.font = &LargeFont;
    
    // MenuDisplayConfig cfg2;
    // cfg2.displayName = "Micro";
    // cfg2.lineHeight = 8;
    // cfg2.lineCount = SCREEN_HEIGHT / cfg2.lineHeight;
    // cfg2.yOffset = 16;
    // cfg2.font = &MicroFont;
    
    this->_config[0] = cfg0;
    this->_config[1] = cfg1;
    char configLength = 2;
    // this->_config[2] = cfg2;

//////// MENU ITEMS ////////
    __menu0.items[0] = "Knob function";
    __menu0.items[1] = "Backlight setup";
    __menu0.items[2] = "Select Font";
    __menu0.items[3] = "Debug";
    __menu0.count = 4;

    __menu1.items[0] = "Media < / >";
    __menu1.items[1] = "Volume { / }";
    __menu1.items[2] = "Backlight [ / ]";
    __menu1.count = 3;

    __menu2.items[0] = "Power";
    __menu2.items[1] = "Brightness";
    __menu2.items[2] = "Sleep";
    __menu2.count = 3;

    for(int i = 0; i < configLength; i++)
        __menu3.items[i] = this->_config[i].displayName;
    __menu3.count = configLength;

    this->_menu[0] = __menu0;
    this->_menu[1] = __menu1;
    this->_menu[2] = __menu2;
    this->_menu[3] = __menu3;
}

void CMenu::renderScreen(){
    switch(this->_menuScreen){
    case -1:
        this->drawLogo();
        return;
    case 2:
        this->drawBacklightMenu();
        return;
    }
    this->renderMenu();
}
void CMenu::menuNavigation(char rot, char btn) {
    if (!rot)
        return;

    MenuDisplayConfig config = this->_config[this->_activeConfig];
    MenuDisplayMenu menu = this->_menu[this->_menuScreen];

    if (rot > 0) this->_menuItem ++;
    if (rot < 0) this->_menuItem --;
    if (this->_menuItem < 0) this->_menuItem = 0;
    if (this->_menuItem >= menu.count) this->_menuItem = menu.count - 1;
    while (this->_menuItem - this->_scroll >= config.lineCount) this->_scroll++;
    while (this->_menuItem - this->_scroll < 0) this->_scroll--;
    this->renderScreen();
}
void CMenu::renderMenu(char draw){
    this->_display->clearDisplay();

    MenuDisplayConfig config = this->_config[this->_activeConfig];
    MenuDisplayMenu menu = this->_menu[this->_menuScreen];

    this->_display->setTextSize(1);             
    this->_display->setTextColor(SSD1306_WHITE);  

    this->_display->setFont(config.font);

    for (char i = this->_scroll; i < menu.count && i < this->_scroll + config.lineCount; i++){
        this->_display->setCursor(5,((i - this->_scroll) * config.lineHeight) + config.yOffset);            
        this->_display->println(menu.items[i]);
    } 

    //// scrollbar rendering
    // this->_display->fillRect(SCREEN_WIDTH -3, 0, 3, SCREEN_HEIGHT, SSD1306_BLACK);
    // int scrollBar = SCREEN_HEIGHT / menu.count;
    // this->_display->fillRect(SCREEN_WIDTH -3, this->_menuItem * scrollBar, 3, scrollBar, SSD1306_WHITE);

    this->_display->fillRect(0, (this->_menuItem - this->_scroll) * config.lineHeight, SCREEN_WIDTH -3, config.lineHeight, SSD1306_INVERSE);
    if (draw)
        this->_display->display();
}
void CMenu::jumpToScreen(char screen, char item){
    this->_menuScreen = screen;
    this->_menuItem = item;
    this->_settingItem = -1;
    this->renderScreen();
}
void CMenu::drawLogo() {
    this->_display->clearDisplay();

    this->_display->drawBitmap((SCREEN_WIDTH - LOGO_W) / 2, (SCREEN_HEIGHT - LOGO_H) / 2, rgndLogo, LOGO_W, LOGO_H, 1);
    if (this->_ledState & 0x01)
        this->_display->drawBitmap(0, SCREEN_HEIGHT - 10, numLockIcon, 10, 10, 1);
    if (this->_ledState & 0x02)
        this->_display->drawBitmap(12, SCREEN_HEIGHT - 10, capsLockIcon, 10, 10, 1);
    if (this->_ledState & 0x04)
        this->_display->drawBitmap(24, SCREEN_HEIGHT - 10, scrlLockIcon, 10, 10, 1);

    this->_display->display();
}
void CMenu::drawBacklightMenu(){
    this->renderMenu(0);

    MenuDisplayConfig config = this->_config[this->_activeConfig];
    // if (this->_settingItem == 0) {
        char w = 14;
        char h = 9;
        if (config.lineHeight < h + 2)
            h = config.lineHeight - 2;
        char o = (config.lineHeight - h) / 2;
        char k = this->backlightEnabled ? 7 : 2;
        this->_display->drawRect((SCREEN_WIDTH - w) - 5, config.lineHeight * (0 - this->_scroll) + o, w, h, SSD1306_INVERSE);
        this->_display->fillRect((SCREEN_WIDTH - w) + k -5, config.lineHeight * (0 - this->_scroll) + o + 2, 5, h - 4, SSD1306_INVERSE);
    // }
    // if (this->_settingItem == 1) {
        this->_display->drawRect(SCREEN_WIDTH - 39, config.lineHeight * (1 - this->_scroll) + 1, 35, config.lineHeight-2, SSD1306_INVERSE);
        this->_display->fillRect(SCREEN_WIDTH - 37, config.lineHeight * (1 - this->_scroll) + 3, this->brightness >> 3, config.lineHeight - 6, SSD1306_INVERSE);
    // }
    // if (this->_settingItem == 2) {
        char buf[5];
        sprintf(buf, "%dm", this->backlightSleepMinutes);
        char len = this->getTextWidth(buf);
        
        this->_display->setCursor(SCREEN_WIDTH - (len + 5), config.lineHeight * (2- this->_scroll) + config.yOffset);
        this->_display->setTextColor(SSD1306_INVERSE);
        this->_display->print(buf);
    // }

    this->_display->fillRect(1, config.lineHeight * this->_settingItem +1, 2, config.lineHeight - 2, SSD1306_BLACK);

    this->_display->display();
}
void CMenu::tick(char rot, char btn){
    unsigned long time = millis();

    if (time - this->_lastActivity > 5000 && this->_menuScreen != -1){
        this->jumpToScreen(-1);
    }

    switch (this->_menuScreen) {
        case -1: // LOGO
            if(btn >= 2) {
                this->jumpToScreen(0);
            }
            break;
        case 0: // Main
            if (btn >= 2){
                this->jumpToScreen(-1);
                break;
            }
            if (btn) {
                switch (this->_menuItem) {
                    case 0:
                        this->jumpToScreen(1, this->knobBehavior);
                        break;
                    case 1:
                        this->jumpToScreen(2);
                        break;
                    case 2:
                        this->jumpToScreen(3, this->_activeConfig);
                        break;
                    case 3:
                        break;
                }
                break;
            }
            this->menuNavigation(rot, btn);
            break;
        case 1: // Knob function
            if (btn >= 2){
                this->jumpToScreen(0);
                break;
            }
            if (btn) {
                this->knobBehavior = this->_menuItem;
                this->jumpToScreen(0);
                break;
            }
            this->menuNavigation(rot, btn);
            break;
        case 2: // Backlight config
            if (btn >= 2){
                jumpToScreen(0);
                break;
            }
            if (this->_settingItem == -1){
                if(btn) {
                    this->_settingItem = this->_menuItem;
                    this->renderScreen();
                    break;
                }
                this->menuNavigation(rot, btn);
            }
            if(this->_settingItem == 0)
            {
                if (btn) {
                    this->jumpToScreen(2, 0);
                    break;
                }
                if (rot) {
                    this->backlightEnabled = !this->backlightEnabled;
                    this->renderScreen();
                    break;
                }
            }
            if(this->_settingItem == 1)
            {
                if (btn) {
                    this->jumpToScreen(2, 0);
                    break;
                }
                if (rot) {
                    this->brightness += rot*16;
                    if (this->brightness > 255) this->brightness = 255;
                    if (this->brightness < 0) this->brightness = 0;
                    this->renderScreen();
                    break;
                }
            }
            if (this->_settingItem == 2){
                if (btn) {
                    this->jumpToScreen(2, 1);
                    break;
                }
                if (rot) {
                    this->backlightSleepMinutes += rot;
                    if (this->backlightSleepMinutes > 20) this->backlightSleepMinutes = 20;
                    if (this->backlightSleepMinutes < 0) this->backlightSleepMinutes = 0;
                    this->renderScreen();
                    break;
                }
            }
            break;
        case 3:
            if (btn >= 2){
                this->jumpToScreen(0);
                break;
            }
            if (btn) {
                this->_activeConfig = this->_menuItem;
                this->jumpToScreen(0);
                break;
            }
            this->menuNavigation(rot, btn);
            break;
    }

    if(rot != 0 || btn != 0) {
        this->_lastActivity = time;
    }
}

char CMenu::getTextWidth(char* text) {
    uint16_t w;
    uint16_t _;
    int16_t __;

    MenuDisplayConfig config = this->_config[this->_activeConfig];

    this->_display->setFont(config.font);
    this->_display->getTextBounds(text, 0, 0, &__, &__, &w, &_);
    
    return w;
}
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button GPIO pins
#define UP_BUTTON 12
#define DOWN_BUTTON 13
#define LEFT_BUTTON 14
#define RIGHT_BUTTON 27
#define ENTER_BUTTON 26

enum ScreenState { CLOCK, MENU };
ScreenState currentState = CLOCK;
unsigned long lastPressTime = 0;
int menuOption = 0;
const int numOptions = 4; // Number of menu options

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);

  setTime(14, 30, 0, 1, 1, 2023); // HH, MM, SS, D, M, Y

  showClock();
}

void loop() {
  if (digitalRead(LEFT_BUTTON) == LOW) { navigateLeft(); delay(200); }
  if (digitalRead(RIGHT_BUTTON) == LOW) { navigateRight(); delay(200); }
  if (digitalRead(ENTER_BUTTON) == LOW) { selectOption(); delay(200); }

  if (currentState == MENU && (millis() - lastPressTime > 5000)) {
    currentState = CLOCK;
    showClock();
  }

  if (currentState == CLOCK && (millis() % 1000 == 0)) {
    showClock();
  }
}

void showClock() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.printf("%02d:%02d", hour(), minute());
  display.display();
}

void showMenu() {
  display.clearDisplay();

  // Display centered main option in large font
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 20); // Centered position for main option

  // Display the main option
  switch (menuOption) {
    case 0: display.print("Main"); break;
    case 1: display.print("Menu"); break;
    case 2: display.print("Setting"); break;
    case 3: display.print("IP"); break;
  }

  // Display adjacent options as smaller squares
  display.setTextSize(1);
  int prevOption = (menuOption - 1 + numOptions) % numOptions;
  int nextOption = (menuOption + 1) % numOptions;

  // Left of center
  display.setCursor(5, 40);
  display.print(getOptionLabel(prevOption));

  // Right of center
  display.setCursor(100, 40);
  display.print(getOptionLabel(nextOption));

  display.display();
}

String getOptionLabel(int option) {
  switch (option) {
    case 0: return "Main";
    case 1: return "Menu";
    case 2: return "Set";
    case 3: return "IP";
    default: return "";
  }
}

void navigateLeft() {
  lastPressTime = millis();
  if (currentState == MENU) {
    menuOption = (menuOption > 0) ? menuOption - 1 : numOptions - 1;
    showMenu();
  }
}

void navigateRight() {
  lastPressTime = millis();
  if (currentState == MENU) {
    menuOption = (menuOption + 1) % numOptions;
    showMenu();
  }
}

void selectOption() {
  lastPressTime = millis();
  if (currentState == CLOCK) {
    currentState = MENU;
    menuOption = 0;  // Start with the first menu option
    showMenu();
  } else {
    // Action for selected option, if needed
  }
}

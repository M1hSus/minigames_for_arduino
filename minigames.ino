//The game code was written by MihSus. You may modify it, but not sell it. 
//Link to author's YouTube channel: https://www.youtube.com/channel/UC-Hw_2HbEyiAnus8Sc9PQ9g

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
#define OLED_ADDRESS 0x3C

int selgame = 1;
int mode = "menu";
float g1X = 50;
int g1meteorX = 0;
int g1meteorY = 0;
int g1score = 0;
int g2score = -1;
int g2X = 0;
int g2Y = 0;
int g2appleX = 0;
int g2appleY = 0;
int g3X = 50;
int g3eggX = 0;
int g3eggY = 0;
int g3score = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
  menu();
}

void loop() {
  if (mode == "menu") {
    menu();
  }
  if (mode == "game1") {
    game1();
  }
  if (mode == "game2") {
    game2();
  }
  if (mode == "game3") {
    game3();
  }
  if (mode == "clearram") {
    popup_clr();
  }
  if (mode == "popup_gameover") {
    popup_gmor();
  }
}

void menu(void) {
  delay(150);
  switch (selgame) {
    case 1:
      display.clearDisplay();
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 5);
      display.println("   Mini-Games v1.1   ");
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println("[ ] > Space Shooter");
      display.setCursor(0, 30);
      display.println(" |    Apple Eater");
      display.setCursor(0,40);
      display.println(" |    Eggs Catcher");
      display.setCursor(0, 50);
      display.println(" |  ----------------");
      display.setCursor(0, 60);
      display.println(" |    Clear RAM");
      display.display();
      break;
    case 2:
      display.clearDisplay();
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 5);
      display.println("   Mini-Games v1.1   ");
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println(" |    Space Shooter");
      display.setCursor(0, 30);
      display.println("[ ] > Apple Eater");
      display.setCursor(0,40);
      display.println(" |    Eggs Catcher");
      display.setCursor(0, 50);
      display.println(" |  ----------------");
      display.setCursor(0, 60);
      display.println(" |    Clear RAM");
      display.display();
      break;
    case 3:
      display.clearDisplay();
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 5);
      display.println("   Mini-Games v1.1   ");
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println(" |    Space Shooter");
      display.setCursor(0, 30);
      display.println(" |    Apple Eater");
      display.setCursor(0,40);
      display.println("[ ] > Eggs Catcher");
      display.setCursor(0, 50);
      display.println(" |  ----------------");
      display.setCursor(0, 60);
      display.println(" |    Clear RAM");
      display.display();
      break;
    case 4:
      display.clearDisplay();
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(0, 5);
      display.println("   Mini-Games v1.1   ");
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println(" |    Apple Eater");
      display.setCursor(0, 30);
      display.println(" |    Eggs Catcher");
      display.setCursor(0,40);
      display.println(" | -----------------");
      display.setCursor(0, 50);
      display.println("[ ] > Clear RAM");
      display.setCursor(0, 60);
      display.println(" |");
      display.display();
      break;
  }
  if (analogRead (A1) >= 0 && analogRead (A1) <= 450) {
    if (selgame < 4) {
      selgame += 1;
    }
  }
  if (analogRead (A1) >= 550 && analogRead (A1) <= 1024) {
    if (selgame > 1) {
      selgame -= 1;
    }
  }
  if (digitalRead (7) == LOW && selgame == 1) {
    delay(300);
    if (digitalRead (7) == HIGH) {
      mode = "game1";
    }   
  }
  if (digitalRead (7) == LOW && selgame == 2) {
    delay(300);
    if (digitalRead (7) == HIGH) {
      mode = "game2";
    }   
  }
  if (digitalRead (7) == LOW && selgame == 3) {
    delay(300);
    if (digitalRead (7) == HIGH) {
      mode = "game3";
    }   
  }
  if (digitalRead (7) == LOW && selgame == 4) {
    delay(300);
    if (digitalRead (7) == HIGH) {
      mode = "clearram";
    }   
  }
}

//GAMES

void game1(void) {
  delay(50);
  display.clearDisplay();
  display.setCursor(0, 5);
  display.println("score:");
  display.setCursor(40, 5);
  display.println(g1score);
  display.setCursor(g1X, 50);
  display.println("<=>");
  display.setCursor(g1meteorX, g1meteorY);
  display.println("o");
  display.display();
  if ((analogRead (A0) >= 550 && analogRead (A0) <= 1024) && g1X >= 5) {
    g1X -= ((analogRead (A0) - 500) / 100);
  }
  if ((analogRead (A0) >= 0 && analogRead (A0) <= 450) && g1X <= 100) {
    g1X += ((500 - analogRead (A0)) / 100);
  }
  if (g1meteorY >= -25) {
    g1meteorY += 2;
  }
  if (g1meteorY >= 60) {
    g1meteorY = -25;
    g1meteorX = random(5, 95);
    g1score += 1;
  }
  if (mode == "game1" && digitalRead (8) == LOW) {
    delay(300);
    if (digitalRead (8) == HIGH) {
      mode = "menu";
    }  
  }
  if ((g1X-5 <= g1meteorX && g1X+5 >= g1meteorX) && (g1meteorY >= 45 && g1meteorY <= 55)) {
    g1X = 50;
    g1meteorX = 0;
    g1meteorY = 0;
    g1score = 0;
    mode = "popup_gameover";
  }
}

void game2(void) {
  delay(50);
  display.clearDisplay();
  display.setCursor(0, 5);
  display.println("score:");
  display.setCursor(40, 5);
  display.println(g2score);
  display.setCursor(g2X, g2Y);
  display.println("O");
  display.setCursor(g2appleX, g2appleY);
  display.println("*");
  display.display();
  if (mode == "game2" && digitalRead (8) == LOW) {
    delay(300);
    if (digitalRead (8) == HIGH) {
      mode = "menu";
    }  
  }
  if ((analogRead (A0) >= 550 && analogRead (A0) <= 1024) && g2X >= 5) {
    g2X -= ((analogRead (A0) - 500) / 100);
  }
  if ((analogRead (A0) >= 0 && analogRead (A0) <= 450) && g2X <= 100) {
    g2X += ((500 - analogRead (A0)) / 100);
  }
  if ((analogRead (A1) >= 550 && analogRead (A1) <= 1024) && g2Y >= 5) {
    g2Y -= ((analogRead (A1) - 500) / 100);
  }
  if ((analogRead (A1) >= 0 && analogRead (A1) <= 450) && g2Y <= 100) {
    g2Y += ((500 - analogRead (A1)) / 100);
  }
  if ((g2X-5 <= g2appleX && g2X+5 >= g2appleX) && (g2Y-5 <= g2appleY && g2Y+5 >= g2appleY)) {
    g2appleX = random(5,95);
    g2appleY = random(5,50);
    g2score += 1;
  }
}

void game3(void) {
  delay(50);
  display.clearDisplay();
  display.setCursor(0, 5);
  display.println("score:");
  display.setCursor(40, 5);
  display.println(g3score);
  display.setCursor(g3X, 50);
  display.println("[___]");
  display.setCursor(g3eggX, g3eggY);
  display.println("O");
  display.display();
  if ((analogRead (A0) >= 550 && analogRead (A0) <= 1024) && g3X >= 0) {
    g3X -= ((analogRead (A0) - 500) / 100);
  }
  if ((analogRead (A0) >= 0 && analogRead (A0) <= 450) && g3X <= 100) {
    g3X += ((500 - analogRead (A0)) / 100);
  }
  if (g3eggY >= -25) {
    g3eggY += 2;
  }
  if (g3eggY >= 60) {
    g3eggY = -25;
    g3eggX = random(5, 95);
    g3score += 1;
  }
  if (mode == "game3" && digitalRead (8) == LOW) {
    delay(300);
    if (digitalRead (8) == HIGH) {
      mode = "menu";
    }  
  }
  if (!(g3X-5 <= g3eggX && g3X+25 >= g3eggX) && (g3eggY >= 45 && g3eggY <= 55)) {
    g3X = 50;
    g3eggX = 0;
    g3eggY = 0;
    g3score = 0;
    mode = "popup_gameover";
  }
  if ((g3X-5 <= g3eggX && g3X+25 >= g3eggX) && (g3eggY >= 45 && g3eggY <= 55)) {
    g3eggY = 70;
  }
}

//POPUPS

void popup_clr(void) {
  display.clearDisplay();
  display.setCursor(25,25);
  display.println("RAM Cleared!");
  display.display();
  g1X = 50;
  g1meteorX = 0;
  g1meteorY = 0;
  g1score = 0;
  g2score = -1;
  g2X = 0;
  g2Y = 0;
  g2appleX = 0;
  g2appleY = 0;
  g3X = 50;
  g3eggX = 0;
  g3eggY = 0;
  g3score = 0;
  delay(3000);
  mode = "menu";
}

void popup_gmor(void) {
  display.clearDisplay();
  display.setCursor(30,25);
  display.println("You Lose!");
  display.display();
  delay(3000);
  mode = "menu";
}

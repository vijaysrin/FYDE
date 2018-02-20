/*
 * Driver setup--- intergrate lcd screen and keypad
 */

#include <Keypad.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <stdio.h>
#include <string.h>


const char password[] = "13222";
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

rgb_lcd lcd;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void getPass(char *key){
  int i = 1;
  int val = 0;
  //lcd.clear();
  lcd.print("*");
  while(*(key + i) != '\0'){
    val = 0;
    while(val == 0){
      val = customKeypad.getKey();
    }
    *(key + i) = val;
    lcd.print("*");
    i++; 
  }
}

void checkPassword(char *key){
  int result = true;
  for(int i = 0; i < 5; i++){
    if(*(key + i) != password[i])
      result = false;
  }
  printScreen(result);
}

void printScreen(int result){
  lcd.clear();
  if(result){
    lcd.setColor(2);
    lcd.print("Correct");
    delay(1000);
    lcd.clear();
    lcd.print("Come in!");
    delay(5000);
    lcd.clear();
  }
  else{
    lcd.setColor(1);
    lcd.print("Incorrect Pass");
    lcd.setCursor(0, 1);
    lcd.print("wrong");
    delay(5000);
    lcd.clear();
  }
}

void colorChange(char* key){
  for (int i = 0; i < 255; i++) {
    checkFirst(key);
    lcd.setRGB(i, 0, 255-i);
    delay(5);
  }
  for (int i = 0; i < 255; i++) {
    checkFirst(key);
    lcd.setRGB(255-i, i, 0);
    delay(5);
  }
  for (int i = 0; i < 255; i++) {
    checkFirst(key);
    lcd.setRGB(0, 255-i, i);
    delay(5);
  }
}

void checkFirst(char *key){
  int val = 0;
  val = customKeypad.getKey();
  if(val){
    key[0] = val;
    lcd.setCursor(0, 1);
    getPass(key);
    checkPassword(key);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char key[] = "*****";
  lcd.print("Enter Password: ");
  colorChange(key);
  lcd.clear();
  }



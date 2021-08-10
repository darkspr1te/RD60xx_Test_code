#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <Wire.h>
#define __ARDUINO_
#include "pins.h"
#include <TM1650.h>
#include <TM16xxButtons.h>

TM1650 module(KEYPAD_SDA,KEYPAD_SCL, KEYPAD_IRQ);   // DIO=8, CLK=9, STB=7
TM16xxButtons buttons(&module);    // TM16xx object
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
//HardwareSerial Serial2(PA3, PA2);
HardwareSerial Serial3(PC_11_ALT1, PC_10_ALT1);

char msgString[100]={0};


int16_t version_local=0;
FACTORY_SETTINGS settings_factory={0};
 
 void dump_factory_config()
{
  //  tft.setTextSize(2);
tft.setTextColor(TFT_WHITE, TFT_BLACK);
tft.setCursor((tft.getViewportHeight()/3),15);
sprintf(msgString," 3f800 struture :-");
tft.println(msgString);
sprintf(msgString,"uint_t check value          0x%02x", settings_factory.check_value);
tft.println(msgString);
sprintf(msgString,"uint_tcheck value two       0x%02X", settings_factory.check_value);
tft.println(msgString);
sprintf(msgString,"uint32_t Serial Number      0x%02x    #%010d", settings_factory.serial_number,settings_factory.serial_number);
tft.println(msgString);
sprintf(msgString,"uint_t LCD Type             0x%02x", settings_factory.lcd_type);
tft.println(msgString);
sprintf(msgString,"uint_t uknown              0x%02x", settings_factory.unknown);
tft.println(msgString);
sprintf(msgString,"uint_t uknown two          0x%02x", settings_factory.unknown_two);
tft.println(msgString);
sprintf(msgString,"uint_t uknown three        0x%02x", settings_factory.unknown_three);
tft.println(msgString);
sprintf(msgString,"uint_t uknown four         0x%02x", settings_factory.unknown_four);
tft.println(msgString);
sprintf(msgString,"uint_t uknown five         0x%02x", settings_factory.unknown_five);
tft.println(msgString);
sprintf(msgString,"uint_t uknown six          0x%02x", settings_factory.unknown_six);
tft.println(msgString); 
sprintf(msgString,"uint_t uknown seven        0x%02x", settings_factory.unknown_seven);
tft.println(msgString);
tft.println();
tft.setTextSize(2);
sprintf(msgString,"Press Power button to continue");
tft.println(msgString);
while (buttons.isPressed(KEY_MAIN_POWER)!=1)
{
  buttons.tick();
  delay(100);
}
}

void init_ADC()
{
  pinMode(V_INPUT,INPUT_ANALOG);
  pinMode(TEMP_INT,INPUT_ANALOG);
  pinMode(TEMP_EXT,INPUT_ANALOG);
  pinMode(V_BATT,INPUT_ANALOG);
}
void init_led_buttons()
{
  pinMode(ON_OFF_LED,OUTPUT);
  pinMode(PWR_MAIN_LED,OUTPUT);
  pinMode(SHIFT_LED,OUTPUT);
  pinMode(MEM_LED,OUTPUT);
  pinMode(ISET_LED,OUTPUT);
  pinMode(VSET_LED,OUTPUT);
}

#define PAGE_DELAY 5000
///

float Vsupply = 3.3; //power supply voltage (3.3 V rail) -STM32 ADC pin is NOT 5 V tolerant
float Vout; //Voltage divider output
float R_NTC; //NTC thermistor resistance in Ohms
float R_10k = 9850; //10k resistor measured resistance in Ohms (other element in the voltage divider)
float B_param = NTC_B_CONST; //B-coefficient of the thermistor
float T0 = 298.15; //25°C in Kelvin
float Temp_K; //Temperature measured by the thermistor (Kelvin)
float Temp_C; //Temperature measured by the thermistor (Celsius)
const int VoutPin = TEMP_EXT; //ADC0 pin of STM32

int return_ADC(char adc_val)
{
  int vInput = analogRead(V_INPUT);
  int TempInt = analogRead(TEMP_INT);
  int TempExt = analogRead(TEMP_EXT);
  int VBATT = analogRead(V_BATT);
   Vout = float(TempExt)* (3.3/1023); 
   R_NTC = (Vout * R_10k) /(Vsupply - Vout); 
  Temp_K = (T0*B_param)/(T0*log(R_NTC/R_10k)+B_param); 
  Temp_C = Temp_K - 273.15;
  float adc_read = Temp_C;
  float tmpVal = (adc_read < 0) ? -adc_read : adc_read;
  int tmpInt1 = tmpVal;                  
  float tmpFrac = tmpVal - tmpInt1;     
  int tmpInt2 = trunc(tmpFrac * 100);  
  if (adc_val==1)
  return tmpInt1;
//  sprintf (msgString, "Temp External = %d.%02d 'C",  tmpInt1, tmpInt2);
//  tft.println(msgString);

//
  Vout = float(TempInt)* (3.3/1023); 
  R_NTC = (Vout * R_10k) /(Vsupply - Vout);
  Temp_K = (T0*B_param)/(T0*log(R_NTC/R_10k)+B_param);
  Temp_C = Temp_K - 273.15; 
  adc_read = Temp_C;
  tmpVal = (adc_read < 0) ? -adc_read : adc_read;
  tmpInt1 = tmpVal;               
  tmpFrac = tmpVal - tmpInt1;     
  tmpInt2 = trunc(tmpFrac * 100);  
 // sprintf (msgString, "Temp Internal= %d.%02d 'C",  tmpInt1, tmpInt2);
//  tft.println(msgString);
if (adc_val==2)
  return tmpInt1;


 // adc_read = vInput/VOLTAGE_DIVIDER_VAL; //assumed value based on a few small readings with rigol ds1054/ fluke 054 classic / UT5005 multimeter 
 // Serial3.print(adc_read);Serial3.print("  ");
  adc_read = float(vInput/VOLTAGE_DIVIDER_VAL_12B);
  //adc_read = (float(vInput)/14);
 // Serial3.println(adc_read);
  tmpVal = (adc_read < 0) ? -adc_read : adc_read;
    char *tmpSign = "";
    if (adc_read<0)
    {
        tmpSign="-";
    }
  tmpInt1 = tmpVal;                 
  tmpFrac = tmpVal - tmpInt1;     
  tmpInt2 = trunc(tmpFrac * 100);  
if (adc_val==3)
  return tmpInt1;
  
 // sprintf (msgString, "Voltage Input = V %s%d.%02d", tmpSign, tmpInt1, tmpInt2);
 // tft.println(msgString);

  adc_read = VBATT/VOLTAGE_DIVIDER_VAL; 
  tmpVal = (adc_read < 0) ? -adc_read : adc_read;
  tmpSign = "";
    if (adc_read<0)
    {
        tmpSign="-";
    }
  tmpInt1 = tmpVal;                 
  tmpFrac = tmpVal - tmpInt1;     
  tmpInt2 = trunc(tmpFrac * 100);  
if (adc_val==4)
  return tmpInt1;
//  sprintf (msgString, "Voltage Battery = V %s%d.%02d", tmpSign, tmpInt1, tmpInt2);
//  tft.println(msgString);

}

#define TFT_GREY 0x5AEB
#define M_SIZE 1.3333
float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(int value, byte ms_delay)
{
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawRightString(buf, M_SIZE*40, M_SIZE*(119 - 20), 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(M_SIZE*(120 + 20 * ltx - 1), M_SIZE*(140 - 20), osx - 1, osy, TFT_WHITE);
    tft.drawLine(M_SIZE*(120 + 20 * ltx), M_SIZE*(140 - 20), osx, osy, TFT_WHITE);
    tft.drawLine(M_SIZE*(120 + 20 * ltx + 1), M_SIZE*(140 - 20), osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
  //  tft.drawCentreString("Deg C", M_SIZE*120, M_SIZE*70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(M_SIZE*(120 + 20 * ltx - 1), M_SIZE*(140 - 20), osx - 1, osy, TFT_RED);
    tft.drawLine(M_SIZE*(120 + 20 * ltx), M_SIZE*(140 - 20), osx, osy, TFT_MAGENTA);
    tft.drawLine(M_SIZE*(120 + 20 * ltx + 1), M_SIZE*(140 - 20), osx + 1, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}

void analogMeter()
{

  // Meter outline
  tft.fillRect(0, 0, M_SIZE*239, M_SIZE*126, TFT_GREY);
  tft.fillRect(5, 3, M_SIZE*230, M_SIZE*119, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    uint16_t y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
    uint16_t x1 = sx * M_SIZE*100 + M_SIZE*120;
    uint16_t y1 = sy * M_SIZE*100 + M_SIZE*140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (M_SIZE*100 + tl) + M_SIZE*120;
    int y2 = sy2 * (M_SIZE*100 + tl) + M_SIZE*140;
    int x3 = sx2 * M_SIZE*100 + M_SIZE*120;
    int y3 = sy2 * M_SIZE*100 + M_SIZE*140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
    x1 = sx * M_SIZE*100 + M_SIZE*120;
    y1 = sy * M_SIZE*100 + M_SIZE*140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 7, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * M_SIZE*100 + M_SIZE*120;
    y0 = sy * M_SIZE*100 + M_SIZE*140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }

 // tft.drawString("Deg C", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  //tft.drawCentreString("DegC", M_SIZE*120, M_SIZE*70, 4); // Comment out to avoid font 4
  tft.drawRect(5, 3, M_SIZE*230, M_SIZE*119, TFT_BLACK); // Draw bezel line

  plotNeedle(0, 0); // Put meter needle at 0
}


void fnClick(byte nButton)
{ // byte nButton is the button-number (first button is number 0)
#if   defined(DEBUG_TWO)
  Serial3.print(F("Button "));
  Serial3.print(nButton);
  Serial3.println(F(" click."));
#endif 
  switch  (nButton)
  {
    case 0:
      Serial3.println("Key ISET pressed");
      digitalWrite(ISET_LED,!digitalRead(ISET_LED));
      break;
    case 1:
      Serial3.println("Key MEM pushed");
      digitalWrite(MEM_LED ,!digitalRead(MEM_LED ));
      break;
    case 2:
      Serial3.println("Key POWER_MAIN pressed");
      digitalWrite(PWR_MAIN_LED ,!digitalRead(PWR_MAIN_LED ));
      break;
    case 3:
      Serial3.println("Key SHIFT pressed");
      digitalWrite(SHIFT_LED ,!digitalRead(SHIFT_LED ));
      break;
    case 4:
      Serial3.println("Key ZERO Pressed");
      break;
    case 5:
      Serial3.println("Key ONE Pressed");
      break;
    case 6:
      Serial3.println("Key FOUR Pressed");
      break;
    case 7:
      Serial3.println("Key SEVEN Pressed");
      break;
    case 8:
      Serial3.println("Key FULL_STOPPressed");
      break;
    case 9:
      Serial3.println("Key TWO Pressed");
      break;
    case 10:
      Serial3.println("Key FIVE Pressed");
      break;
    case 11:
      Serial3.println("Key EIGHT Pressed");
      break;
    case 12:
      Serial3.println("Key LEFT Pressed");
      break;
    case 13:
      Serial3.println("Key THREE Pressed");
      break;
    case 14:
      Serial3.println("Key SIX Pressed");
      break;
    case 15:
      Serial3.println("Key NINE Pressed");
      break;
    case 16:
      Serial3.println("Key RIGHT Pressed");
      break;
    case 17:
      Serial3.println("Key ENTER Pressed");
      break;
    case 18:
      Serial3.println("Key DOWN Pressed");
      break;
    case 19:
      Serial3.println("Key UP Pressed");
      break;
    case 20:
      Serial3.println("Key ROTARY Pressed");
      break;
    case 21:
      Serial3.println("Key VSET Pressed");
      digitalWrite(VSET_LED ,!digitalRead(VSET_LED ));
      break;
    case 23:
      Serial3.println("Key ON_OFF pressed");
      digitalWrite(ON_OFF_LED ,!digitalRead(ON_OFF_LED ));
      break;

    default :
      Serial3.println("error unknown key");
  }
}



void writeI2CByte(byte data_addr, byte data){
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr){
  byte data = NULL;
  
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1); //retrieve 1 returned byte
  delay(1);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}

void init_EEPROM()
{
  Serial3.println("Enable EEPROM");
  Wire.setSDA(EEPROM_SDA);
  Wire.setSCL(EEPROM_SCL);
  Wire.begin();
  //writeI2CByte(0, 1);
  int value=0;
  #if 1
  for (int row=0;row<0xf;row++)
  {
    for (int column=0;column<0xf;column++)
    {
      value = readI2CByte(column+row);
    //  Serial3.print(value,HEX);
     // Serial3.print(", ");
     sprintf(msgString,"0x%02x ",value);
     Serial3.print(msgString);
    }
    Serial3.println();
  }
#endif

}
void setup() {

init_ADC();
init_led_buttons();
Serial3.begin(115200);//start serial early in case of any debug
Serial3.println("\n\rEnable USB Serial");

tft.init();
tft.setRotation(3); 
tft.fillScreen(TFT_BLACK);

tft.setTextColor(TFT_WHITE, TFT_BLUE);
tft.fillRect(0,0,320,16, TFT_BLUE);
settings_factory=*(FACTORY_SETTINGS*)FACTORY_CALIB_MEM;
tft.setCursor((tft.getViewportHeight()/3),4);
sprintf(msgString," Riden 60%d version ", RIDEN_MODEL);
 
tft.println(msgString);



init_EEPROM();
buttons.attachClick(fnClick);
dump_factory_config();
tft.setTextSize(2);
//delay(1500);

tft.fillScreen(TFT_BLACK);
tft.setCursor(0,0);
analogReadResolution(12); //set ADC to 12 bit 
analogMeter(); // Draw analogue meter
updateTime = millis(); // Next update time
}



void loop() {

buttons.tick();

 if (updateTime <= millis()) {
    updateTime = millis() + 35; // Update emter every 35 milliseconds
 
    // Create a Sine wave for testing
   // d += 4; if (d >= 360) d = 0;
    //value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[0]=return_ADC(0);
    plotNeedle(return_ADC(3), 0); // It takes between 2 and 12ms to replot the needle with zero delay
  }
}
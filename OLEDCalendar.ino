#include <ESP8266WiFi.h>
#include <SSD1306.h>
#include <TimeLib.h>


// -- OLED Configuration --------------------------------------------------------------------------------------------------

// Refer to https://github.com/squix78/esp8266-oled-ssd1306 for details on Daniel Eichhorn's great library for using an
// SSD1306 display with the ESP8266.  The sketch only uses the basic library to render screens and ignores the advance UI 
// library that provides frames and overlays.
//
 
#define OLED_SDA                                    D1          // pin 14
#define OLED_SDC                                    D2          // pin 12
#define OLED_ADDR                                   0x3C

SSD1306          display(OLED_ADDR, OLED_SDA, OLED_SDC);        // For I2C


// -- TimeLib ------------------------------------------------------------------------------------------------------------

// Refer to https://github.com/PaulStoffregen/Time for details on Paul Stoffregen's time library.  It includes samples on
// synchronising the date and time with various sources including a Real Time Clock, internet NTP time service, GPS time 
// data, and Serial time messages from a computer. This sample code 'hard codes' a date and time for simplicity. 
//


// -- Calendar Configuration ---------------------------------------------------------------------------------------------

#define CAL_SPACING_X                               19
#define CAL_SPACING_X_WIDTH                         15
#define CAL_SPACING_Y_6_ROWS                        9
#define CAL_SPACING_Y_5_ROWS                        10

#define CAL_FEBRUARY                                2
#define CAL_SHOW_6_ROWS_OF_DAYS                     false
#define CAL_SHOW_MONTH_YEAR                         true

#define CAL_HIGHLIGHT_CURRENT_DAY            
#undef CAL_HIGHLIGHT_CURRENT_DAY_REVERSE                        Highlight in reverse font?    
#define CAL_HIGHLIGHT_CURRENT_DAY_HEIGHT            7            

#if CAL_SHOW_MONTH_YEAR == true
  #define CAL_INVERSE_MONTH_YEAR                    true
  #define CAL_INVERSE_MONTH_YEAR_TOP                0
  #define CAL_INVERSE_MONTH_YEAR_LEFT               0
  #define CAL_INVERSE_MONTH_YEAR_WIDTH              128
  #define CAL_INVERSE_MONTH_YEAR_HEIGHT             9
  #define CAL_MONTH_YEAR_TOP                        -2
  #define CAL_SPACING_Y_TOP                         8
#else
  #define CAL_SPACING_Y_TOP                         -1
#endif


// -- Initialization -----------------------------------------------------------------------------------------------
//
void setup() {

  Serial.begin(115200);
    
  setTime(12, 0, 0, 16, 3, 2016); 
  display.init();
  display.displayOn();
  renderDate(now());
}

void loop() {

  delay(100);
  
}


// -------------------------------------------------------------------------------------------------------
// Determine the number of days in the nominated month ..

int daysInMonth(time_t timeT) {

  int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  return (month(timeT) == CAL_FEBRUARY ? (year(timeT)%4  == 0 ? (year(timeT)%100 != 0 ? 29 : (year(timeT)%400 == 0 ? 29 : 28)) : 28) : days[month(timeT) - 1]);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first day in the month ..

time_t firstDayOfMonth(time_t timeT) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = 1;
  tm.Month = month(timeT);
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Render a calendar ..

void renderDate(time_t timeT) {

  time_t firstOfMonth = firstDayOfMonth(timeT);

  display.clear();
  display.setFont(ArialMT_Plain_10);

  #if CAL_SHOW_MONTH_YEAR == true
  
    #if CAL_INVERSE_MONTH_YEAR
        display.setColor(WHITE);
        display.fillRect(CAL_INVERSE_MONTH_YEAR_LEFT, CAL_INVERSE_MONTH_YEAR_TOP, CAL_INVERSE_MONTH_YEAR_WIDTH, CAL_INVERSE_MONTH_YEAR_HEIGHT);
        display.setColor(BLACK);
    #endif
    
    String months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, CAL_MONTH_YEAR_TOP, months[month(firstOfMonth) - 1] + "  " + String(year(firstOfMonth)));
    
    #if CAL_INVERSE_MONTH_YEAR
      display.setColor(WHITE);
    #endif
    
  #endif
  
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(0 + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Mo");
  display.drawString((1 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Tu");
  display.drawString((2 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "We");
  display.drawString((3 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Th");
  display.drawString((4 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Fr");
  display.drawString((5 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Sa");
  display.drawString((6 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Su");

  int dayOfMonth = 1;

  int dow = (dayOfWeek(firstOfMonth) == 1 ? 6 : dayOfWeek(firstOfMonth) - 2);
  int maxDays = daysInMonth(firstOfMonth);
  int maxRows = 1 + ((maxDays - (7 - dow)) / 7) + ((maxDays - (7 - dow)) % 7 > 0 ? 1 : 0);
  int spacing_Y = ((maxRows == 6 && CAL_SHOW_6_ROWS_OF_DAYS) || CAL_SHOW_MONTH_YEAR ? CAL_SPACING_Y_6_ROWS : CAL_SPACING_Y_5_ROWS);


  // Render first row of days, this may be less than seven days depending on when the first day of the month is ..
  
  for (int col = dow; col < 7; col++) {

    #if defined(CAL_HIGHLIGHT_CURRENT_DAY) 
    
      #if defined(CAL_HIGHLIGHT_CURRENT_DAY_REVERSE)
      
        if (day(timeT) == dayOfMonth) {
          display.setColor(WHITE);
          display.fillRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + spacing_Y + 2, (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_CURRENT_DAY_HEIGHT);   
          display.setColor(BLACK);
        }

      #else

        if (day(timeT) == dayOfMonth) {
          display.drawRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + spacing_Y + 2, (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_CURRENT_DAY_HEIGHT);      
        }
                  
      #endif

    #endif

    display.drawString((col * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP + spacing_Y, String(dayOfMonth));
    
    #if defined(CAL_HIGHLIGHT_CURRENT_DAY)
    
      if (day(timeT) == dayOfMonth) {

        display.setColor(WHITE);

      }
      
    #endif
    
    dayOfMonth++;
      
  }


  // Render remaining rows.  If the month happens to span 6 rows handle it according to the CAL_SHOW_6_ROWS_OF_DAYS value ..

  for (int row = 2; row <= 6 && dayOfMonth <= maxDays; row++) {

    for (int col = 0; col < 7 && dayOfMonth <= maxDays; col++) {

        #if defined(CAL_HIGHLIGHT_CURRENT_DAY) 
        
          #if defined(CAL_HIGHLIGHT_CURRENT_DAY_REVERSE)
          
            if (day(timeT) == dayOfMonth) {
              display.setColor(WHITE);
              display.fillRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + 2 + ((CAL_SHOW_6_ROWS_OF_DAYS ? row : (row % 6 == 0 ? 1 : row)) * spacing_Y), (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), spacing_Y - 1);   
              display.setColor(BLACK);
            }

          #else

            if (day(timeT) == dayOfMonth) {
              display.drawRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + 2 + ((CAL_SHOW_6_ROWS_OF_DAYS ? row : (row % 6 == 0 ? 1 : row)) * spacing_Y), (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), spacing_Y - 1);   
            }
                      
          #endif

        #endif
        
        display.drawString((col * CAL_SPACING_X) + CAL_SPACING_X_WIDTH -1, CAL_SPACING_Y_TOP + ((CAL_SHOW_6_ROWS_OF_DAYS ? row : (row % 6 == 0 ? 1 : row)) * spacing_Y), String(dayOfMonth));

        #if defined(CAL_HIGHLIGHT_CURRENT_DAY)
        
          if (day(timeT) == dayOfMonth) {

            display.setColor(WHITE);

          }
          
        #endif
        
        dayOfMonth++;
        
     }
  
  }

  display.display();
  
}


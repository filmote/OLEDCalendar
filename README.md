##OLEDCalendar
An ESP8266 / OLED display project that renders a calendar.  
<br />

##Background
The inspiration for this project came from [rydepier](https://github.com/rydepier)'s [Arduino-and-OLED-Calendar](https://github.com/rydepier/Arduino-and-OLED-Calendar) project which was targeted at the Arduino and used a different library to drive the OLED.  While rewriting it for the ESP8266, I used none of the original code.

Additional thanks to :

* [PaulStoffregen](https://github.com/PaulStoffregen) for his [Time](https://github.com/PaulStoffregen/Time) project and 
* [Squix78](https://github.com/squix78) for his [esp8266-oled-ssd1306](https://github.com/squix78/esp8266-oled-ssd1306) library for driving these little OLED displays.  
<br />

##In Operation

The calendar provides a couple of configuration parameters that control its visual appearance and allow it to utilise the small real estate of the OLED effectively. Namely these are:

```c
#define CAL_SHOW_6_ROWS_OF_DAYS                     false
#define CAL_SHOW_MONTH_YEAR                         false 
```
<br /><br />

__CAL_SHOW_MONTH_YEAR__ set to __false__, __CAL_SHOW_6_ROWS_OF_DAYS__ set to __true__: 

Note that the calendar takes up six lines in this example and line spacing is tight at 9 pixels between rows..  Where a month renders in five rows, the line spacing will be increased to improve the readability (11 pixels between lines).

![Calendar 2](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_02_thumb.jpg)

<br /><br />
__CAL_SHOW_MONTH_YEAR__ set to __false__, __CAL_SHOW_6_ROWS_OF_DAYS__ set to __false__:

Note that the line spacing is greater than the previous examples (11 pixels between rows) but the 31 is rendered on the first line.  Most months will render in five rows (or even four if it is February in a non-leap year and the first day of the month is a Monday!). 

![Calendar 3](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_03_thumb.jpg)

<br /><br />
__CAL_SHOW_MONTH_YEAR__ set to __true__: 

When rendering the month / year heading, the date must be displayed in 6 rows (as if __CAL_SHOW_6_ROWS_OF_DAYS__ set to __false__).  Due to real estate restrictions, the line spacing is kept tight (9 pixels).

![Calendar 1](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_01_thumb.jpg)

<br />


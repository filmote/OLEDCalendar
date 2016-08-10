##OLEDCalendar
An ESP8266 / OLED display project that renders a calendar.  
<br />

##Background
There are numerous articles, projects and libraries that set the ESP8266 into Access Point mode allowing you to connect and configure an SSID and password before restarting the device in Station mode.  These are great but what if you actually have a display attached to the device?  Why can't the device attempt to connect to previously saved settings and if this fails, allow the user to select an Access Point and enter a pasword using a GUI?

I have used a number of screens on the Arduino but wanted this project to be compatible with the small 128x64 pixel OLED displays that have become very popular and cheap to buy.  I also wanted to keep the input as simple as possible and settled on 5 buttons - 4 for movement (up, down, left and right) and one for selecting options. 

The inspiration for this project came from two separate GitHub projects :

* [PaulStoffregen](https://github.com/tzapu) for his [Time](https://github.com/PaulStoffregen/Time) project and 
* [Squix78](https://github.com/squix78) for his [esp8266-oled-ssd1306](https://github.com/squix78/esp8266-oled-ssd1306) library for driving these little OLED displays.  
<br />

##In Operation

The calendar provides a couple of configuration parameters that control its visual appearance and allow it to utilise the small real estate of the OLED effectively. Namely these are:

```c
#define CAL_SHOW_6_ROWS_OF_DAYS                     false
#define CAL_SHOW_MONTH_YEAR                         false 
```


__CAL_SHOW_MONTH_YEAR__ set to __false__, __CAL_SHOW_6_ROWS_OF_DAYS__ set to __true__: 
Note that the calendar takes up six lines in this example and line spacing is tight at 9 pixels between rows..  Where a month renders in five rows, the line spacing will be increased to improve the readability (11 pixels between lines).

![Calendar 2](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_02_thumb.jpg)

__CAL_SHOW_MONTH_YEAR__ set to __false__, __CAL_SHOW_6_ROWS_OF_DAYS__ set to __false__:
Note that the line spacing is greater than the previous examples (11 pixels between rows) but the 31 is rendered on the first line.  Most months will render in five rows (or even four if it is February in a non-leap year and the first day of the month is a Monday!). 

![Calendar 3](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_03_thumb.jpg)

__CAL_SHOW_MONTH_YEAR__ set to __true__: 
When rendering the month / year heading, the date must be displayed in 6 rows (as if __CAL_SHOW_6_ROWS_OF_DAYS__ set to __false__).  Due to real estate restrictions, the line spacing is kept tight (9 pixels).
![Calendar 1](https://github.com/filmote/OLEDCalendar/blob/master/images/calendar_01_thumb.jpg)

<br />


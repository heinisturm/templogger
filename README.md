# templogger

a little Arduino based temperatur logger.

An Arduino Pro mini is used to log temperature from a DS18B20 every 60s.
The temperature values are stored in the internal eeprom.

PIN   Function
2     ONE_WIRE_BUS for DS1820
10    PIN_SHOW pull to GND to print the temperatur values to the uart
11    PIN DUMMY no function
12    PIN_ERASE pull to GND clear eeprom data

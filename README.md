# Temperature Sensor
Made a  1-wire bus system driver for ds18b20. I use the micro controller esp32 with esp-idf and the language C

For now, it only works with 1 ds18, but can be fixed easily. Match Rom has to be implemented for that thought.

# Features incoming
* Multiple ds18 on the same wire
* Write ST7793 driver to make use of my display. (SPI interface)

 

# Esp-idf Commands
. $HOME/esp/esp-idf/export.sh
idf.py -p /dev/ttyUSB0 flash
idf.py reconfigure
idf.py menuconfig
Shift-Alt-G, hover affect

## Reset
esptool.py --no-stub -p /dev/ttyUSB0 flash_id



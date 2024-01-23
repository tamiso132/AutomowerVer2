. $HOME/esp/esp-idf/export.sh

idf.py -p /dev/ttyUSB0 flash

-Grounding all current, esp32 max ground current, how it works
https://www.analog.com/en/technical-articles/successful-pcb-grounding-with-mixedsignal-chips--follow-the-path-of-least-impedance.html

to reset
esptool.py --no-stub -p /dev/ttyUSB0 flash_id
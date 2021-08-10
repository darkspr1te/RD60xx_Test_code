# Riden RD60xx Testing code


####Working :-
- LCD     (via tft_espi lib)              100%

- Buttons (via tm16xx lib)                100%

- ADC inputs VIN/VBAT (arduino code)      100%

- Temp ADC inputs (calib values wrong)     50%

- Power control                           0%

- FAN/RELAY                               0%


### Comments

for TM16xx lib to compile you must edit TM16xxMatricGFX.cpp and put 
`#if 0`

`#endif `
around all the code in the file in order exclude it from compile or it will require a dozen adafruit libs to compile











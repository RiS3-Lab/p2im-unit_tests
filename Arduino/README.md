# Arduino sample firmware

You can use either the pre-compiled firmware binary in each directory, or compile the firmware from source code by yourself.

## Compiling firmware
Set up the Arduino development environment:  
1) Download the [Arduino core](https://drive.google.com/file/d/13FO7wVcyBzSKz19MirNG6V7RgrgGietP/view?usp=sharing), and untar it to ~/.arduino15

2) Download the [library](https://drive.google.com/file/d/1YTkcOAXTXF4obIdlH_Cd-sOcAt9OqwgO/view?usp=sharing) that firmware rely on, and untar it to ~/Arduino

Then `cd` to the firmware directory, such as `ADC/`. Do `../build-f103.sh` or `../build-ad.sh` to compile the firmware

For `GPIO` and `GPIO_INT` firmware, different MCU uses different pins. You need to manually comment/uncomment the code that instructs which pins to use.

# run this script in each directory, such as Arduino/ADC
../arduino-cli/arduino-cli compile -b arduino:sam:arduino_due_x_dbg *.ino --build-path `realpath ./build` -o firmware

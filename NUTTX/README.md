# NUTTX
The source code and configuration files for each unit test is at [src/myapp](src/myapp) and [src/configs](src/configs), while the firmware binary and model instantiated are under the directories named after peripherals, such as [ADC/](ADC). 

You can either use the firmware binary shipped in each subdirectory, or compile firmware binary from source code.

## Compiling from source code
### Setup
```bash
# Install dependencies
sudo apt-get install automake bison build-essential flex gperf libncurses5-dev libtool libusb-dev libusb-1.0.0-dev pkg-config


cd <nuttx_base>/

cd nuttex_env/tools/kconfig-frontends/
./configure
make
sudo make install
sudo ldconfig


cd <nuttx_base>/

# Copy source code
cp -r src/myapp nuttx_env/apps/examples

# Copy configuration files
cp -r src/configs/* nuttx_env/nuttx/configs/stm32f103-minimum/
```


### Compiling NUTTx samples
```bash
cd <nuttx_base>/
make -C nuttx_env/nuttx distclean


# Choose the firmware to compile
# Use USART as an example
cd nuttx_env/apps/examples/myapp

# myapp_main.c.adc/myapp_main.c.gpioint/myapp_main.c.pwm/myapp_main.c.usart/myapp_main.c.gpio/myapp_main.c.i2c/myapp_main.c.spi are for adc/gpioint/pwm/usart/gpio/i2c/spi firmware respectively
# Choose to compile myapp_main.c.usart for USART. Note that there should be only one .c file in nuttx_env/apps/examples/myapp
cp myapp_main.c.usart myapp_main.c 


# Configure
# adc/gpio/gpioint/i2c/pwm/spi/usart directory stores configuration file
cd <nuttx_base>/
cd nuttx_env/nuttx/tools
./configure.sh stm32f103-minimum/usart

cd ..
make

# nuttx/nuttx.bin is the ELF/binary file of the firmware
```

# RIOT sample firmware
Sample firmware is organized by peripherals.
Each folder is for one peripheral.

In each folder, we include 
* Binary of the sample firmware
* Source code of the sample firmware. All peripherals, except `GPIO` and `GPIO_INT`, use one single source code (.c) file for all MCUs.
`GPIO` and `GPIO_INT` have two separate source code files: `mainF103_SAM3` for F103 and SAM3 MCU, and `mainK64F` for K64F MCU.
* Makefile. Each MCU has its own Makefile. MakefileF103.mk/MakefileK64F.mk/MakefileSAM3.mk are for F103/K64F/SAM3 MCU respectively.
* The model instantiated by P2IM.


Note that not all peripherals are supported on all MCUs by RIOT,
therefore, each folder only contains Makefiles and binary for those that are available.

Besides, `RIOT-ENV/` folder includes the src code for RIOT OS, which is required to compile the firmware.

Although we provide the **firmware binary**, you can still compile the firmware from source code.


## How to compile firmware
### Compile firmware
1) Change directory to the specific peripheral.

 ```bash
 cd GPIO
 ```

2) This step only applies to `GPIO` and `GPIO_INT`. 

Choose the source code file for the MCU you want to use (`mainF103_SAM3` is for F103 and SAM3 MCU, while `mainK64F` is for K64F MCU), and add `.c` file extension to it.
Note that only one `.c` file with `main` function is allowed in the same folder.

3) Compile the firmware by make. Note that each MCU has it own Makefile.
 ```bash
 # compiling the GPIO firmware for F103
 make -f MakefileF103.mk
 ```

4) The firmware binary is output to `./bin` directory

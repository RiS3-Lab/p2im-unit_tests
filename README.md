This is the git repo for unit tests of [P<sup>2</sup>IM paper](https://www.usenix.org/conference/usenixsecurity20/presentation/feng).

For each unit test case, we include its source code, binary (ELF), and the processor-peripheral model instantiated by P2IM.


## How is the git repo organized
Unit test cases are organized by OS and peripherals. 
For example, `Arduino/ADC/` directory has
* Source code of Arduino ADC test case (.ino file),
* Firmware binary of Arduino ADC test case on f103 and sam3 MCU (.elf file),
* Test results (.csv file). Test results include all registers that are accessed by the unit test firmware, their category in ground truth (`Reg cat` column) and their category assigned by P2IM (`Model Cat` column). Note that when calculating register categorization accuracy in P2IM paper, only registers that have been read by the firmware are considered. This is because registers that are never read by the firmware do not influence firmware execution in P2IM at all. It does not matter whether those registers are correctly categorized or not.


## How to instantiate model for the firmware and calculate statistics
We take Arduino ADC peripheral on SAM3 MCU as an example.
```bash
# modify the mi_path, qemu_path, objdump_path, model_stat_path, gt_path in <repo_path>/run.py

# cd to the directory where firmware is located
cd Arduino/ADC

# run.py instantiates processor-peripheral interface model, and calculates statistics
../../run.py sam3 SAM3X8EArduinoADC.elf # ../../run.py shows usage of the script

# peripheral_model-sam3.json is the peripheral model instantiated
# statistics are printed to stdout and sam3.csv
```


## OS-specific README
Some steps, such as firmware compilation, are OS specific.
Therefore, we have OS-specific README for [Arduino](Arduino/README.md), [RIOT](RIOT/README.md), and [Nuttx](NUTTX/README.md).

Note that you need GNU Arm Embedded Toolchain to compile the firmware.
Steps to set up the toolchain:
1. Download the toolchain from [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).
2. Untar the downloaded file by `tar xjf *.tar.bz2`.
3. Add `bin/` directory extracted into your `$PATH` environment variable.
4. Test if the toolchain is added to `$PATH` successfully by `which arm-none-eabi-gcc`.


## Citing our [paper](https://www.usenix.org/conference/usenixsecurity20/presentation/feng)
```
@inproceedings {p2im,
title = {P2IM: Scalable and Hardware-independent Firmware Testing via Automatic Peripheral Interface Modeling},
author={Feng, Bo and Mera, Alejandro and Lu, Long},
booktitle = {29th {USENIX} Security Symposium ({USENIX} Security 20)},
year = {2020},
url = {https://www.usenix.org/conference/usenixsecurity20/presentation/feng},
}
```


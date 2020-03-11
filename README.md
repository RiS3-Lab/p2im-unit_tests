This is the git repo for unit tests of [P<sup>2</sup>IM paper](https://www.usenix.org/conference/usenixsecurity20/presentation/feng).

For each unit test case, we include its source code, binary (ELF), and the processor-peripheral model instantiated by P2IM.


## How is the git repo organized
Unit test cases are organized by OS and peripherals. 
For example, `Arduino/ADC/` directory has
* Source code of Arduino ADC test case (.ino file),
* Firmware binary of Arduino ADC test case on f103 and sam3 MCU (.elf file),
* Test results (.csv file). Test results include all registers that are accessed by the unit test firmware, their category in ground truth (`Reg cat` column) and their category assigned by P2IM (`Model Cat` column). Note that when calculating register categorization accuracy in P2IM paper, only registers that have been read by the firmware are considered. This is because registers that are never read by the firmware do not influence firmware execution in P2IM at all. It does not matter whether those registers are correctly categorized or not.


## OS-specific README
Some steps, such as firmware compilation, are OS specific.
Therefore, we have OS-specific README for [Arduino](Arduino/README.md), [RIOT](RIOT/README.md), and [Nuttx](NUTTX/README.md).



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


## TODO
In the near future, we are going to: 
* Release source code of Arduino core
* Explain how to build Arduino test cases
* Fix/explain GPIO and GPIO_INT require source code (pin usage) changes for different MCUs.

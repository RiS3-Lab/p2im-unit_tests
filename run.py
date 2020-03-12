#!/usr/bin/env python3
import sys, shutil, subprocess

mcus = ["f103", "f429", "sam3", "k64f"]
ground_truth_f = {"f103": "STM32F103-GroundTruth.csv", "f429": "STM32F429-GroundTruth.csv", "sam3": "AtmelSAM3-GroundTruth.csv", "k64f": "NXPK64F-GroundTruth.csv"}

# path
mi_path = "/home/bo/p2im/p2im_scratch/model_instantiation/me.py"
qemu_path = "/home/bo/p2im/p2im_scratch/qemu/precompiled_bin/qemu-system-gnuarmeclipse"
objdump_path = "/home/bo/p2im/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objdump"

model_stat_path = "/home/bo/p2im/p2im_scratch/utilities/model_stat/statFp3.py"
gt_path = "/home/bo/p2im/p2im_scratch/externals/p2im-ground_truth"


if len(sys.argv) == 3:
    mcu = sys.argv[1]
    if mcu not in mcus:
        sys.exit("MCU model %s not supported!" % mcu)

    # delete old model
    shutil.rmtree("1/", ignore_errors=True)

    # generate cfg file for model instantiation script
    cfg_f = "mi-%s.cfg" % mcu
    cfg_board = {"f103": "NUCLEO-F103RB", "f429": "STM32F429I-Discovery", "sam3": "Arduino-Due", "k64f": "FRDM-K64F"}
    cfg_mcu= {"f103": "STM32F103RB", "f429": "STM32F429ZI", "sam3": "SAM3X8E", "k64f": "MK64FN1M0VLL12"}

    with open(cfg_f, "w") as f:
        f.write("[qemu]\n")
        f.write("bin         = %s\n" % qemu_path)
        f.write("log         = unimp,guest_errors,int\n\n")

        f.write("[program]\n")
        f.write("board       = %s\n" % cfg_board[mcu])
        f.write("mcu         = %s\n" % cfg_mcu[mcu])
        f.write("img         = %s\n\n" % sys.argv[2])

        f.write("[model]\n")
        f.write("retry_num   = 3\n")
        f.write("peri_addr_range = 512\n")
        f.write("objdump     = %s\n" % objdump_path)
        f.write("log_file    = me.log\n")

    # instantiate model
    subprocess.call([mi_path, "-c", cfg_f])

    # rename results
    model_f = "peripheral_model-%s.json" % mcu
    shutil.copyfile("1/peripheral_model.json", model_f)

    # calculate model statistics
    stat_f = "%s.csv" % mcu
    subprocess.call([model_stat_path, model_f, "%s/%s" % (gt_path, ground_truth_f[mcu]), stat_f])

    '''
    # commit results
    print("Results are added to git")
    subprocess.call(["git", "add", model_f, stat_f, stat_f+".stat",sys.argv[2]])
    '''


else:
    print("Usage: %s mcu_model <firmware_elf>" % sys.argv[0])
    print("\tAvailable mcu_model: ", mcus)

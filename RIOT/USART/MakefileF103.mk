# name of your application
APPLICATION = F103-RIOT-USART
# If no BOARD is found in the environment, use this default:
#BOARD ?= native
BOARD ?= nucleo-f103rb

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT-ENV


USEMODULE += periph_uart
USEMODULE += stdio_uart_rx


# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 0

include $(RIOTBASE)/Makefile.include

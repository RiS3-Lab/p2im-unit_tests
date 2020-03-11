# name of your application
APPLICATION = K64F-RIOT-USART
# If no BOARD is found in the environment, use this default:
#BOARD ?= native
BOARD ?= frdm-k64f

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT-ENV


USEMODULE += periph_uart
USEMODULE += stdio_uart_rx

DISABLE_MODULE += cortexm_fpu

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 0

include $(RIOTBASE)/Makefile.include

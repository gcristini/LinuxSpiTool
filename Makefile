
# Current makefile directory
CURRENT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Directory starting point of the source files
SOURCE_DIR := $(abspath $(CURRENT_DIR))
BASE_TREE_SRC := $(abspath $(SOURCE_DIR))/

RM := rm -r -f

RENAME_FILE := mv

# --------------------------------------------------  OUTPUT NAMES  --------------------------------------------------------------

# Output library
OUTPUT := spi_tool

# Board path where library must copied
BOARD_PATH_LIB := root@10.139.40.33:/home/root
# --------------------------------------------------------------------------------------------------------------------------------

# --------------------------------------  Set toolchain  ---------------------------------------------
BINARY_COMPILER := /opt/fsl-imx-wayland/4.14-sumo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux
COMPILER_SYS_ROOT := --sysroot=/opt/fsl-imx-wayland/4.14-sumo/sysroots/aarch64-poky-linux/
DEBUG_OPTIMIZATION := -O0 -g3 -Wall -DDEBUG
RELEASE_OPTIMIZATION := -O3 -g0

# c compiler
CC := $(BINARY_COMPILER)/aarch64-poky-linux-gcc

# C++ compiler
CPP := $(BINARY_COMPILER)/aarch64-poky-linux-g++

# asm compiler
CC_ASM := $(BINARY_COMPILER)/aarch64-poky-linux-as

# Linker
LINK := $(BINARY_COMPILER)/aarch64-poky-linux-g++

# Disassembler
DISASSEMBLER := $(BINARY_COMPILER)/aarch64-poky-linux-objdump

# Compiler flags
CPPFLAGS := $(RELEASE_OPTIMIZATION) -rdynamic -fmessage-length=0 -fpermissive \
	    -mcpu=cortex-a53 \
	    -fsigned-char $(COMPILER_SYS_ROOT)
CFLAGS 	 := $(RELEASE_OPTIMIZATION) -rdynamic -Wwrite-strings -Wunused-function -Wpointer-arith \
	    -fmessage-length=0 -mcpu=cortex-a53 -fsigned-char \
	    $(COMPILER_SYS_ROOT)
LNKFLAGS := -Xlinker -Map=$(OUTPUT).map -rdynamic -mcpu=cortex-a53 -fsigned-char \
	    $(COMPILER_SYS_ROOT)

# C preprocessor symbols
C_DEFINES := 

# assembly preprocessor defines
ASM_FLAGS := 
# ------------------------------------------------------------------------------------------------

# In order to exclude a file from the compilation remove the specified file from this list
# C source files
C_SRC	:= 	$(SOURCE_DIR)/spi_tool.c \
			$(SOURCE_DIR)/spi_lib.c

CPP_SRC := 	

# In order to exclude a file from the compilation remove the specified file from this list
# Assembly source files
ASM_SRC :=      

# Specify the user libraries to link
USR_LIBS := 	

# Specify the system libs
LIBS := pthread rt

# Specify system static libraries
SYS_STATIC_LIBS := 

# Target list of include directories
TARGET_INCLUDE :=   

include common.mak

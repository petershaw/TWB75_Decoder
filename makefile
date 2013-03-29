###################################################
######      AVR Project - AnalyserDude       ######
###################################################
###### Project:   AnalyserDude
###### Company:   ps
###### Developer: Peter Shaw
###### Copyright: 2013

PROJECTNAME = AnalyserDude

# Name of target controller
# (e.g. 'at90s8515', see the available avr-gcc mmcu
# options for possible values)
MCU = atmega328p

# Frequency of the controller
# Set this to the frequency of your controler. It will
# be accessable from within your code as well
F_CPU = 16000000UL

# id to use with programmer
# default: PROGRAMMER_MCU=$(MCU)
# In case the programer used, e.g avrdude, doesn't
# accept the same MCU name as avr-gcc (for example
# for ATmega8s, avr-gcc expects 'atmega8' and 
# avrdude requires 'm8')
PROGRAMMER_MCU = m328p

# Programmer to use with avrdude
PROGRAMMER=usbasp

# port to use a bootloader
# This should be the port for your MCU.
BOOTLOADER_PORT = /dev/tty.SLAB_USBtoUART

# baud to use a bootloader
# This is the baud rate to use with the bootloader
BOOTLOADER_BAUD = 9600


# Source files
# List C/C++/Assembly source files:
# (list all files to compile, e.g. 'a.c b.cpp as.S'):
# Use .cc, .cpp or .C suffix for C++ files, use .S
# (NOT .s !!!) for assembly source code files.
PRJSRC = src/device/deviceconfig.c \
	src-lib/lcd/lcd.c \
	src-lib/uart/uart.c \
	src/control/frontbuttoncontrol.c \
	src/ui/lights.c \
	src/ui/menu.c \
	src/functions/hello.c \
	src/functions/countExtPorts.c \
	src/functions/showDACValue.c \
	src/functions/showFastPorts.c \
	src/options/uartonoff.c \
    src/options/saveeeprom.c \
	src/main.c

# additional includes (e.g. -I/path/to/mydir)
INC = 

# libraries to link in (e.g. -lmylib)
LIBS = 

# Optimization level,
# use s (size opt), 1, 2, 3 or 0 (off)
OPTLEVEL = s




### You should not have to touch anything below this line ###

SHELL = ./makefile.shell

# HEXFORMAT -- format for .hex file output
HEXFORMAT = ihex

# compiler
CFLAGS = -I. $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL)  \
         -DF_CPU=$(F_CPU)                          \
         -fpack-struct -fshort-enums               \
         -funsigned-bitfields -funsigned-char      \
         -Wall -Wstrict-prototypes                 \
         -Wa,-ahlms=$(firstword                    \
                    $(filter %.lst, $(<:.c=.lst)))

# c++ specific flags
CPPFLAGS = -fno-exceptions                 \
           -DF_CPU=$(F_CPU)                \
           -Wa,-ahlms=$(firstword          \
           $(filter %.lst, $(<:.cpp=.lst)) \
           $(filter %.lst, $(<:.cc=.lst))  \
           $(filter %.lst, $(<:.C=.lst)))

# assembler
ASMFLAGS = -I. $(INC) -mmcu=$(MCU)          \
           -x assembler-with-cpp            \
           -Wa,-gstabs,-ahlms=$(firstword   \
           $(<:.S=.lst) $(<.s=.lst))

# linker
LDFLAGS = -Wl,-Map,$(TRG).map -mmcu=$(MCU)  \
          -L "$${LIBPATH}"                  \
          -lm $(LIBS)

##### executables ####
#/usr/local/CrossPack-AVR/bin/
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AVRDUDE = avrdude
REMOVE = rm -f

##### automatic target names ####
TRG=$(PROJECTNAME).out
DUMPTRG=$(PROJECTNAME).s

HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

# Start by splitting source files by type
#  C++
CPPFILES=$(filter %.cpp, $(PRJSRC))
CCFILES=$(filter %.cc, $(PRJSRC))
BIGCFILES=$(filter %.C, $(PRJSRC))
#  C
CFILES=$(filter %.c, $(PRJSRC))
#  Assembly
ASMFILES=$(filter %.S, $(PRJSRC))

# List all object files we need to create
OBJDEPS=$(CFILES:.c=.o)     \
        $(CPPFILES:.cpp=.o) \
        $(BIGCFILES:.C=.o)  \
        $(CCFILES:.cc=.o)   \
        $(ASMFILES:.S=.o)

# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

# All the possible generated assembly
# files (.s files)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.s))

.SUFFIXES : .c .cc .cpp .C .o .out .s .S \
            .hex .ee.hex .h .hh .hpp

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean
all: $(TRG) $(HEXTRG)

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS)

#### Generating assembly ####
# asm from C
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

# asm from (hand coded) asm
%.s: %.S
	$(CC) -S $(ASMFLAGS) $< > $@

# asm from C++
.cpp.s .cc.s .C.s :
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $@

#### Generating object files ####
# object from C
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# object from C++ (.cc, .cpp, .C files)
.cc.o .cpp.o .C.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# object from asm
.S.o :
	$(CC) $(ASMFLAGS) -c $< -o $@

#### Generating hex files ####
# hex files from elf
.out.hex:
	$(OBJCOPY) -j .text                    \
	           -j .data                    \
	           -O $(HEXFORMAT) $< $@

.out.ee.hex:
	$(OBJCOPY) -j .eeprom                     \
	           --change-section-lma .eeprom=0 \
	           -O $(HEXFORMAT) $< $@

#### Bootloader ####
bootloader:
	bootloader -p $(HEXROMTRG) -d $(BOOTLOADER_PORT) -b $(BOOTLOADER_BAUD)

bootloader_gui:
	"AVR Builder" --bootloader --file="$(shell pwd)/$(HEXROMTRG)" --port=$(BOOTLOADER_PORT) --baud=$(BOOTLOADER_BAUD)

#### Upload ####
upload:
	$(AVRDUDE) -c $(PROGRAMMER) -B$(BOOTLOADER_BAUD) -Uflash:w:$(HEXROMTRG) -p $(PROGRAMMER_MCU)

#### screen terminal ####
term:
	screen $(BOOTLOADER_PORT) $(BOOTLOADER_TERM)

#### Information ####
info:
	which $(CC)
	$(CC) -v
	avr-ld -v

#### Cleanup ####
clean:
	$(REMOVE) $(TRG) $(TRG).map $(DUMPTRG)
	$(REMOVE) $(OBJDEPS)
	$(REMOVE) $(LST)
	$(REMOVE) $(GENASMFILES)
	$(REMOVE) $(HEXTRG)


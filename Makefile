AVR_GCC = avr-gcc
AVR_OBJ = avr-objcopy
GCC_ARG = -Wall -Os -mmcu=atmega328p
OBJ_ARG = -O ihex -R .eeprom
NAME    = avrmorse
STDLIB  =

INCDIR  = include
LIBDIR  = lib
OBJDIR  = build
SRCDIR  = src
BINDIR  = bin

AVRDUDE = avrdude
DUDEARG = -b 115200 -c arduino -D -p atmega328p
DEVPORT = /dev/ttyACM0
OBJHEX	= $(NAME).hex

HEADER  =
OBJ     = avrmorse.o
DEPS    = $(patsubst %, $(INCDIR)/%,$(HEADER))
BIN     = $(patsubst %, $(OBJDIR)/%,$(OBJ))
HEX		= $(patsubst %, $(OBJDIR)/%,$(OBJHEX))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(AVR_GCC) -c -o $@ $< $(GCC_ARG)
	
$(BINDIR)/$(NAME).elf: $(BIN)
	$(AVR_GCC) -o $@ $^ $(GCC_ARG) $(STDLIB)
	
$(OBJDIR)/$(NAME).hex: $(BINDIR)/$(NAME).elf
	$(AVR_OBJ) $(OBJ_ARG) $< $@

.PHONY: clean

all: $(DEPS) $(BINDIR) $(HEX)

clean:
	@rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~
	@rm -f $(BINDIR)/*.elf
	@rm -f $(OBJDIR)/*.hex
	
burn: $(HEX)
	$(AVRDUDE) $(DUDEARG) -P $(DEVPORT) -U flash:w:$(OBJHEX)

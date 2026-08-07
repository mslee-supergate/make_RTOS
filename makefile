MCPU= cortex-a8
TARGET= rvpb

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
LIBGCC = $(shell $(CC) -print-libgcc-file-name)

LINKER_SCRIPT = ./navilos.ld
MAP_FILE = build/navilos.map

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.o, $(ASM_SRCS))

VPATH = boot \
		hal/$(TARGET) \
		lib \
		kernel

C_SRCS = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard lib/*.c))
C_SRCS += $(notdir $(wildcard kernel/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

INC_DIRS = include hal hal/$(TARGET) lib kernel
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

navilos = build/navilos.axf
navilos_bin = build/navilos.bin

.PHONY: all clean run debug gdb

all: $(navilos)

clean:
	@rm -fr build

run: $(navilos)
	qemu-system-arm -M realview-pb-a8 -kernel $(navilos) -nographic

debug: $(navilos)
	qemu-system-arm -M realview-pb-a8 -kernel $(navilos) -S -gdb tcp::1234,ipv4

gdb:
	gdb-multiarch build/navilos.axf

$(navilos): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $@ $(ASM_OBJS) \
		$(C_OBJS) $(LIBGCC) -Map=$(MAP_FILE)
	$(OC) -O binary $@ $(navilos_bin)

build/%.o: boot/%.S
	@mkdir -p build
	$(CC) -g -mcpu=$(MCPU) $(INC_FLAGS) -c -o $@ $<

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -g -mcpu=$(MCPU) $(INC_FLAGS) -c -o $@ $<

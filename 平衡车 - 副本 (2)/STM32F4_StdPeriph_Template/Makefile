PROJECT := STM32F4_StdPeriph_Template
BUILD_DIR := build

PREFIX ?= arm-none-eabi-
CC := $(PREFIX)gcc
AS := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
SIZE := $(PREFIX)size

# brew 的 arm-none-eabi-gcc 不带 newlib，这里指向手动提取的 newlib（见项目记忆）
NEWLIB_DIR := /opt/homebrew/arm-none-eabi-newlib

CPU_FLAGS := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS := $(CPU_FLAGS) -std=gnu11 -O0 -g3 -Wall -Wextra -ffunction-sections -fdata-sections
CFLAGS += -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER
CFLAGS += -ICORE -IUSER -IFWLIB/inc -Idrive -I$(NEWLIB_DIR)/include
LDFLAGS := $(CPU_FLAGS) -nostartfiles -TSTM32F407ZGTx_FLASH.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map -L$(NEWLIB_DIR)/lib/thumb/v7e-m+fp/softfp
LDLIBS := --specs=$(NEWLIB_DIR)/lib/thumb/v7e-m+fp/softfp/nosys.specs -lc -lm -lnosys

# F407 只有 FSMC 没有 FMC（FMC 是 F427/F429 的 SDRAM 控制器），
# stm32f4xx_fmc.c 编译会报 FMC_Bank2 等未定义，这里排除掉（与 Keil 工程一致）
FWLIB_SRC := $(filter-out FWLIB/src/stm32f4xx_fmc.c, $(wildcard FWLIB/src/*.c))
C_SOURCES := USER/main.c USER/stm32f4xx_it.c USER/system_stm32f4xx.c $(FWLIB_SRC) $(wildcard drive/*.c)
OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
STARTUP_OBJECT := $(BUILD_DIR)/CORE/startup_stm32f407xx_gcc.o

.PHONY: all clean flash

all: $(BUILD_DIR)/$(PROJECT).hex

$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS) $(STARTUP_OBJECT) STM32F407ZGTx_FLASH.ld
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(STARTUP_OBJECT) $(LDLIBS)
	$(SIZE) $@

$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(STARTUP_OBJECT): CORE/startup_stm32f407xx_gcc.s
	@mkdir -p $(dir $@)
	$(AS) $(CPU_FLAGS) -x assembler-with-cpp -c $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

flash: $(BUILD_DIR)/$(PROJECT).hex
	STM32_Programmer_CLI -c port=SWD -w $< -v -rst

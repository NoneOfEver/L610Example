################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
L610Example.hex \

SECONDARY_LIST += \
L610Example.lst \

SECONDARY_SIZE += \
L610Example.siz \


# 所有目标
all: L610Example.elf secondary-outputs

# 工具调用
L610Example.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -T "C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"L610Example.map" --specs=nano.specs --specs=nosys.specs -o "L610Example.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
L610Example.hex: L610Example.elf
	@	riscv-none-embed-objcopy -O ihex "L610Example.elf"  "L610Example.hex"
	@	@
L610Example.lst: L610Example.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble "L610Example.elf" > "L610Example.lst"
	@	@
L610Example.siz: L610Example.elf
	@	riscv-none-embed-size --format=berkeley "L610Example.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) L610Example.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

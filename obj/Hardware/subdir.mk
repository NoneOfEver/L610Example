################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/usart.c 

OBJS += \
./Hardware/usart.o 

C_DEPS += \
./Hardware/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\Debug" -I"C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\Core" -I"C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\User" -I"C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\Peripheral\inc" -I"C:\Users\noneo\Desktop\智能购物车\【工程】CH32V307V-EVT连接腾讯云收发数据工程\L610Example\Hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


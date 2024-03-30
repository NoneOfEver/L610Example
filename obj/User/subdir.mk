################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/L610.c \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/L610.o \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/L610.d \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"C:\Users\noneo\Desktop\���ܹ��ﳵ\�����̡�CH32V307V-EVT������Ѷ���շ����ݹ���\L610Example\Debug" -I"C:\Users\noneo\Desktop\���ܹ��ﳵ\�����̡�CH32V307V-EVT������Ѷ���շ����ݹ���\L610Example\Core" -I"C:\Users\noneo\Desktop\���ܹ��ﳵ\�����̡�CH32V307V-EVT������Ѷ���շ����ݹ���\L610Example\User" -I"C:\Users\noneo\Desktop\���ܹ��ﳵ\�����̡�CH32V307V-EVT������Ѷ���շ����ݹ���\L610Example\Peripheral\inc" -I"C:\Users\noneo\Desktop\���ܹ��ﳵ\�����̡�CH32V307V-EVT������Ѷ���շ����ݹ���\L610Example\Hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


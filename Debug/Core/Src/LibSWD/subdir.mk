################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LibSWD/libswd_bin.c \
../Core/Src/LibSWD/libswd_bitgen.c \
../Core/Src/LibSWD/libswd_bus.c \
../Core/Src/LibSWD/libswd_cmd.c \
../Core/Src/LibSWD/libswd_cmdq.c \
../Core/Src/LibSWD/libswd_core.c \
../Core/Src/LibSWD/libswd_dap.c \
../Core/Src/LibSWD/libswd_debug.c \
../Core/Src/LibSWD/libswd_drv.c \
../Core/Src/LibSWD/libswd_error.c \
../Core/Src/LibSWD/libswd_externs.c \
../Core/Src/LibSWD/libswd_log.c \
../Core/Src/LibSWD/libswd_memap.c 

OBJS += \
./Core/Src/LibSWD/libswd_bin.o \
./Core/Src/LibSWD/libswd_bitgen.o \
./Core/Src/LibSWD/libswd_bus.o \
./Core/Src/LibSWD/libswd_cmd.o \
./Core/Src/LibSWD/libswd_cmdq.o \
./Core/Src/LibSWD/libswd_core.o \
./Core/Src/LibSWD/libswd_dap.o \
./Core/Src/LibSWD/libswd_debug.o \
./Core/Src/LibSWD/libswd_drv.o \
./Core/Src/LibSWD/libswd_error.o \
./Core/Src/LibSWD/libswd_externs.o \
./Core/Src/LibSWD/libswd_log.o \
./Core/Src/LibSWD/libswd_memap.o 

C_DEPS += \
./Core/Src/LibSWD/libswd_bin.d \
./Core/Src/LibSWD/libswd_bitgen.d \
./Core/Src/LibSWD/libswd_bus.d \
./Core/Src/LibSWD/libswd_cmd.d \
./Core/Src/LibSWD/libswd_cmdq.d \
./Core/Src/LibSWD/libswd_core.d \
./Core/Src/LibSWD/libswd_dap.d \
./Core/Src/LibSWD/libswd_debug.d \
./Core/Src/LibSWD/libswd_drv.d \
./Core/Src/LibSWD/libswd_error.d \
./Core/Src/LibSWD/libswd_externs.d \
./Core/Src/LibSWD/libswd_log.d \
./Core/Src/LibSWD/libswd_memap.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/LibSWD/libswd_bin.o: ../Core/Src/LibSWD/libswd_bin.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_bin.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_bitgen.o: ../Core/Src/LibSWD/libswd_bitgen.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_bitgen.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_bus.o: ../Core/Src/LibSWD/libswd_bus.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_bus.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_cmd.o: ../Core/Src/LibSWD/libswd_cmd.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_cmd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_cmdq.o: ../Core/Src/LibSWD/libswd_cmdq.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_cmdq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_core.o: ../Core/Src/LibSWD/libswd_core.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_core.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_dap.o: ../Core/Src/LibSWD/libswd_dap.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_dap.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_debug.o: ../Core/Src/LibSWD/libswd_debug.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_debug.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_drv.o: ../Core/Src/LibSWD/libswd_drv.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_drv.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_error.o: ../Core/Src/LibSWD/libswd_error.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_error.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_externs.o: ../Core/Src/LibSWD/libswd_externs.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_externs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_log.o: ../Core/Src/LibSWD/libswd_log.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_log.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/LibSWD/libswd_memap.o: ../Core/Src/LibSWD/libswd_memap.c Core/Src/LibSWD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -DDEBUG -c -I../Core/Inc -I"C:/Users/varma.mudunuri/STM32CubeIDE/L073RZ/Core/Src/LibSWD" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LibSWD/libswd_memap.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


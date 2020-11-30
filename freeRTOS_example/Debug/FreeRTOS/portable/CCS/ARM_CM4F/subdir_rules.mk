################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/portable/CCS/ARM_CM4F/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/sinan/workspace_v10/freeRTOS_example/libraries" --include_path="/Users/sinan/workspace_v10/freeRTOS_example/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="/Applications/ti/ccs1011/ccs/ccs_base/arm/include" --include_path="/Users/sinan/workspace_v10/freeRTOS_example/FreeRTOS/include" --include_path="/Applications/ti/ccs1011/ccs/ccs_base/arm/include/CMSIS" --include_path="/Users/sinan/workspace_v10/freeRTOS_example" --include_path="/Applications/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --printf_support=nofloat --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/portable/CCS/ARM_CM4F/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/sinan/workspace_v10/freeRTOS_example/libraries" --include_path="/Users/sinan/workspace_v10/freeRTOS_example/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="/Applications/ti/ccs1011/ccs/ccs_base/arm/include" --include_path="/Users/sinan/workspace_v10/freeRTOS_example/FreeRTOS/include" --include_path="/Applications/ti/ccs1011/ccs/ccs_base/arm/include/CMSIS" --include_path="/Users/sinan/workspace_v10/freeRTOS_example" --include_path="/Applications/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --printf_support=nofloat --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



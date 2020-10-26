################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/sinan/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/Applications/ti/ccs930/ccs/ccs_base/arm/include" --include_path="/Applications/ti/ccs930/ccs/ccs_base/arm/include/CMSIS" --include_path="/Users/sinan/Google Drive (kasim.sinan.yildirim@gmail.com)/embedded systems course/TI CSS Workspace/driverLib-blink" --include_path="/Applications/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



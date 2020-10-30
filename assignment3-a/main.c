#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* calibration difference for the temperature sensor */
float calDifference;
uint32_t cal30;

/* enable on-chip temperature sensor */
void _temperatureConfigure()
{
    uint32_t cal85;

    /* Setting reference voltage to 2.5 and enabling temperature sensor */
    REF_A_enableTempSensor();
    REF_A_setReferenceVoltage(REF_A_VREF2_5V);
    REF_A_enableReferenceVoltage();

    cal30 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
    SYSCTL_30_DEGREES_C);
    cal85 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
    SYSCTL_85_DEGREES_C);
    calDifference = cal85 - cal30;
}

/* port configuration steps here */
void _portConfigure()
{
    // set Port 1 Pin 1 (button) as input port with pull-up resistor enabled
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    // LED Configuration (P1.0 as output for the RED LED)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    // Red LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);

    // Green LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);

    // Blue LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);

    // enable P1.1 interrupt
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    // enable PORT 1 interrupt
    Interrupt_enableInterrupt(INT_PORT1);
}

void _ADCConfigure()
{
    /* Initializing ADC (MCLK/1/1) with temperature sensor routed */
    ADC14_enableModule();
    /* init ADC so that it is configured to sample the temperature sensor */
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
    ADC_TEMPSENSEMAP);

    /* Configuring ADC Memory (ADC_MEM0 A22 (Temperature Sensor) in repeat
     * mode).
     */
    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_INTBUF_VREFNEG_VSS,
    ADC_INPUT_A22,false);

    /* Configuring the sample/hold time for 192 */
    ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_192, ADC_PULSE_WIDTH_192);

    /* Enabling sample timer in auto iteration mode and interrupts*/
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION); /* select manual trigger for the sampling */
    ADC14_enableInterrupt(ADC_INT0);

    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);

    /* make ADC active */
    ADC14_enableConversion();
}

/**
 * main.c
 */
void main(void)
{
    // stop watchdog timer
    WDT_A_holdTimer();

    // configure peripherals
    _portConfigure();
    _temperatureConfigure();
    _ADCConfigure();

    while (1)
    {
        // put MCU into low-power mode (suspend CPU);
        PCM_gotoLPM0();
    }
}

bool adc_request = false;

// interrupt handler routine for PORT1
void PORT1_IRQHandler()
{
    uint_fast16_t status;

    // get which pin triggered the interrupt
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    // clear the interrupt flag register of Port 1
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // check if P1.1 triggered
    if (status & GPIO_PIN1)
    {
        // toggle LED
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

        if(adc_request != true){
            adc_request = true;
            // take a sample from temperature sensor
            ADC14_toggleConversionTrigger();
        }
    }
}

// interrupt handler routine for ADC
void ADC14_IRQHandler(void)
{
    uint64_t status;
    int16_t conRes;
    float tempC;

    // check which ADC channel triggered the interrupt
    status = ADC14_getEnabledInterruptStatus();
    // clear the interrupt flag register of ADC
    ADC14_clearInterruptFlag(status);

    // if interrupt source is ADC channel 0 (temperature measurement)
    if(status & ADC_INT0)
    {
        conRes = ((ADC14_getResult(ADC_MEM0) - cal30) * 55);
        tempC = (conRes / calDifference) + 30.0f;

        if (tempC < 20.0f)
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0); // toggle RED
        else if (tempC >= 20.0f && tempC < 22.0f)
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1); // toggle GREEN
        else
            GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2); // toggle BLUE

        adc_request = false;
    }

}

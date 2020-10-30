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

/* Timer_A UpMode Configuration Parameter */
const Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_ACLK,              // ACKL = 32Khz
        TIMER_A_CLOCKSOURCE_DIVIDER_1,         // ACKL/1 = 32 Khz
        30000,                                 // 30000 tick period (for almost 1000 ms operation)
        TIMER_A_TAIE_INTERRUPT_DISABLE,        // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,   // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                       // Clear value
};

// this configures timer so that it counts from 0 to the TIMER_PERIOD value
void _timerUpModeConfigure(){

    // configure the TIMER_A0 timer (16-bit timer)
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    // enable Timer_A0 capture and compare interrupt
    Interrupt_enableInterrupt(INT_TA0_0);

    // run the timer
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
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
    _timerUpModeConfigure();

    while (1)
    {
        // put MCU into low-power mode (suspend CPU);
        PCM_gotoLPM0();
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
    }

}

// timer interrupt handler
void TA0_0_IRQHandler(){
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    // toggle LED
    GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
    // take a sample from temperature sensor
    ADC14_toggleConversionTrigger();
}

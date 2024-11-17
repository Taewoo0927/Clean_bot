#ifndef IO_H
#define IO_H

#define LAUNCHPAD

typedef enum
{
#if defined(LAUNCHPAD) // Launchpad (MSP430G2553IN20)
    IO_TEST_LED,
    IO_UART_RXD,
    IO_UART_TXD,
    IO_UNUSED_1,
    IO_UNUSED_2,
    IO_UNUSED_3,
    IO_UNUSED_4,
    IO_UNUSED_5,
    IO_UNUSED_6,
    IO_UNUSED_7,
    IO_UNUSED_8,
    IO_UNUSED_9,
    IO_UNUSED_10,
    IO_UNSUED_11,
    IO_UNUSED_12,
    IO_UNUSED_13,
#elif defined(CLEAN_BOT) // Clean_bot (MSP430G2553IPW28)
    IO_XSHUT_LEFT,
    IO_XSHUT_RIGHT,
    IO_XSHUT_FRONT,
    IO_INTR_FRONT,
    IO_DRV_SLEEP,
    IO_DRV_PH,
    IO_DRV_EN,
    IO_SBW_TCK,
    IO_UART_RX,
    IO_UART_TX,
    IO_GPIO_1_0,
    IO_GPIO_1_3,
    IO_GPIO_1_4,
    IO_GPIO_1_5,
    IO_GPIO_3_4,
    IO_SCL,
    IO_SDA,
    IO_ML_PWM,
    IO_ML_CH1,
    IO_ML_CH2,
    IO_MR_PWM,
    IO_MR_CH1,
    IO_MR_CH2,
    IO_IR_RECEIVER,
    IO_DEBUGG_CONN
#endif
} io_e;


#endif //IO_H


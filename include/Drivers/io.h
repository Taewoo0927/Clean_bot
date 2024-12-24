#ifndef IO_H
#define IO_H

#define LAUNCHPAD

typedef enum
{
    IO_10 = 10,
    IO_11 = 11,
    IO_12 = 12,
    IO_13 = 13,
    IO_14 = 14,
    IO_15 = 15,
    IO_16 = 16,
    IO_17 = 17,
    IO_20 = 20,
    IO_21 = 21,
    IO_22 = 22,
    IO_23 = 23,
    IO_24 = 24,
    IO_25 = 25,
    IO_26 = 26,
    IO_27 = 27,
} io_generic_e;
// Pins
typedef enum
{
#if defined(LAUNCHPAD) // Launchpad (MSP430G2553IN20)
    IO_TEST_LED = IO_10,
    IO_UART_RXD = IO_11,
    IO_UART_TXD = IO_12,
    IO_UNUSED_1 = IO_13,
    IO_UNUSED_2 = IO_14,
    IO_UNUSED_3 = IO_15,
    IO_UNUSED_4 = IO_16,
    IO_UNUSED_5 = IO_17,
    IO_UNUSED_6 = IO_20,
    IO_UNUSED_7 = IO_21,
    IO_UNUSED_8 = IO_22,
    IO_UNUSED_9 = IO_23,
    IO_UNUSED_10 = IO_24,
    IO_UNSUED_11 = IO_25,
    IO_UNUSED_12 = IO_26,
    IO_UNUSED_13 = IO_27,
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
    IO_DEBUGG_CONN,
#endif
} io_e;

// Select register - mode
typedef enum
{
    IO_SEL_GPIO,
    IO_SEL_ALT1,
    IO_SEL_ALT2,
    IO_SEL_ALT3,
} io_sel_e;

// Direction register - mode
typedef enum
{
    IO_DIR_OP,
    IO_DIR_IP,
} io_dir_e;

// Pull-up/Pull-down register - mode
typedef enum
{
    IO_RESISTOR_DISABLED,
    IO_RESISTOR_ENABLED,
} io_resistor_e;

typedef enum
{
    IO_PULL_STATE_LOW,  //(Pull-down)
    IO_PULL_STATE_HIGH, //(Pull-up)
} io_out_e;

// Input register - mode
typedef enum
{
    IO_INPUT_LOW,
    IO_INPUT_HIGH,
} io_input_state_e;

// io configuration - mode
struct io_configuration
{
    io_sel_e select;
    io_resistor_e resistor;
    io_dir_e direction;
    io_out_e output;
};

// Function definitions
void io_configuration(io_e io, const struct io_configuration *config);
void io_set_sel(io_e io, io_sel_e sel);
void io_set_dir(io_e io, io_dir_e dir);
void io_set_resistor(io_e io, io_resistor_e resistor);
void io_set_output(io_e io, io_out_e out);
io_input_state_e io_get_input(io_e io);

#endif // IO_H

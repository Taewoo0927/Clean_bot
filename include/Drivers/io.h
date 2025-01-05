#ifndef IO_H
#define IO_H

// apply code for launchpad
#define LAUNCHPAD

/* Creating mask to find port */
#define IO_PORT(io) (((io) / 10) - 1)        // Extract Port number, -1 is to account for lookup table 0 -> P1, 1 -> P2
#define IO_PIN_IDX(io) (((io) % 10))         // Extract Pin Index
#define IO_PIN_BIT(io) (1 << IO_PIN_IDX(io)) // Shift to compute Pin BIT
#define IO_PORT_SIZE 2
#define IO_PIN_SIZE 28 // port10 to port 27 so end -> 28
#define IO_PIN_CNT 8   // count of pin numbers - 10~17 is 8 and 20~27 is 8 so total 16
#define UNUSED_PINS {IO_SEL_GPIO, IO_RESISTOR_ENABLED, IO_DIR_OP, IO_PULL_STATE_LOW}
#define IO_OUTPUT_TEST {IO_SEL_GPIO, IO_RESISTOR_DISABLED, IO_DIR_OP, IO_PULL_STATE_LOW}

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
    IO_UNUSED_11 = IO_25,
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
struct io_configuration_s
{
    io_sel_e select;
    io_resistor_e resistor;
    io_dir_e direction;
    io_out_e output;
};

typedef enum
{
    IO_EDGE_FALLING,
    IO_EDGE_RISING
} io_edge_e;

typedef enum
{
    IO_PORT1,
    IO_PORT2,
} io_port_e;

// Function definitions
void io_init(void);
void io_configuration(io_e io, const struct io_configuration_s *config);
void io_set_sel(io_e io, io_sel_e sel);
void io_set_dir(io_e io, io_dir_e dir);
void io_set_resistor(io_e io, io_resistor_e resistor);
void io_set_output(io_e io, io_out_e out);
io_input_state_e io_get_input(io_e io);

// Interrupt function definitions
typedef void (*isr_function)(void); // pointer function, basically I can point to different function and call isr_function
void io_configure_interrupt(io_e io, io_edge_e edge, isr_function isr);
void io_interrupt_flag(io_e io);
void io_interrupt_enable(io_e io);
void io_disable_interrupt(io_e io);
void io_enable_interrupt(io_e io);

#endif // IO_H

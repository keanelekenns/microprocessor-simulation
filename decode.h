#include <stdint.h>
#define SSS_MASK 0x07
#define DDD_MASK 0x38
#define DDD_SHIFT 3
#define MEM 0x07

// Indicates T-state should be skipped
#define SKIP 0x00
// Indicates T-state should take time but do nothing
#define IDLE 0xFF

// Control values for T1
#define PCL_OUT     0x01
#define REGL_OUT    0x02
#define REGA_OUT    0x03

// Control values for T2
#define PCH_OUT  0x01
#define REGH_OUT 0x02
#define REGA_OUT 0x03

// Control values for T3
#define FETCH                    0x01
#define PUSH_STACK               0x02
#define FETCH_HALT               0x03
#define REGB_OUT                 0x04
#define DATA_TO_REGB             0x05
#define LOW_ADD_TO_REGB          0x06
#define REGB_TO_OUT              0x07
#define LOWER_ADDR_TO_REGB       0x08
#define HIGHER_ADDR_TO_REGA      0x09
#define HIGHER_ADDR_TO_REGA_COND 0x0A

// Control values for T4
#define SSS_TO_REGB     0x01
#define POP_STACK       0x02
#define POP_STACK_C     0x03
#define REG_A_TO_PCH    0x04
#define COND_FF_OUT     0x05

// Control values for T5
#define REGB_TO_DDD     0x01
#define ALU_OP          0x02
#define ROTATE_REGA     0x03
#define REGB_TO_PCL     0x04
#define REGB_TO_REGA    0x05

// ALU Operations
#define ADD     0x01
#define ADD_C   0x02
#define SUB     0x03
#define SUB_B   0x04
#define L_AND   0x05
#define L_XOR   0x06
#define L_OR    0x07
#define CMP     0x08
#define INC     0x09
#define DEC     0x0A
#define RLC     0x0B
#define RRC     0x0C
#define RAL     0x0D
#define RAR     0x0E

// Next type of fetch
#define OPCODE      0x01
#define IMMEDIATE   0x02
#define LOW_ADDR    0x03
#define HIGH_ADDR   0x04
#define IO          0x05

// Memory operation to complete
#define MEM_READ    0x01
#define MEM_WRITE   0x02

// Contains control signals for instruction execution
typedef struct DecodeControl {
    uint8_t current_cycle;
    uint8_t cycle_length;
    uint8_t source_register;
    uint8_t destination_register;
    uint8_t t1_control[3];
    uint8_t t2_control[3];
    uint8_t t3_control[3];
    uint8_t t4_control[3];
    uint8_t t5_control[3];
    uint8_t alu_operation;
} DecodeControl;

// Decodes based on opcode
DecodeControl decode(DecodeControl decode_control, uint8_t opcode);

DecodeControl init_decode_control(DecodeControl decode_control);

// Set control for ALU operations on an scratch pad register
DecodeControl set_control_scratch_pad(DecodeControl decode_control);

// Set control for an ALU operation on a value stored in memory
DecodeControl set_control_memory(DecodeControl decode_control);

// Set control for an ALU operation on a value stored in the next instruction byte
DecodeControl set_control_immediate(DecodeControl decode_control);

// Set control for an accumulator rotate operation
DecodeControl set_control_rotate(DecodeControl decode_control);

uint8_t check_in_sequence(uint8_t value, uint8_t start, uint8_t end, uint8_t increment);

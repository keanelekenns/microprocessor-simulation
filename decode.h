#include <stdint.h>
#define SSS_MASK 0x07
#define DDD_MASK 0x38
#define DDD_SHIFT 3
#define MEM 0x07

#define SKIP 0x00

// Control values for T1
#define PCL_OUT     0x01
#define REGL_OUT    0x02
#define REGA_OUT    0x04

// Control values for T2
#define PCH_OUT  0x01
#define REGH_OUT 0x02
#define REGA_OUT 0x04

// Control values for T3
#define FETCH           0x01
#define PUSH_STACK      0x02
#define FETCH_HALT      0x04
#define REGB_OUT        0x08
#define DATA_TO_REGB    0x10
#define LOW_ADD_TO_REGB 0x20
#define REGB_TO_OUT     0x40

// Control values for T4
#define SSS_TO_REGB     0x01
#define POP_STACK       0x02
#define POP_STACK_C     0x04
#define REG_A_TO_PCH    0x08
#define COND_FF_OUT     0x10
#define IDLE            0x20

// Control values for T5
#define REGB_TO_DDD     0x01
#define ADD_OP          0x02
#define ROTATE_REGA     0x04
#define REGB_TO_PCL     0x08
#define REGB_TO_REGA    0x10

// ALU Operations
#define ADD     0x01
#define SUB     0x02
#define L_AND   0x04
#define L_XOR   0x08
#define L_OR    0x10
#define CMP     0x20
#define INC     0x40
#define DEC     0x80

// Next type of fetch
#define OPCODE      0x01
#define IMMEDIATE   0x02
#define LOW_ADDR    0x04
#define HIGH_ADDR   0x08
#define IO          0x10

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

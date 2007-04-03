#ifndef OPCODES_H
#define OPCODES_H

#define ADC_I 0x69
#define ADC_Z 0x65
#define ADC_ZX 0x75
#define ADC_A 0x6D
#define ADC_AX 0x7D
#define ADC_AY 0x79
#define ADC_IX 0x61
#define ADC_IY 0x71

#define AND_I 0x29
#define AND_Z 0x25
#define AND_ZX 0x35
#define AND_A 0x2D
#define AND_AX 0x3D
#define AND_AY 0x39
#define AND_IX 0x21
#define AND_IY 0x31

#define ASL_IM 0x0A
#define ASL_Z 0x06
#define ASL_ZX 0x16
#define ASL_A 0x0E
#define ASL_AX 0x1E

#define BCC_I 0x90
#define BCS_I 0xB0
#define BEQ_I 0xF0

#define BIT_Z 0x24
#define BIT_A 0x2C

#define BMI_I 0x30
#define BNE_I 0xD0
#define BPL_I 0x10

#define BRK_IM 0x00

#define BVC_I 0x50
#define BVS_I 0x70

#define CLC_IM 0x18
#define CLD_IM 0xD8
#define CLI_IM 0x58
#define CLV_IM 0xB8

#define CMP_I 0xC9
#define CMP_Z 0xC5
#define CMP_ZX 0xD5
#define CMP_A 0xCD
#define CMP_AX 0xDD
#define CMP_AY 0xD9
#define CMP_IX 0xC1
#define CMP_IY 0xD1

#define CPX_I 0xE0
#define CPX_Z 0xE4
#define CPX_A 0xEC

#define CPY_I 0xC0
#define CPY_Z 0xC4
#define CPY_A 0xCC

#define DEC_Z 0xC6
#define DEC_ZX 0xD6
#define DEC_A 0xCE
#define DEC_AX 0xDE

#define DEX_IM 0xCA
#define DEY_IM 0x88

#define EOR_I 0x49
#define EOR_Z 0x45
#define EOR_ZX 0x55
#define EOR_A 0x4D
#define EOR_AX 0x5D
#define EOR_AY 0x59
#define EOR_IX 0x41
#define EOR_IY 0x51

#define INC_Z 0xE6
#define INC_ZX 0xF6
#define INC_A 0xEE
#define INC_AX 0xFE

#define INX_IM 0xE8
#define INY_IM 0xC8

#define JMP_A 0x4C
#define JMP_IN 0x6C

#define JSR_A 0x20

#define LDA_I 0xA9
#define LDA_Z 0xA5
#define LDA_ZX 0xB5
#define LDA_A 0xAD
#define LDA_AX 0xBD
#define LDA_AY 0xB9
#define LDA_IX 0xA1
#define LDA_IY 0xB1

#define LDX_I 0xA2
#define LDX_Z 0xA6
#define LDX_ZY 0xB6
#define LDX_A 0xAE
#define LDX_AY 0xBE

#define LDY_I 0xA0
#define LDY_Z 0xA4
#define LDY_ZX 0xB4
#define LDY_A 0xAC
#define LDY_AX 0xBC

#define LSR_AC 0x4A
#define LSR_Z 0x46
#define LSR_ZX 0x56
#define LSR_A 0x4E
#define LSR_AX 0x5E

#define NOP_IM 0xEA

#define ORA_I 0x09
#define ORA_Z 0x05
#define ORA_ZX 0x15
#define ORA_A 0x0D
#define ORA_AX 0x1D
#define ORA_AY 0x19
#define ORA_IX 0x01
#define ORA_IY 0x11

#define PHA_IM 0x48
#define PHP_IM 0x08

#define PLA_IM 0x68
#define PLP_IM 0x28

#define ROL_AC 0x2A
#define ROL_Z 0x26
#define ROL_ZX 0x36
#define ROL_A 0x2E
#define ROL_AX 0x3E

#define ROR_AC 0x6A
#define ROR_Z 0x66
#define ROR_ZX 0x76
#define ROR_A 0x6E
#define ROR_AX 0x7E

#define RTI_IM 0x40
#define RTS_IM 0x60

#define SBC_I 0xE9
#define SBC_Z 0xE5
#define SBC_ZX 0xF5
#define SBC_A 0xED
#define SBC_AX 0xFD
#define SBC_AY 0xF9
#define SBC_IX 0xE1
#define SBC_IY 0xF1

#define SEC_IM 0x38
#define SED_IM 0xF8
#define SEI_IM 0x78

#define STA_Z 0x85
#define STA_ZX 0x95
#define STA_A 0x8D
#define STA_AX 0x9D
#define STA_AY 0x99
#define STA_IX 0x81
#define STA_IY 0x91

#define STX_Z 0x86
#define STX_ZY 0x96
#define STX_A 0x8E

#define STY_Z 0x84
#define STY_ZY 0x94
#define STY_A 0x8C

#define TAX_IM 0xAA
#define TAY_IM 0xA8

#define TSX_IM 0xBA
#define TXA_IM 0x8A
#define TXS_IM 0x9A
#define TYA_IM 0x98

#endif

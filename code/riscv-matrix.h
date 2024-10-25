/* SCALAR REGISTERS*/
#define X0                            "00000"
#define X1                            "00001"
#define X2                            "00010"
#define X3                            "00011"
#define X4                            "00100"
#define X5                            "00101"
#define X6                            "00110"
#define X7                            "00111"
#define X8                            "01000"
#define X9                            "01001"
#define X10                           "01010"
#define X11                           "01011"
#define X12                           "01100"
#define X13                           "01101"
#define X14                           "01110"
#define X15                           "01111"
#define X16                           "10000"
#define X17                           "10001"
#define X18                           "10010"
#define X19                           "10011"
#define X20                           "10100"
#define X21                           "10101"
#define X22                           "10110"
#define X23                           "10111"
#define X24                           "11000"
#define X25                           "11001"
#define X26                           "11010"
#define X27                           "11011"
#define X28                           "11100"
#define X29                           "11101"
#define X30                           "11110"
#define X31                           "11111"
#define A0                            X10
#define A1                            X11
#define A2                            X12
#define A3                            X13
#define A4                            X14
#define A5                            X15
#define A6                            X16
#define A7                            X17
#define T0                            X5
#define T1                            X6
#define T2                            X7
#define T3                            X28
#define T4                            X28
#define T5                            X28
#define T6                            X31
#define ZERO                          X0

/* MATRIX REGISTERS */
#define M0                            "00000"
#define M1                            "00001"
#define M2                            "00010"
#define M3                            "00011"
#define M4                            "00100"
#define M5                            "00101"
#define M6                            "00110"
#define M7                            "00111"
#define M8                            "01000"
#define M9                            "01001"
#define M10                           "01010"
#define M11                           "01011"
#define M12                           "01100"
#define M13                           "01101"
#define M14                           "01110"
#define M15                           "01111"
#define M16                           "10000"
#define M17                           "10001"
#define M18                           "10010"
#define M19                           "10011"
#define M20                           "10100"
#define M21                           "10101"
#define M22                           "10110"
#define M23                           "10111"
#define M24                           "11000"
#define M25                           "11001"
#define M26                           "11010"
#define M27                           "11011"
#define M28                           "11100"
#define M29                           "11101"
#define M30                           "11110"
#define M31                           "11111"

/* INSTRUCTIONS */
#define ML(md, rs1)         ".word 0b001000100000" rs1 "000" md "1110111 \n\t"
#define MS(md, rs1)         ".word 0b001000100000" rs1 "001" md "1110111 \n\t"

#define MLS(md, rs1, rs2)   ".word 0b0010001" rs2  rs1 "100" md "1110111 \n\t"
#define MSS(md, rs1, rs2)   ".word 0b0010001" rs2  rs1 "101" md "1110111 \n\t"

#define MMV_XMU(md, rs1)    ".word 0b010000100001" rs1 "000" md "1110111 \n\t"
#define MZERO(md)           MMV_XMU(md, X0)

#define MMACU(md, ms1, ms2) ".word 0b0110001" ms2  ms1 "000" md "1110111 \n\t"
#define MMAC(md, ms1, ms2)  ".word 0b0110011" ms2  ms1 "000" md "1110111 \n\t"
#define MMACF(md, ms1, ms2) ".word 0b0110101" ms2  ms1 "000" md "1110111 \n\t"

#define MADDU(md, ms1, ms2) ".word 0b0110001" ms2  ms1 "001" md "1110111 \n\t"
#define MADD(md, ms1, ms2)  ".word 0b0110011" ms2  ms1 "001" md "1110111 \n\t"
#define MADDF(md, ms1, ms2) ".word 0b0110101" ms2  ms1 "001" md "1110111 \n\t"

#define MSUBU(md, ms1, ms2) ".word 0b0110001" ms2  ms1 "010" md "1110111 \n\t"
#define MSUB(md, ms1, ms2)  ".word 0b0110011" ms2  ms1 "010" md "1110111 \n\t"
#define MSUBF(md, ms1, ms2) ".word 0b0110101" ms2  ms1 "010" md "1110111 \n\t"

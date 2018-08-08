enum opcodes {
    EXIT  = 0x00,
    SLOTH = 0x01,
    ADD   = 0x02, 
    SUB   = 0x03, 
    MULT  = 0x04, 
    DIV   = 0x05, 
    COMP  = 0x06,
    LOAD  = 0x07,
    STOR  = 0x08,
    GOTO  = 0x09,
    CH    = 0x0A,
    PUSH  = 0x0B
};

struct sloth_program {
    char* codes;
};
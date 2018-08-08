# SlothLang

SlothLang is an esoteric programming language by Aaron Goidel

# Features

  - Write code in a highly efficient and easy to read language
  - Slothy sloths are slothy

## Tech

SlothLang is parsed and executed in C. 

And of course the code behind the SlothLang VM itself is open source and can be found on [GitHub][slgit].

## Usage
A Sloth program is parsed in new-line deliminated instructions. Every line starts a new instruction at ```0x00```. Each occurance of the word `sloth` on a line increases the instruction code by one. At the end of each line the resulting instruction code is pushed and the next line is read. 

Since a Sloth command is generally based on the number of times the word sloth appears in a row, the syntax will be documented as a multiplication. For example the documentation `sloth * 3` means `sloth sloth sloth` in Sloth code.

To save time and effort, there are a few commands which do not follow the scheme outlined above. These will be outlined below. Note: the `and` operator is used to separate arguements.

# Syntax and Effects
### Exit
**Syntax:** `nap`
**Effect:** will terminate the execution of the program and return the top element from the stack.
**NOTE:** every Sloth file must end in `nap`.

### Add
**Syntax:** `sloth * 2`
**Effect:** pops the first two values off the stack and pushes their sum.
**Stack:** `S, x, y -> S, x+y`

### Subtract
**Syntax:** `sloth * 3`
**Effect:** pops the first two values off the stack and pushes their difference.
**Stack:** `S, x, y -> S, x-y`

### Multiply
**Syntax:** `sloth * 4`
**Effect:** pops the first two values off the stack and pushes their product.
**Stack:** `S, x, y -> S, x*y`

### Divide
**Syntax:** `sloth * 5`
**Effect:** pops the first two values off the stack and pushes their sum.
**Stack:** `S, x, y -> S, x/y`
**NOTE:** Division in SlothLang is integer division, meaning divide will always round fractions down. e.g. 3/2 = 1

### Compare <c>
**Syntax:** `sloth * 6 and sloth * c`
Notice that the **compare** instruction requires an arguement. The number of sloths after the `and` will determine which comparison should be made. See [Comparison Codes](#comparison-codes) for reference.

**Effect:** pops the first two values off the stack and pushes the truthiness of a comparison between them.
**Stack:** ``S, x, y -> S, 1 if true 0 if false``

### Input <t>
**Syntax:** `sloth * 7 and sloth * t`
The **input** instruction takes a type code to determine what kind of data is being read. See [Type Codes](#type-codes) for reference.

**Effect:** reads in either an integer or an ASCII character from standard in.
**Stack:** `S -> S, x`

### Output <t>
**Syntax:** `sloth * 8 and sloth * t`
The **output** instruction takes a type code to determine what kind of data is being displayed. See [Type Codes](#type-codes) for reference.

**Effect:** pops the top value off the stack and writes it to standard out.
**Stack:** `S, x -> S`

### GOTO <n>
**Syntax:** `sloth * 9 and sloth * n`
The **GOTO** instruction takes a number of sloths as the offset if the result is true.

**Effect:** pops the top value off the stack, if the value is 1, the program counter is increased by the offset, else continues as normal.
**Stack:** `S, x -> S`

### Push <i>
**Syntax:** `slothy sloth * i`

**Effect:** pushes the integer value of the number of sloths following slothy onto the stack.
**Stack:** `S -> S, x`
**Example:** `slothy sloth sloth sloth` pushes 3 onto the stack.

## Operation, Comparison, and Type Codes
SlothLang relies on the translation of a number of sloths to a numeric code in order to perform specific operations. 

### Comparison Codes
The compare function uses `<c>` sloths in order to select what kind of comparison is being made.
|Comparison Code|Operation|
|-|-|
|`0x01`|`x == y`|
|`0x02`|`x != y`|
|`0x03`|`x < y`|
|`0x04`|`x <= y`|
|`0x05`|`x > y`|
|`0x06`|`x >= y`|

### Type Codes
Type Codes `<t>` are used in the Input and Output instructions in order to determine what kind of data is being read or written.
|Type Code|Type of I/O|
|-|-|
|`0x01`|A signed integer value|
|`0x02`|A single ASCII character|

### Operation Codes
Sloth code is read in by the SlothVM as bytecode. The following is the bytecode for each SlothLang instruction.
| Byte Code | Name | 
|-|-|
|`0x00`|Exit|
|`0x02`|Add| 
|`0x03`|Subtract| 
|`0x04`|Multiply| 
|`0x05`|Divide|
|`0x06`|Compare <c>|
|`0x07`|Input <t>|
|`0x08`|Output <t>|
|`0x09`|GOTO <o>|
|`0x0A`|Push <i>|

   [slgit]: <https://github.com/AaronCGoidel/SlothLang>
   

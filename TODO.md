# TODO List

an low-level **Python** Interpretor

## What to Implement:

- Parse input of py source file and execute accordingly
- should support built-in types: **integer,floating point,boolean value**
- can calculate the value of expression.expression can be algebra or logical
- can define variable.
- can assign a value of expression to variable
- should support program flow control command,such as *if,while,for,break,continue*,.etc
- can declare functions and call them
- interactive mode

*optional:*

- object-oriented features,such as **class**.
- GUI frontend.
- IDE

## Implement specification:

the whole project should be divided as follows:

- a core utility to setup initialization,control interactive mode and interpreter mode,take in input from files in the latter.
- a parser to parse input lines and sentence,generating info about the input,including command type(a enumeration),expression parts based on syntax and semantic analysis.
- an expression calculator module to specifically calculate the value of an **expression**,should act accordingly to command type,as algebra or boolean operations. Note to implement bit-wise operation such as << as well as normal calculation such as ++
- a basic flow control system
- a dynamic container to maintain the variable defined and maintain the list of symbols in the file.it should also record function infomations later.
- a function module to define a function and provide callback ways.


Han Zhilei:2018-6-15 :AST structure completed

# char

![](https://i.imgur.com/MEfEIrR.png)

Char is an esoteric stack based programming language, which commands are single characters. The language was designed to be fast and simple.

___

# Syntax

Char's syntax can be represented as a table of commands:

| Command   | Parameter | Meaning                                                         |
| :-------: | :-------: | :-------------------------------------------------------------- |
| `>`       | Number    | Push a number onto the stack                                    |
| `<`       | -         | Discard the top item on the stack                               |
| `+`       | -         | Pop `a` and `b`. Push `a + b`                                   |
| `*`       | -         | Pop `a` and `b`. Push `a * b`                                   |
| `/`       | -         | Pop `a` and `b`. Push `b / a`                                   |
| `%`       | -         | Pop `a` and `b`. Push `b % a`                                   |
| `.`       | -         | Pop `a` and print it as a character                             |
| `,`       | -         | Read `a` and push it's ASCII value onto the stack               |
| `"`       | -         | Duplicate the top item on the stack                             |
| `&`       | -         | Swap the top two items on the stack                             |
| `#`       | -         | Ignore the next characters to the end of the line
| `~`       | -	        | Run the next statement if top of the stack is lower than 0	  |
| `?`       | -	        | Run the next statement if top of the stack is not 0	          |
| `^`       | Label     | Mark a location in the program                                  |
| `:`       | Label     | Jump to a label                                                 |
| `;`       | Label     | Call a subroutine                                               |
| `!`       | -         | End a subroutine and transfer control back to the caller        |
| `@`       | -         | End the program                                                 |

___

# Timeline

Currently Char is in its beta state. There's a lot that has to be done / improved.

- [x] `v1-beta` - The first version of Char
  - [x] `v1.0-beta` - the base release
- [ ] `v2-beta` - File System
  - [ ] `v2.0-beta` - the base release
  - [ ] `v2.1-beta` - file system implementation
  - [ ] `v2.2-beta` - file linking
- [ ] `v3-beta` - Standard Library
  - [ ] `v3.0-beta` - the base release
  - [ ] `v3.1-beta` - a little peek on the Char's standard library
  - [ ] `v3.2-beta` - _chrlib_, the standard library for Char

___

# Example

A program that prints its input:
```
# out.char
^read
	,
	? :print
	@
^print
	.
	:read
```
More examples can be found in the `examples` directory

___

# Usage

After you've built an executable you can run it according to this usage:

`<exe> <src> <input>`

- `<exe>`   - path to your executable
- `<src>`   - path to your source file
- `<input>` - input of the program `(optional)`

___

###### This README was inspired by a README from the repository of the [Night](https://github.com/DynamicSquid/night) programming language

# advanced-database-technologies

## Lab 1

To compile:
```sh
gcc <file_name>.c -o <executable_file>
```
if additional library needed (here: `sqlite3`), use additional `-l` flag:

```sh
gcc -l<library_name> <file_name>.c -o <executable_file>
```

To run:

```sh
<executable_file> 
```
Passing any argument will enable transactions, for example:
```sh
<executable_file> t
```

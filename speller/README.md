# Spellcheck C program
*[CS50] Week 5 - Data Structures - Problem Set 5*

> For this problem, you’ll implement a program that  
> spell-checks a file, using a **hash table** and a **linked list**.

![example](example.png)

Main functionality implemented in `dictionary.c`

## Useful URLs
- Problem Set 5 - [`Speller`]
- Make [Flags]
- Basics of [Hash Tables]

## Memory management test
Using [`Valgrind`]:
```sh
$ valgrind ./speller dictionaries/large texts/carroll.txt

==20094== 
==20094== HEAP SUMMARY:
==20094==     in use at exit: 0 bytes in 0 blocks
==20094==   total heap usage: 143,096 allocs, 143,096 frees, 8,023,256 bytes allocated
==20094== 
==20094== All heap blocks were freed -- no leaks are possible
==20094== 
==20094== For lists of detected and suppressed errors, rerun with: -s
==20094== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

[CS50]:https://cs50.harvard.edu/x/2022/
[`Speller`]:https://cs50.harvard.edu/x/2022/psets/5/speller/
[Flags]:https://earthly.dev/blog/make-flags/
[Hash Tables]:https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/
[`Valgrind`]:https://valgrind.org/

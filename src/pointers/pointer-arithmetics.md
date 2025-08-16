
# Pointer Arithmetic on Character Pointer:

```
pcData++;

addr( pcData + 1 ) = addr( pcData ) + [ sizeof( char ) * 1 ];
addr( pcData + 1 ) = addr( pcData ) + [ 1 * 1 ];
addr( pcData + 1 ) = addr( pcData ) + 1;
```

# Indirection operator with pre-increment operator
`++*p is equivalent to ++ (*p)`<br>
`*++p is equivalent to *(++p)`

# Indirection operator with post-increment operator:
`*p++ will be equivalent to *(p++)`


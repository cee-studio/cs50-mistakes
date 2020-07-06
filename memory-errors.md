# Memory Errors

### 1. [Caesar] argv[1] is 0 if argc is 1. 
```
int main(int argc, string argv[])
{
    int n = strlen(argv[1]);
    ...
```
```
  Memory access error: invalid parameter; abort execution.
  # strlen's parameter (0x0) is not a valid pointer
  # Stack trace (most recent call first) of the error.
  # [0]  file:/prog.c::9, 13
  # [1]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200615-OwQ&name=fB6Xk)


### 2. [Recover] Too small to hold the null terminator
```
char filename[8]; // Array to store my filename
...
sprintf(filename, "%03i.jpg", file_count);
```

```
  Memory access error: writing to the outside of a memory block; abort execution.
  # Writing 1 bytes to 0xffdb6c84 will clobber other memory blocks.
  #
  # The memory-block-to-be-written (start:0xffdb6c7c, size:8 bytes) is bound to 'filename' at
  #    file:/recover.c::13, 10
  #
  #  0xffdb6c7c           0xffdb6c83
  #  +--------------------------+
  #  |memory-block-to-be-written|......
  #  +--------------------------+
  #                              ^~~~~~~~~~
  #        the write starts at 0xffdb6c84 that is right after the memory block end.
  #
  # Stack trace (most recent call first) of the write.
  # ...
  # [3]  file:/recover.c::46, 17
```

### 3. [Recover] Pasing an invalid buffer pointer to `fread`
```
 while (fread(buffer, 512, 1, fPointer) == 512)
    {
     ...
     fclose(fPointer);
```
```
  Memory access error: invalid parameter; abort execution.
  # fread's 1st parameter is not a valid pointer.
  # Stack trace (most recent call first) of the error.
  # [0]  file:/recover.c::45, 12
  # [1]  [libc-start-main]
```

### 4. [Recover] Passing an invalid pointer to `sprintf`
```
  char * jpg_filename = NULL;
  ...
  sprintf(jpg_filename, "%03i.jpg", jpg_count - 1); // line 39
```
```
  Memory access error: dereferencing a null pointer; abort execution.
  # Writing 2 bytes to address 0x0.
  #
  # Stack trace (most recent call first) of the write.
  # ...
  # [9]  file:/recover.c::39, 17
```

### 5. [Speller] Passing a NULL pointer to `fscanf`
```
    char *nw = NULL;
    while (fscanf(dict, "%c", nw) != EOF)
```
```
  Memory access error: invalid parameter; abort execution.
  # fscanf's 3rd parameter is not a valid pointer
  # Stack trace (most recent call first) of the error.
  # [0]  file:/dictionary.c::82, 12
  # [1]  file:/speller.c::40, 19
  # [2]  [libc-start-main]
```

### 6. [Speller] Accessing the next field of NULL
```
            // table[hash(temp)] is NULL.
            node* n = malloc(sizeof(node)); 
            if (table[hash(temp)] -> next != NULL) // segfault here
            {
                n = table[hash(temp)] -> next;
            }
```
```
  Memory access error: dereferencing a non-pointer; abort execution.
  # Reading 4 bytes from an illegit address (0x30).
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/dictionary.c::68, 23
  # [1]  file:/speller.c::40, 19
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200615-hQb&name=speller)


### 7. [Speller] Passing a non-pointer to `fscanf`
```
    char *dictionaryword[LENGTH];
    while (fscanf(file, "%s", *dictionaryword) != EOF) // segfault here
```
```
  Memory access error: invalid parameter; abort execution.
  # fscanf's 3rd parameter is not a valid pointer
  # Stack trace (most recent call first) of the error.
  # [0]  file:/dictionary.c::92, 12
  # [1]  file:/speller.c::40, 19
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200615-UYs&name=speller)


### 8. [Speller] A negligence
trav is assigned to the address of a new memoy block, but it is
immediately overwritten by another value.
```
    node *trav = malloc(sizeof(node));
    trav = table[index];  // trav is overwritten
    while (1)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
```
```
  Memory access error: dereferencing a null pointer; abort execution.
  # Reading 1 bytes from address 0x0.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/musl-1.1.10/src/string/strcasecmp.c::8, 2
  # [1]  file:/dictionary.c::43, 13
  # [2]  file:/speller.c::113, 32
  # [3]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200615-1RB&name=speller)


### 9. [Speller] Using uninitialized memory
```
Node* cursor = malloc(sizeof(Node));
...
    cursor->next = table[index];
    //checks that cursor points to corect word
    while(cursor->next != NULL)
    {
        if(strcasecmp(cursor->word,word) == 0) // memory error
```
```
  Memory access warning: reading uninitialized memory; continue execution.
  # Reading 1 bytes from 0x8fbf170 will read undefined data.
  #
  # The memory-space-to-be-read (start:0x8fbf170, size:52 bytes) is allocated at
  #    file:/dictionary.c::37, 20
  # It is not initialized.
  #
  #  0x8fbf170               0x8fbf1a3
  #  +------------------------------+
  #  | the memory-space-to-be-read  |
  #  +------------------------------+
  #  ^~~~~~~~~~
  #      the read starts at the begin of the memory-space.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/musl-1.1.10/src/string/strcasecmp.c::8, 2
  # [1]  file:/dictionary.c::57, 12
  # [2]  file:/speller.c::113, 32
  # [3]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200615-45p&name=speller)


### 10. [Speller] Not a modulo of N
```
    int X = (hash (word)); // a negative value
    if (table[X] == NULL)  // line 35
```
```
  Memory access error: reading from the outside of a memory block; abort execution.
  # Reading 4 bytes from 0x8090270 will read undefined values.
  #
  # The memory-block-to-be-read (start:0x8090274, size:184 bytes) is bound to 'table' at
  #    file:/dictionary.c::29, 0
  #
  #                               0x8090274           0x809032b
  #                               +--------------------------+
  #                         ......| memory-block-to-be-read  |
  #                               +--------------------------+
  #                            ^~~~~~~~~~
  #   the read starts at 0x8090270 that is 4 bytes before the memory block start.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/dictionary.c::35, 9
  # [1]  file:/speller.c::113, 32
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200616-b27&name=speller)


### 11. [Speller] Accessing the next field of a NULL pointer
```
bool unload(void)
{
    node *tmp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        printf ("table[%d] = %p\n", i, table[i]);
        for (cursor = table[i]; 
             cursor; 
             cursor = cursor->next) { // this advance the NULL cursor again 
            tmp = cursor;
            cursor = cursor->next; // this advance cursor, and cursor become NULL
            free(tmp);
        }
    }
    free(cursor);
    return false;
}
```
```
  Memory access error: dereferencing a non-pointer; abort execution.
  # Reading 4 bytes from an illegit address (0x30).
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/dictionary.c::132, 14
  # [1]  file:/speller.c::153, 21
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200616-0DT&name=speller)

### 12. [Speller] Passing a NULL pointer to `fscanf`
```
char * str = NULL;
...
while (fscanf(file, "%s", str) != EOF) {
```
```
  Memory access error: invalid parameter; abort execution.
  # fscanf's 3rd parameter is not a valid pointer
  # Stack trace (most recent call first) of the error.
  # [0]  file:/dictionary.c::110, 10
  # [1]  file:/speller.c::40, 19
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200616-8WN&name=speller)


### 13. [Recover] A negligence
`byte` has the jpg data, but `buffer` is used to check for jpg header. 
```
    while ((fread(byte, 512, 1, card)) == 1)
    {
        BYTE buffer[512];
        char filename[8];
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
```
```
  Memory access warning: reading uninitialized memory.
  # Reading 1 bytes from 0xff84b60c will read undefined data.
  #
  # The memory-block-to-be-read (start:0xff84b60c, size:512 bytes) is bound to 'buffer' at
  #    file:/recover.c::26, 14
  # It is not initialized.
  #
  #  0xff84b60c           0xff84b80b
  #  +--------------------------+
  #  | memory-block-to-be-read  |
  #  +--------------------------+
  #  ^~~~~~~~~~
  #      the read starts at the begin of the memory block.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/recover.c::28, 13
  # [1]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200618-l2V&name=recover)


### 14. [Readability] A logic error
```
do {
    j++;
    while (Text[j] != '!' || Text[j] != '?' ||
           Text[j] != '.') /*This is were the error is (all 3 of them)*/ 
    {
      j++;
    }
    SentencesZ++;
  } while (j < strlen(Text));
```
```
 Memory access error: reading from the outside of a memory block; abort execution.
  # Reading 1 bytes from 0x99c4025 will read undefined values.
  #
  # The memory-block-to-be-read (start:0x99c4010, size:21 bytes) is allocated at
  #    file:/tmp/src/libcs50/src/cs50.c::185, 16
  #
  #  0x99c4010           0x99c4024
  #  +--------------------------+
  #  | memory-block-to-be-read  |......
  #  +--------------------------+
  #                              ^~~~~~~~~~
  #        the read starts at 0x99c4025 that is right after the memory block end.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/prog.c::40, 5
  # [1]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200620-307&name=CSwRu)


### 15. [Speller] Not understanding free
a node is immediately freed after adding to the hash table
```
    while(fscanf(file, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
	
        ...
        n -> next = table[pos];
        table[pos] = n;
	
	...
        // Free the allocated memory
        free(n);
    }
```
```
  Memory access error: reading from a freed memory block; abort execution.
  # Reading 1 bytes from 0x928ddc0 will read undefined values.
  #
  # The memory-block-to-be-read (start:0x928ddc0, size:52 bytes) was allocated at
  #    file:/dictionary.c::47, 19
  # It was freed, and its allocation location might be distorted by subsequent reuses.
  #
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/musl-1.1.10/src/string/strcasecmp.c::8, 2
  # [1]  file:/dictionary.c::108, 13
  # [2]  file:/speller.c::113, 32
  # [3]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200621-Bzs&name=speller)


### 16. [Recover] Not understanding `fread`
```
while (fread(buffer, 512, 1, file) == 512) {
  img = fopen (...);
}
fclose(img); // segfault here
```

```
  Memory access error: invalid parameter; abort execution.
  # fclose's parameter (0xffa0503c) is not a valid FILE pointer.
  # Stack trace (most recent call first) of the error.
  # [0]  file:/recover.c::81, 3
  # [1]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200624-Idc&name=recover)

### 17. [Speller] Use after free
```
void nullFree()
{
    for(int i = 0; i < N; i++)
    {
        if(current->children[i] == NULL) // current points to a freed memory block
        {
            printf("NULL");
            return free(current);
        }
        else
        {
            current = current->children[i];
            nullFree();
        }
    }
}
```
```
  Memory access error: reading from a freed memory block; abort execution.
  # Reading 4 bytes from 0x992d014 will read undefined values.
  #
  # The memory-block-to-be-read (start:0x992d010, size:112 bytes) was allocated at
  #    file:/dictionary.c::35, 12
  # It was freed, and its allocation location might be distorted by subsequent reuses.
  #
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/dictionary.c::179, 12
  # [1]  file:/dictionary.c::167, 9
  # [2]  file:/speller.c::152, 21
  # [3]  [libc-start-main]
  
```
[demo](https://cee.studio/?bucket=200627-SFw&name=speller.trie)

### 18. [Speller] Reading uninitialized Memory
`word` is not fully initialized, and the loop is not terminated at `\0`.
```
   for (int i = 0; i < LENGTH; i++)
        lcword[i] = tolower(word[i]); 
```
```
  Memory access warning: reading uninitialized memory.
  # Reading 1 bytes from 0xff8a2abe will read undefined data.
  #
  # The memory-block-to-be-read (start:0xff8a2abc, size:46 bytes) is bound to 'word' at
  #    file:/speller.c::68, 10
  # It is not initialized.
  #
  #  0xff8a2abc           0xff8a2ae9
  #  +--------------------------+
  #  | memory-block-to-be-read  |
  #  +--------------------------+
  #              ^~~~~~~~~~
  #      the read starts at 2 bytes offset of the memory block.
  #
  # Stack trace (most recent call first) of the read.
  # [0]  file:/dictionary.c::36, 21
  # [1]  file:/speller.c::113, 32
  # [2]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200627-TAx&name=speller)


### 19. [Speller] Allocation is too small
```
    char *word = malloc(LENGTH);
    ...
    //Iterate over dictionary until fscanf return EOF (meaning it's the end of the file)
    while (fscanf(dicfile, "%s", word) != EOF)
    {
```
```
  Memory access error: writing to the outside of a memory block; abort execution.
  # Writing 1 bytes to 0x8fb1ded will clobber other memory blocks.
  #
  # The memory-block-to-be-written (start:0x8fb1dc0, size:45 bytes) is allocated at
  #    file:/dictionary.c::70, 18
  #
  #  0x8fb1dc0           0x8fb1dec
  #  +--------------------------+
  #  |memory-block-to-be-written|......
  #  +--------------------------+
  #                              ^~~~~~~~~~
  #        the write starts at 0x8fb1ded that is right after the memory block end.
  #
  # Stack trace (most recent call first) of the write.
  # [0]  file:/musl-1.1.10/src/stdio/vfscanf.c::271, 12
  # [1]  file:/musl-1.1.10/src/stdio/fscanf.c::28, 8
  # [2]  file:/dictionary.c::81, 12
  # [3]  file:/speller.c::40, 19
  # [4]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200627-Way&name=speller)


### 20. [Speller] Using an uninitialized pointer
```
bool check(const char *word)
{
    char *test;  // test is not initialized

    int bucket = hash(word);
    node *trav = table[bucket];

    while (trav != NULL)
    {
        strcpy(trav->word, test);
```
```
 Memory access error: invalid parameter; abort execution.
  # strlen's parameter (0x9e6bdc0) is not a valid pointer
  # Stack trace (most recent call first) of the error.
  # [0]  file:/musl-1.1.10/src/string/stpcpy.c::15, 16
  # [1]  file:/musl-1.1.10/src/string/strcpy.c::8, 2
  # [2]  file:/dictionary.c::37, 9
  # [3]  file:/speller.c::113, 32
  # [4]  [libc-start-main]
```
[demo](https://cee.studio/?bucket=200629-WCN&name=speller)

# Logic errors

### [Caesar] doesn't handle lack of key
The check of argc is too late.
```
int main(int argc, string argv[])
{   
    //reject if input is non-numeric
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("caesar + key\n");
            return 1;
        }
    }
    // reject if the number of arguments is not 2
    if (argc !=2)
    {
        printf("caesar + key\n");
        return 1;
    }
 ```
 [demo](https://cee.studio/?bucket=200706-zNf&name=lagh1)
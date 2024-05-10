# include <stdio.h>
# include <ctype.h>

# define LIMIT 100

int sctoi(char c);

void toBinary(int type, char input[]);
void toDecimal(int type, char input[]);


int main()
{   
    char from, to;
    from = '0';
    to = '0';
    char input[LIMIT];

    printf("This is a number base conversion program\nPlease select the operation you wish to perform\n");
    printf("[1] Binary\n[2] Decimal\n[3] Octal\n[4] Hexadecimal\n\n[Q/q] To Exit the program\n\n");
    
    // Prompt and validate from input
    while (!(from - '0'))
    {
        printf("From: ");
        scanf(" %c", &from);
        
        // Remember order of precedence
        // arithmetic first
        // relational, then equality
        // after that it's logical (&& is higher than ||)
        if ((isalpha(from) && tolower(from) - 'q') || (isdigit(from) && sctoi(from) > 4))
        {
            from = '0';
            printf("Invalid Input! Please Enter the correct selection\n");
        }
        else if (!(tolower(from) - 'q'))
        {
            printf("Program exited\n");
            return -1;
        }
                  
    }
    
    // Prompt and validate to input
    while (!(to - '0'))
    {
        printf("To: ");
        scanf(" %c", &to);

        if ((isalpha(to) && tolower(to) - 'q') || (isdigit(to) && sctoi(to) > 4))
        {
            to = '0';
            printf("Invalid Input! Please Enter the correct selection\n");
        }
        else if (!(tolower(to) - 'q'))
        {
            printf("Program exited\n");
            return -1;
        }
    }

    printf("Enter the number you wish to convert:\n");
    scanf(" %s", input);

    switch (from)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

// sctoi: return the integer representation of the digit character, return -1 upon non-digit input
int sctoi(char c)
{
    if (isdigit(c))
        return c - '0';
    
    return -1;
}
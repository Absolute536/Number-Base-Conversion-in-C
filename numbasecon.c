# include <stdio.h>
# include <ctype.h>

# define LIMIT 100

int sctoi(char c);
int validateInput(char type, char s[]);

void toBinary(int type, char input[]);
void toDecimal(int type, char input[]);


int main(void)
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

    int validate = 0;

    while (!validate)
    {
        if ((validate = validateInput(from, input)) == -1)
        {
            printf("Program exited\n");
            return -1;
        }
        
        if (!validate)
        {
            printf("Invalid input! Enter the correct number.\n");
            scanf(" %s", input);
        }
        else
        {
            // program execution if everything is valid
            ;
        }
    }
    


}

// sctoi: return the integer representation of the digit character, return -1 upon non-digit input
int sctoi(char c)
{
    if (isdigit(c))
        return c - '0';
    
    return -1;
}

// validateInput: return -1 if only 'Q' / 'q' is input, else validate the input based on user's option, return 0 if invalid
int validateInput(char type, char s[])
{   
    int from = sctoi(type);

    if (tolower(s[0]) == 'q' && s[1] == '\0')
        return -1;

    int i = 0;
    if (from == 4 && s[0] == '0' && tolower(s[1]) == 'x')
        i = 2;

    // Depending on the type of "from" chosen, validate s[] differently
    while (s[i] != '\0')
    {
        switch (from)
        {
            case 1:
                // Binary - check if it is a digit and > 1
                if (!isdigit(s[i]) || sctoi(s[i]) > 1)
                    return 0;
                break;
            case 2:
                // Decimal - check if it is a digit
                if (!isdigit(s[i]))
                    return 0;
                break;
            case 3:
                // Octal - check if the first character is a backslash '\'
                if (s[0] != '\\' || ( i > 0 && (!isdigit(s[i]) || sctoi(s[i]) > 7)))
                    return 0;
                break;
            case 4:
                // Hexadecimal - check if the character goes beyond 'A'/'a' and 'F'/'f'
                if (!isdigit(s[i]) && (tolower(s[i]) < 'a' || tolower(s[i]) > 'f'))
                    return 0;
                break;
        }

        i++;
    }

    // remove, maybe not
    return 1;
}
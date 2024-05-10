# include <stdio.h>
# include <ctype.h>

# define LIMIT 100

int sctoi(char c);
int validateInput(char type, char s[]);

void toType(char input[], int ans, int type);
int getDecimal(int from, char input[]);

int main(void)
{   
    char from, to;
    from = '0';
    to = '0';
    char input[LIMIT];

    printf("This is a number base conversion program\nPlease select the operation you wish to perform\n");
    printf("[1] Binary\n[2] Decimal\n[3] Octal (Must: Preceed input with '\')\n[4] Hexadecimal (Optional: Preceed input with 0x or 0X)\n\n[Q/q] To Exit the program\n\n");
    
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
            int result = getDecimal(sctoi(from), input);

            int type = sctoi(to);

            toType(input, result, type);
                    
            printf("%s\n", input);
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

    // Return 1 if everything goes well
    return 1;
}

int getDecimal(int from, char input[])
{   
    int result = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        switch (from)
        {
            case 1:
                result = result * 2 + sctoi(input[i]);
                break;
            case 2:
                result = result * 10 + sctoi(input[i]);
                break;
            case 3:
                if (!i)
                    i = 1;
                result = result * 8 + sctoi(input[i]);
                break;
            case 4:
                if (input[0] == '0' && tolower(input[1]) == 'x' && i < 1) // This thing is not efficient
                    i = 2;
                if (isalpha(input[i]))
                    result = result * 16 + (tolower(input[i]) - 'a' + 10);
                else
                    result = result * 16 + sctoi(input[i]);
                break;
        }
    }

    return result;
}

void toType(char input[], int ans, int type)
{
    char reverse[LIMIT];

    int i = 0;
    
    while (ans)
    {
        switch (type)
        {
            case 1:
                reverse[i++] = '0' + (ans % 2);
                ans /= 2;
                break;
            case 2:
                reverse[i++] = '0' + (ans % 10);
                ans /= 10;
                break;
            case 3:
                reverse[i++] = '0' + (ans % 8);
                ans /= 8;
                break;
            case 4:
                if (ans % 16 > 9)
                    reverse[i++] = 'A' + ((ans % 16) - 10);
                else
                    reverse[i++] = '0' + (ans % 16);
                ans /= 16;
                break;
        }
    }
    reverse[i] = '\0';

    int j = 0;
    while (i)
    {
        input[j] = reverse[--i];
        j++;
    }
    input[j] = '\0';
}

# include <stdio.h>
# include <ctype.h>

# define LIMIT 100

int dctoi(char c); // digit character to integer (for single character only)
int validateInput(char type, char s[]);

void toType(char input[], int ans, int type);
int getDecimal(int from, char input[]);

int main(void)
{   
    // Initialise data
    char from, to;
    from = '0';
    to = '0';
    char input[LIMIT];

    // Display the program operation
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
        if ((isalpha(from) && tolower(from) - 'q') || (isdigit(from) && dctoi(from) > 4))
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

        if ((isalpha(to) && tolower(to) - 'q') || (isdigit(to) && dctoi(to) > 4))
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

    // Get number to convert
    printf("Enter the number you wish to convert: ");
    scanf(" %s", input);

    int validate = 0;

    // Validate the input number, re-prompt if needed
    while (!validate)
    {
        if ((validate = validateInput(from, input)) == -1)
        {
            printf("Program exited\n");
            return -1;
        }
        
        if (!validate)
        {
            printf("\nInvalid input! Enter the number in the correct base.\nEnter the number you wish to convert: ");
            scanf(" %s", input);
        }
        else
        {
            // Program execution if everything is valid
            int result = getDecimal(dctoi(from), input);

            int type = dctoi(to);

            toType(input, result, type);
                    
            printf("Conversion result: %s\n", input);
        }
    }
}

// dctoi: return the integer representation of the digit character, return -1 upon non-digit input
int dctoi(char c)
{
    if (isdigit(c))
        return c - '0';
    
    return -1;
}

// validateInput: return -1 if only 'Q' / 'q' is input, else validate the input based on user's option, return 0 if invalid
int validateInput(char type, char s[])
{   
    int from = dctoi(type);

    if (tolower(s[0]) == 'q' && s[1] == '\0')
        return -1;

    int i = 0;
    // Start from the third index if the given input is in hexadecimal and starts with 0x
    if (from == 4 && s[0] == '0' && tolower(s[1]) == 'x')
        i = 2;

    // Depending on the type of "from" chosen, validate s[] differently
    while (s[i] != '\0')
    {
        // A switch statement to check for invalid input, and return 0 if found
        switch (from)
        {
            case 1:
                // Binary - check if it is a digit and > 1
                if (!isdigit(s[i]) || dctoi(s[i]) > 1)
                    return 0;
                break;
            case 2:
                // Decimal - check if it is a digit
                if (!isdigit(s[i]))
                    return 0;
                break;
            case 3:
                // Octal - check if the first character is a backslash '\' OR if the input characters are digits OR greater than 7
                if (s[0] != '\\' || ( i > 0 && (!isdigit(s[i]) || dctoi(s[i]) > 7)))
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

// getDecimal: return the decimal representation of the given input
int getDecimal(int from, char input[])
{   
    int result = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        switch (from)
        {
            /*
             * The conversion is performed using the formula/equation
             * result = result * numberBaseConvertTo + integer value of the character in the number base
             * result is initialised as 0
             * This works due to multiplication property (distributive?)
             */
            case 1:
                result = result * 2 + dctoi(input[i]); 
                break;
            case 2:
                result = result * 10 + dctoi(input[i]);
                break;
            case 3:
                // Skip the first index as it is a backslash character in the input (Octal)
                if (!i) // Another not efficient
                    i = 1;
                result = result * 8 + dctoi(input[i]);
                break;
            case 4:
                // Skip the first two indices if the input has 0x (Hexadecimal)
                if (input[0] == '0' && tolower(input[1]) == 'x' && i < 1) // This thing is not efficient
                    i = 2;
                if (isalpha(input[i]))
                    result = result * 16 + (tolower(input[i]) - 'a' + 10);
                else
                    result = result * 16 + dctoi(input[i]);
                break;
        }
    }

    return result;
}

// toType: convert the input to the corresponding number base according to the type and store the conversion result back to the input array
void toType(char input[], int ans, int type)
{
    // char array to hold the reverse of the conversion result
    char reverse[LIMIT];

    int i = 0;
    
    while (ans)
    {
        /*
         * TThe decimal value of the input is used to convert it to the corresponding number base

         * The conversion is performed using the standard number base conversion method via division
         * 
         * By dividing the integer (decimal number) with the corresponding base,
         * the remainder of each division can be obtained
         * 
         * The remainders obtained are the value to each of the digits in the target number base we want to obtained (in reverse order)
         * 
         * So by taking the modulo of the decimal input and dividing it by 2 until the quotient reaches 0,
         * we can calculate the corresponding number base representation of the given input
         */
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
                if (ans % 16 > 9) // If the digit represents a value > 9 (10 and above), use the corresponding alphabet (Hexadecimal)
                    reverse[i++] = 'A' + ((ans % 16) - 10);
                else
                    reverse[i++] = '0' + (ans % 16);
                ans /= 16;
                break;
        }
    }
    reverse[i] = '\0'; // Append the null terminating character to the end of the input

    // reverse copy the reverse array to the input array
    int j = 0;
    while (i)
    {
        input[j] = reverse[--i]; // --i to skip the \0 which i previously pointed to
        j++;
    }
    input[j] = '\0'; // Again append \0 at the end of the input array
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "romancalc.h"


int main()
{
    
    /* declaration */
    char *roman_num1;
    char *roman_num2;
    char *roman_sum;
    char *math_operator;
    
    while(1)
    {
        /* dynamic memory allocation */
        roman_num1=calloc(sizeof(char),50);
        roman_num2=calloc(sizeof(char),50);
        math_operator=calloc(sizeof(char),10);
        
        /* inputs */
        printf("Enter the first operand and then press enter: ");
        scanf("%s", roman_num1);
        roman_num1=(char*) realloc(roman_num1,strlen(roman_num1)+1);
        
        printf("Enter the second operand and then press enter: ");
        scanf("%s", roman_num2);
        roman_num2=(char*) realloc(roman_num2,strlen(roman_num2)+1);
        
        printf("Enter the mathematical operation (\"+\" or \"-\") and then press enter: ");
        scanf("%s", math_operator);
        
        /* calculations */
        printf("\nMethod 1: Add/ Subtract by Roman2Decimal , Decimal Add/Subtract, Decimal2Roman\n");
        if (*math_operator==43)  /* ascii of plus  */
        {roman_sum=addition(roman_num1,roman_num2);
         printf("%s + %s  = %s \n\n", roman_num1,roman_num2,roman_sum);}
        else if (*math_operator==45)  /* ascii of plus  */
        {roman_sum=subtraction(roman_num1,roman_num2);
         printf("%s - %s  = %s \n\n", roman_num1,roman_num2,roman_sum);}
        else
            printf("Unknown math operation \n");
        
        
        /* calculations 2 */
        printf("\nMethod 2: Add/Subtract by By String Merge (Onhand and Borrow Baskets)\n");
        if (*math_operator==43)  /* ascii of plus  */
        {roman_sum=addition_nondecimal(roman_num1,roman_num2);
         printf("%s + %s  = %s \n\n", roman_num1,roman_num2,roman_sum);}
        else if (*math_operator==45)  /* ascii of plus  */
        {roman_sum=subtraction_nondecimal(roman_num1,roman_num2);
         printf("%s - %s  = %s \n\n", roman_num1,roman_num2,roman_sum);}
        else
            printf("Unknown math operation \n");
        
        printf("\n ------------------------------------- \n");
        /* deallocation */
        free(roman_num1);
        free(roman_num2);
        free(roman_sum);
        free(math_operator);
    }
    return 0;
}













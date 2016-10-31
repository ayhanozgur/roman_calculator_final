#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "romancalc.h"

#define error_output "INVALID"

/* addition function */
char * addition(char *roman_num1, char *roman_num2)
{
    
    char *roman_sum;
    short decimal_num1,decimal_num2;
    short total;
    int error=0;
    error=(roman_num_validity(roman_num1, (int) 1)+ roman_num_validity(roman_num2,(int) 2));
    
    if (error==0)
    {
        /* operands ruman numerical to decimal conversion */
        decimal_num1=roman_to_decimal(roman_num1, (int) 1);
        decimal_num2=roman_to_decimal(roman_num2, (int) 2);
        
        total= decimal_num1 + decimal_num2;
        
        /* operands decimal to roman numerical conversion */
        roman_sum=decimal_to_roman(total);
        
        return roman_sum;
    }
    else
        return error_output;
}

/* subtraction function */
char * subtraction(char *roman_num1, char *roman_num2)
{
    
    char *roman_sum;
    short decimal_num1,decimal_num2;
    short total;
    int error=0;
    
    error=(roman_num_validity(roman_num1, (int) 1)+ roman_num_validity(roman_num2,(int) 2));
    
    if (error==0)
    {
        /* operands ruman numerical to decimal conversion */
        decimal_num1=roman_to_decimal(roman_num1,(int) 1);
        decimal_num2=roman_to_decimal(roman_num2, (int) 2);
        
        total= decimal_num1 - decimal_num2;
        
        
        /* zero or negative output check */
        if (total <=0)
        {printf("Zero or negative outputs can not express by romen numerals \n");return error_output;}
        else
        {roman_sum=decimal_to_roman(total);}
        
        return roman_sum;
    }
    else
        return error_output;
}

/* roman numerical validity check function*/
int roman_num_validity(char *roman_num, int operand_ID)
{
    /* declaration and initialization */
    int i=0;
    
    int count_M=0;
    int count_D=0;
    int count_L=0;
    int count_V=0;
    int count_C=0;
    int count_X=0;
    int count_I=0;
    
    int count_CM=0;
    int count_CD=0;
    int count_XC=0;
    int count_XL=0;
    int count_IX=0;
    int count_IV=0;
    
    int error_set=0;
    int error=0;
    int error_check[11]={0,0,0,0,0,0,0,0,0,0,0};
    
    int num_length =strlen(roman_num);
    int *order_ID=calloc(sizeof(int),num_length);
        if (order_ID==NULL)
		{
			printf ("Error allocating requested memory");
			exit (1);
		}
    
    i=(num_length);
    
    while (i>0)
    {
        switch (roman_num[i-1])
        {
            case 'M':
                order_ID[i-1]=7;
                count_M++;
                break;
            case 'D':
                order_ID[i-1]=6;
                count_D++;
                break;
            case 'C':
                order_ID[i-1]=5;
                count_C++;
                break;
            case 'L':
                order_ID[i-1]=4;
                count_L++;
                break;
            case 'X':
                order_ID[i-1]=3;
                count_X++;
                break;
            case 'V':
                order_ID[i-1]=2;
                count_V++;
                break;
            case 'I':
                order_ID[i-1]=1;
                count_I++;
                break;
            default:
                error_set=1;
                break;
        }
        i--;
        
        /* error check for multiple multiple use of DLV and CXI characters */
        if ((count_D==2) || (count_L==2) || (count_V==2))
        {error_set=2;break;}
        else if ((count_C==4) || (count_X==4) || (count_I==4))
        {error_set=3;break;}
        
        if (count_M>1 && count_C==0)
        {error_check[0]=1;}
        if (count_C>1 && count_X==0)
        {error_check[1]=1;}
        if (count_X>1 && count_I==0)
        {error_check[2]=1;}
        if (count_X==1 && count_L==1)
        {error_check[3]=1;}
        if (count_X==2 && count_L==1)
        {error_check[4]=1;}
        if (count_X==1 && count_C==1)
        {error_check[5]=1;}
        if (count_X==2 && count_C==1)
        {error_check[6]=1;}
        if (count_C==1 && count_D==1)
        {error_check[7]=1;}
        if (count_C==2 && count_D==1)
        {error_check[8]=1;}
        if (count_C==1 && count_M==1)
        {error_check[9]=1;}
        if (count_C==2 && count_M==1)
        {error_check[10]=1;}
        
    }
    
    
    /* error generation for  multiple use of DLV and CXI characters */
    if (error_set==1)
    {error=1;printf("Unknown Character in operand %d \n", operand_ID);return error;}
    else if (error_set==2)
    {error=1;printf("D L V characters can't be used more than one in operand %d \n", operand_ID);return error;}
    else if (error_set==3)
    {error=1;printf("C X I characters can't be used more than three in operand %d \n", operand_ID);return error;}
    
    
    /* error check for illegal use of combine characters such as XCXC, IIX,IIIV, XCX etc*/
    for (i=(num_length-1); i>0; i--)
    {
        if (order_ID[i]>order_ID[i-1])
        {
            if ((order_ID[i]-2)==(order_ID[i-1]) || (order_ID[i]-1)==(order_ID[i-1]))
            {
                if (order_ID[i-1]==2 || order_ID[i-1]==4 || order_ID[i-1]==6)
                {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
                
                order_ID[i-1]=(-order_ID[i-1]);
                if (order_ID[i]==7)
                    count_CM++;
                else if (order_ID[i]==6)
                    count_CD++;
                else if (order_ID[i]==5)
                    count_XC++;
                else if (order_ID[i]==4)
                    count_XL++;
                else if (order_ID[i]==3)
                    count_IX++;
                else if (order_ID[i]==2)
                    count_IV++;
                
            }
            else
            {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
        }
        else if (order_ID[i]<0)
        {
            if (order_ID[i-1]==(-order_ID[i]))
            {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
            else if (order_ID[i-1] < order_ID[i+1])
            {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
        }
        else
        {}
    }
    
    /* error generation for illegal use of combine characters such as XCXC, IIX,IIIV, XCX etc*/
    if ((count_CM>1) || (count_CD>1) || (count_XC>1) || (count_XL>1) || (count_IX>1) || (count_IV>1))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((count_I>count_IX  && count_IX>0) || (count_I>count_IV  && count_IV>0))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if (((count_CM>1) &&(count_CD>1)) || ((count_XC>1) && (count_XL>1)) || ((count_IX>1) && (count_IV>1)))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((error_check[0]>0 && count_C>0) || (error_check[1]>0 && count_X>0) || (error_check[2]>0 && count_I>0))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((error_check[3]>0 && count_X>1 && count_IX==0) || (error_check[4]>0 && count_X==3 && count_IX==1) || (error_check[4]>0 && count_X==3 && count_IX==0))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((error_check[5]>0 && count_X>1 && count_IX==0) || (error_check[6]>0 && count_X==3 && count_IX==1) || (error_check[6]>0 && count_X==3 && count_IX==0) )
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((error_check[7]>0 && count_C>1 && count_XC==0) || (error_check[8]>0 && count_C==3 && count_XC==1) || (error_check[8]>0 && count_C>2 && count_XC==0))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    if ((error_check[9]>0 && count_C>1 && count_XC==0) || (error_check[10]>0 && count_C==3 && count_XC==1) || (error_check[10]>0 && count_C>2 && count_XC==0))
    {error=1;printf("Not a valid roman number in operand %d \n", operand_ID);return error;}
    
    free(order_ID);
    return error;
}


/* roman numerical to decimal conversion function */
short roman_to_decimal(char *roman_num, int operand_ID)
{
    
    /* declaration and initialization */
    int i=0;
    short decimal_sum=0;
    
    int num_length = strlen(roman_num);
    short *decimal_array=calloc(sizeof(short),num_length);
        if (decimal_array==NULL)
		{
			printf ("Error allocating requested memory");
			exit (1);
		}
    
    /* algorithm */
    while (i<num_length)
    {
        
        switch (*roman_num)
        {
            case 'M':
                decimal_array[i]=1000;
                break;
            case 'D':
                decimal_array[i]=500;
                break;
            case 'C':
                decimal_array[i]=100;
                break;
            case 'L':
                decimal_array[i]=50;
                break;
            case 'X':
                decimal_array[i]=10;
                break;
            case 'V':
                decimal_array[i]=5;
                break;
            case 'I':
                decimal_array[i]=1;
                break;
            default:
                break;
        }
        roman_num++;
        i++;
    }
    
    
    /* subtracting digits are defined as negative numbers in array */
    for (i=(num_length-1); i>0; i--)
    {
        if (decimal_array[i]>decimal_array[i-1])
        {
            if (decimal_array[i]==(10*decimal_array[i-1]) || decimal_array[i]==(5*decimal_array[i-1]) )
            {decimal_array[i-1]=(-decimal_array[i-1]);}
        }
    }
    
    
    
    /* summation of digits  */
    for (i=0; i<num_length; i++)
    {
        decimal_sum=decimal_sum+decimal_array[i];
    }
    
    
    free(decimal_array);
    
    return decimal_sum;
    
}



/* decimal to ruman numerical conversion */
char * decimal_to_roman(short decimal_num)
{
    /* decleration and initialization */
    char *roman_sum;
    char *startpoint_roman_sum;
    roman_sum=calloc(sizeof(char),50);
        if (roman_sum==NULL)
		{
			printf ("Error allocating requested memory");
			exit (1);
		}
    
    startpoint_roman_sum=roman_sum;
    
    
    /* algorithm */
    while (decimal_num>999)
    {
        *roman_sum='M';
        decimal_num=(decimal_num-1000);
        roman_sum++;
    }
    
    /* 100 to 1000 routine */
    if (decimal_num>899)
    {
        *roman_sum='C';
        roman_sum++;
        *roman_sum='M';
        roman_sum++;
        decimal_num=(decimal_num-900);
    }
    else if (decimal_num>499)
    {
        *roman_sum='D';
        roman_sum++;
        decimal_num=(decimal_num-500);
    }
    else if (decimal_num>399)
    {
        *roman_sum='C';
        roman_sum++;
        *roman_sum='D';
        roman_sum++;
        decimal_num=(decimal_num-400);
    }
    
    
    while (decimal_num>99)
    {
        *roman_sum='C';
        decimal_num=(decimal_num-100);
        roman_sum++;
    }
    
    /* 10 to 100 routine */
    if (decimal_num>89)
    {
        *roman_sum='X';
        roman_sum++;
        *roman_sum='C';
        roman_sum++;
        decimal_num=(decimal_num-90);
    }
    else if (decimal_num>49)
    {
        *roman_sum='L';
        roman_sum++;
        decimal_num=(decimal_num-50);
    }
    else if (decimal_num>39)
    {
        *roman_sum='X';
        roman_sum++;
        *roman_sum='L';
        roman_sum++;
        decimal_num=(decimal_num-40);
    }
    
    /* 1 to 10 routine */
    while (decimal_num>9)
    {
        *roman_sum='X';
        decimal_num=(decimal_num-10);
        roman_sum++;
    }
    
    if (decimal_num>8)
    {
        *roman_sum='I';
        roman_sum++;
        *roman_sum='X';
        roman_sum++;
        decimal_num=(decimal_num-9);
    }
    else if (decimal_num>4)
    {
        *roman_sum='V';
        roman_sum++;
        decimal_num=(decimal_num-5);
    }
    else if (decimal_num>3)
    {
        *roman_sum='I';
        roman_sum++;
        *roman_sum='V';
        roman_sum++;
        decimal_num=(decimal_num-4);
    }
    
    while (decimal_num>0)
    {
        *roman_sum='I';
        decimal_num=(decimal_num-1);
        roman_sum++;
    }
    
    
    startpoint_roman_sum=(char*) realloc(startpoint_roman_sum,strlen(startpoint_roman_sum)+1);
    
    return startpoint_roman_sum;
    
}

/* addition nondecimal function */
char * addition_nondecimal(char *roman_num1, char *roman_num2)
{
    char *roman_sum;
    int error=0;
    char onhand_basket[7]={0,0,0,0,0,0,0};
    char borrow_basket[7]={0,0,0,0,0,0,0};
    
    /* roman numerical validity check */
    error=(roman_num_validity(roman_num1, (int) 1)+ roman_num_validity(roman_num2,(int) 2));
    
    if (error==0)
    {
        
        /* distribute operand 1 and 2 to onhand and borrow baskets according to subtraction*/
        string_baskets(roman_num1,onhand_basket,borrow_basket);
        string_baskets(roman_num2,onhand_basket,borrow_basket);
        
        /* unite borrow basket into onhand_basket */
        error=basket_union(onhand_basket,borrow_basket);
        /* unite onhand basket into roman numerical string */
        if (error==0)
        {
            roman_sum=convert_baskets_to_string(onhand_basket);
            return roman_sum;
        }
        else
            return error_output;
    }
    else
        return error_output;
}

/* subtraction nondecimal function */
char * subtraction_nondecimal(char *roman_num1, char *roman_num2)
{
    char *roman_sum;
    int error=0;
    char onhand_basket[7]={0,0,0,0,0,0,0};
    char borrow_basket[7]={0,0,0,0,0,0,0};
    
    /* roman numerical validity check */
    error=(roman_num_validity(roman_num1, (int) 1)+ roman_num_validity(roman_num2,(int) 2));
    
    if (error==0)
    {
        /* distribute operand 1 and 2 to onhand and borrow baskets according to subtraction*/
        string_baskets(roman_num1,onhand_basket,borrow_basket);
        string_baskets(roman_num2,borrow_basket,onhand_basket);
        
        /* unite borrow basket into onhand_basket */
        error=basket_union(onhand_basket,borrow_basket);
        
        /* unite onhand basket into roman numerical string */
        if (error==0)
        {
            roman_sum=convert_baskets_to_string(onhand_basket);
            return roman_sum;
        }
        else
            return error_output;
    }
    else
        return error_output;
}

/* distribute roman numericals into onhand and borrow baskets addding values (ex. X inside IX) in onhand, subtracting values (ex. I inside IX) in borrow basket */
void string_baskets(char *roman_num,char *onhand_basket, char *borrow_basket)
{
    /* declaration and initialization */
    int i=0;
    int j=0;
    short decimal_sum=0;
    
    int num_length = strlen(roman_num);
    int *order_ID=calloc(sizeof(int),num_length);
    char *start_roman_num=roman_num;
        if (order_ID==NULL)
		{
			printf ("Error allocating requested memory");
			exit (1);
		}
    
    
    /* algorithm */
    /* put all numaricals into onhand basket */
    while (i<num_length)
    {
        switch (*roman_num)
        {
            case 'M':
                onhand_basket[6]++;
                break;
            case 'D':
                onhand_basket[5]++;
                break;
            case 'C':
                onhand_basket[4]++;
                break;
            case 'L':
                onhand_basket[3]++;
                break;
            case 'X':
                onhand_basket[2]++;
                break;
            case 'V':
                onhand_basket[1]++;
                break;
            case 'I':
                onhand_basket[0]++;
                break;
            default:
                break;
        }
        roman_num++;
        i++;
    }
    
    /* create an array that shows magnitude of each char inside roman numerical */
    roman_num=start_roman_num;
    while (j<num_length)
    {
        switch (*roman_num)
        {
            case 'M':
                order_ID[j]=6;
                break;
            case 'D':
                order_ID[j]=5;
                break;
            case 'C':
                order_ID[j]=4;
                break;
            case 'L':
                order_ID[j]=3;
                break;
            case 'X':
                order_ID[j]=2;
                break;
            case 'V':
                order_ID[j]=1;
                break;
            case 'I':
                order_ID[j]=0;
                break;
            default:
                break;
        }
        j++;
        roman_num++;
    }
    
    /* find and take the subtracting numaricals from onhand basket to borrow one (ex. I inside IX goes to borrow basket  */
    for (i=(num_length-1); i>0; i--)
    {
        if (order_ID[i]>order_ID[i-1])
        {
            if (order_ID[i]==((order_ID[i-1])+2) || order_ID[i]==((order_ID[i-1])+1) )
            {(borrow_basket[order_ID[i-1]])++;(onhand_basket[order_ID[i-1]])--;}
        }
    }
    
    free(order_ID);
}

/* unite the onhand and borrow baskets into one basket  */
/* it subtracts the borrow ones from the onhand basket, if it couldn't find any insuide onhand basket, it calls distribute_baskets function */
int basket_union(char* onhand_basket,char* borrow_basket)
{
    int error=0;
    
    if (onhand_basket[6] >= borrow_basket[6])
    {onhand_basket[6]=(onhand_basket[6] - borrow_basket[6]);borrow_basket[6]=0;}
    else
    {error=1;printf("Zero or negative outputs can not express by romen numerals \n");return error;}
    
    if (onhand_basket[5] < borrow_basket[5])
        error=distribute_baskets(onhand_basket,5);
    if (error==0)
    {onhand_basket[5]=(onhand_basket[5] - borrow_basket[5]);borrow_basket[5]=0;}
    
    if (onhand_basket[4] < borrow_basket[4])
        error=distribute_baskets(onhand_basket,4);
    if (error==0)
    {onhand_basket[4]=(onhand_basket[4] - borrow_basket[4]);borrow_basket[4]=0;}
    
    if (onhand_basket[3] < borrow_basket[3])
        error=distribute_baskets(onhand_basket,3);
    if (error==0)
    {onhand_basket[3]=(onhand_basket[3] - borrow_basket[3]);borrow_basket[3]=0;}
    
    if (onhand_basket[2] < borrow_basket[2])
        error=distribute_baskets(onhand_basket,2);
    if (error==0)
    {onhand_basket[2]=(onhand_basket[2] - borrow_basket[2]);borrow_basket[2]=0;}
    
    if (onhand_basket[1] < borrow_basket[1])
        error=distribute_baskets(onhand_basket,1);
    if (error==0)
    {onhand_basket[1]=(onhand_basket[1] - borrow_basket[1]);borrow_basket[1]=0;}
    
    if (onhand_basket[0] < borrow_basket[0])
        error=distribute_baskets(onhand_basket,0);
    if (error==0)
    {onhand_basket[0]=(onhand_basket[0] - borrow_basket[0]);borrow_basket[0]=0;}
    
    if ((onhand_basket[0]+onhand_basket[1]+onhand_basket[2]+onhand_basket[3]+onhand_basket[4]+onhand_basket[5]+onhand_basket[6])==0)
        error=1;
    
    if (error==1)
    {printf("Zero or negative outputs can not express by romen numerals \n");}
    return error;
}

/* takes one from the higher numerical basket and distribute its value into lower numarical baskets */
int distribute_baskets(char *onhand_basket, char i)
{
    int error=0;
    
    if ((onhand_basket[6] > 0) && i<6)
    {
        (onhand_basket[6])--;
        (onhand_basket[5])++;
        (onhand_basket[4])= (onhand_basket[4])+4;
        (onhand_basket[3])++;
        (onhand_basket[2])= (onhand_basket[2])+4;
        (onhand_basket[1])++;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else if ((onhand_basket[5] > 0) && i<5)
    {
        (onhand_basket[5])--;
        (onhand_basket[4])= (onhand_basket[4])+4;
        (onhand_basket[3])++;
        (onhand_basket[2])= (onhand_basket[2])+4;
        (onhand_basket[1])++;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else if ((onhand_basket[4] > 0) && i<4)
    {
        (onhand_basket[4])--;
        (onhand_basket[3])++;
        (onhand_basket[2])= (onhand_basket[2])+4;
        (onhand_basket[1])++;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else if ((onhand_basket[3] > 0) && i<3)
    {
        (onhand_basket[3])--;
        (onhand_basket[2])= (onhand_basket[2])+4;
        (onhand_basket[1])++;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else if ((onhand_basket[2] > 0) && i<2)
    {
        (onhand_basket[2])--;
        (onhand_basket[1])++;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else if ((onhand_basket[1] > 0) && i<1)
    {
        (onhand_basket[1])--;
        (onhand_basket[0])= (onhand_basket[0])+5;
    }
    else
    {error=1;printf("Zero or negative outputs can not express by romen numerals \n");}
    return error;
}


/* convert the numbers inside onhand basketinto the string */
char * convert_baskets_to_string(char *onhand_basket)
{
    /* declaration and initialization */
    char *roman_sum;
    char *startpoint_roman_sum;
    roman_sum=calloc(sizeof(char),50);
    if (roman_sum==NULL)
		{
			printf ("Error allocating requested memory");
			exit (1);
		}
    
    startpoint_roman_sum=roman_sum;
    
    /* distribute numericals inside basket from lower ones to higher (eg. 5 I numerical inside onhand_basket[0] convert into 1 V)*/
    while (onhand_basket[0]>4)
    {onhand_basket[0]=(onhand_basket[0]-5);(onhand_basket[1])++;}
    while (onhand_basket[1]>1)
    {onhand_basket[1]=(onhand_basket[1]-2);(onhand_basket[2])++;}
    while (onhand_basket[2]>4)
    {onhand_basket[2]=(onhand_basket[2]-5);(onhand_basket[3])++;}
    while (onhand_basket[3]>1)
    {onhand_basket[3]=(onhand_basket[3]-2);(onhand_basket[4])++;}
    while (onhand_basket[4]>4)
    {onhand_basket[4]=(onhand_basket[4]-5);(onhand_basket[5])++;}
    while (onhand_basket[5]>1)
    {onhand_basket[5]=(onhand_basket[5]-2);(onhand_basket[6])++;}
    
    /* the number of values inside baskets are added to the string*/
    /* if there are special cases IV, IX, XC ..etc, they are added by if sentences */
    while (onhand_basket[6]>0)
    {*roman_sum='M'; roman_sum++;(onhand_basket[6])--;}
    
    if ((onhand_basket[5]==1) && (onhand_basket[4]==4))
    {*roman_sum='C'; roman_sum++; *roman_sum='M'; roman_sum++;(onhand_basket[5])--;(onhand_basket[4])--;}
    else if ((onhand_basket[5]==0) && (onhand_basket[4]==4))
    {*roman_sum='C'; roman_sum++; *roman_sum='D'; roman_sum++;(onhand_basket[4])--;}
    else
    {
        while (onhand_basket[5]>0)
        {*roman_sum='D'; roman_sum++;(onhand_basket[5])--;}
        while (onhand_basket[4]>0)
        {*roman_sum='C'; roman_sum++;(onhand_basket[4])--;}
    }
    
    if ((onhand_basket[3]==1) && (onhand_basket[2]==4))
    {*roman_sum='X'; roman_sum++; *roman_sum='C'; roman_sum++;(onhand_basket[3])--;(onhand_basket[2])--;}
    else if ((onhand_basket[3]==0) && (onhand_basket[2]==4))
    {*roman_sum='X'; roman_sum++; *roman_sum='L'; roman_sum++;(onhand_basket[2])--;}
    else
    {
        while (onhand_basket[3]>0)
        {*roman_sum='L'; roman_sum++;(onhand_basket[3])--;}
        while (onhand_basket[2]>0)
        {*roman_sum='X'; roman_sum++;(onhand_basket[2])--;}
    }
    
    if ((onhand_basket[1]==1) && (onhand_basket[0]==4))
    {*roman_sum='I'; roman_sum++; *roman_sum='X'; roman_sum++;(onhand_basket[1])--;(onhand_basket[0])--;}
    else if ((onhand_basket[1]==0) && (onhand_basket[0]==4))
    {*roman_sum='I'; roman_sum++; *roman_sum='V'; roman_sum++;(onhand_basket[0])--;}
    else
    {
        while (onhand_basket[1]>0)
        {*roman_sum='V'; roman_sum++;(onhand_basket[1])--;}
        while (onhand_basket[0]>0)
        {*roman_sum='I'; roman_sum++;(onhand_basket[0])--;}
    }
    
    
    startpoint_roman_sum=(char*) realloc(startpoint_roman_sum,strlen(startpoint_roman_sum)+1);
    
    return startpoint_roman_sum;
}


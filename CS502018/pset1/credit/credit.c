#include <stdio.h>
#include <cs50.h>
#include <string.h>

//Proto for whatCard function
void whatCard(long long num, int length);

int main(void)
{
    //declare credit number variable
    long long number = 0;

    //ask user for credit card number
    number = get_long_long("Enter the credit card number: ");

    //create a copy of a number to count the number
    long long creditCopy = number;
    int creditLength = 0;

    while(creditCopy != 0)
    {
        creditCopy /= 10;
        creditLength++;
    }

    //checks if the number is the proper length
    if(creditLength != 15 && creditLength != 16 && creditLength != 13)
    {
        printf("INVALID\n");
    }

    //flag for everyother number
    bool flag = false;

    //sum variable declared
    int sum = 0;

    //reset variable to credit card number
    creditCopy = number;

    //goes through each number of the credit number
    for(int i = 0; i < creditLength; i++)
    {

        //flag to check if it is every other number
        if(flag == true)
        {
            //gets the digit and times by 2
            int firstNum = ((creditCopy % 10) * 2);

            //if the number is greater than 10
            if(firstNum >= 10)
            {
                //goes through each digit and adds them
                for(int j = 0; j < 2; j++)
                {
                    sum = sum + (firstNum % 10);
                    firstNum /= 10;
                }
            }

            //adds number to sum
            else
            {
                sum = sum + firstNum;
            }

            //move on the next digit and make the flag false to skip the next one
            creditCopy /= 10;
            flag = false;
        }

        //get the digit and add it to sum
        else
        {
            int num = creditCopy % 10;
            sum = sum + num;
            creditCopy /= 10;
            flag = true;
        }
    }

    //checks if sum ends in 0
    if((sum % 10) == 0)
    {
        //call function to find out what card type it is
        whatCard(number, creditLength);
    }

    //if sum does not have 0 at the end print invalid
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

//whatCard prints what kind of card it is
void whatCard(long long num, int length)
{
    //declare array to store num in
    int numArray[length];

    //counter is length - 1 since arrays start at 0
    int counter = length - 1;

    //goes through each array and puts a variable from num
    for(int i = 0; i < length; i++)
    {
        numArray[counter] = (num % 10);
        counter--;
        num /= 10;
    }

    //check if card is a VISA
    if(numArray[0] == 4)
    {
        printf("VISA\n");
    }

    //checks if card is an American Express
    else if(numArray[0] == 3)
    {
        if(numArray[1] == 4 || numArray[1] == 7)
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    //checks if card is a MasterCard
    else if(numArray[0] == 5)
    {
        if(numArray[1] == 1 ||numArray[1] == 2 ||numArray[1] == 3 ||numArray[1] == 4 ||numArray[1] == 5)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    //prints invalid if no card starts with certain numbers
    else
    {
        printf("INVALID\n");
    }
}
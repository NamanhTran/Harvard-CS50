#import the cs50 library
import cs50

def main():
    #gets the credit card number
    number = cs50.get_string("Number: ")

    #gets the credit card length
    length = len(number)

    #checks if the length of the number is one of the card type
    if length != 15 and length != 16 and length != 13:

        print("INVALID")

        return 1

    #finds the credit card type
    type = credit_type(number)

    #end program is credit_type returned false
    if type == False:
        print("INVALID")
        return 1

    #checks if the card number is valid
    valid = check_sum(number, length)

    #prints the type if card is valid
    if valid == True:
        print(type)

    #prints if not valid
    else:
        print("INVALID")

    return 0



def credit_type(n):

    #set the first two numbers of the
    n = n[0] + n[1]

    #if first number is 4 return VISA
    if n[0] == '4':
        return "VISA"

    #if first two number is 51, 52, 53, 54, 55 return MASTER
    elif n == "51" or n == "52" or n == "53" or n == "54" or n == "55":
        return "MASTERCARD"

    #if first two number is 34 or 37 return AMEX
    elif n == "34" or n == "37":
        return "AMEX"

    #if can't identify return false
    else:
        return False

def check_sum(number, length):

    #cast the credit card number string to a int
    intNumber = int(number)

    #declare the sum variable
    sum = 0

    #declare the index that will be use to go through the number string
    index = length - 1

    #flag to determine whether it the every other number
    flag = 0

    #loops through the number string
    for i in range(length):

        #if every other number
        if flag == 1:

            #cast the number in question to an int
            temp = int(number[index])

            #multiply the number by 2
            temp *= 2

            #add to the sum variable
            sum += 2

            #truncate the number
            intNumber //= 10

            #reduce the index
            index -= 1

            #not it's is not the other number
            flag = 0

        #if the other number
        else:

            #truncate the last digit
            intNumber //= 10

            #move index back
            index -= 1

            #now is the other number
            flag = 1

    #return True if valid
    if sum % 2 == 0:
        return True

    #return False if not vaid
    else:
        return False




if __name__ == "__main__":
    main()
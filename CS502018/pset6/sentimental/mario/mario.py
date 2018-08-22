#imports the cs50 library
import cs50

#initalize the input variable
input = 0

#keeps looping until user enters correct input
while True:
    input = cs50.get_int("Height: ")

    if input >= 0 and input <= 23:
        break

#initalize space and block variable
space = input - 1
block = 1

#loops through the rows
for i in range(input):

    #creates the space before the blocks
    for j in range(space):
        print(" ", end="")

    #creates the block
    for k in range(block):
        print("#", end="")

    #prints the gap
    print("  ", end="")

    #prints the second set of blocks
    for k in range(block):
        print("#", end="")

    #prints the space
    print()

    #decrement the space and block
    space -= 1
    block += 1
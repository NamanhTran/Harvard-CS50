import sys
import cs50

def main():

    #checks for proper command line arguments
    if len(sys.argv) != 2:
        print("Usage: python vigenere.py k")
        sys.exit(1)

    elif not sys.argv[1].isalpha():
        print("Usage: python vigenere.py k")
        sys.exit(1)

    #gets the key from the commpand line argument
    key = sys.argv[1]

    #get the plaintext from the user
    plaintext = cs50.get_string("plaintext: ")

    #run the cipher against the plaintext
    ciphertext = cipher(plaintext, key)

    #prints the ciphertext
    print(f"ciphertext: {ciphertext}")

def cipher(plaintext, key):

    #declare the ciphertext string
    ciphertext = ""

    #set all letters in the key to lowercase
    key = key.lower()

    #counter for the key wraparound
    counter = 0

    #loop through each character through the plaintext
    for i in range(len(plaintext)):

        #set the key to an int
        temp = ord(key[counter % len(key)]) - 97

        #if the letter is uppercase
        if plaintext[i].isupper():

            #run the algorithm
            ciphertext += chr(((ord(plaintext[i]) - 65 + temp) % 26) + 65)

            #counter for the key
            counter += 1

        #if the letter is lowercase
        elif plaintext[i].islower():

            #run the algorithm
            ciphertext += chr(((ord(plaintext[i]) - 97 + temp) % 26) + 97)

            #counter for the key
            counter += 1

        #if the letter is not alpha
        else:

            #add to the ciphertext string
            ciphertext += plaintext[i]

    #return the ciphertext
    return ciphertext


if __name__ == "__main__":
    main()
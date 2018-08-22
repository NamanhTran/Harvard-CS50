import sys
import cs50

def main():

    #check if proper arguements are passed
    if len(sys.argv) != 2:
        print("Usage: python caesar.py k")
        sys.exit(1)

    #cast key from string to int
    key = int(sys.argv[1])

    #get the plaintext
    plaintext = cs50.get_string("plaintext: ")

    #run the plaintext into the cipher function
    ciphertext = cipher(plaintext, key)

    #prints the cipher text
    print(f"ciphertext: {ciphertext}")

def cipher(plaintext, key):

    #declare ciphertext string
    ciphertext = ""

    #go through each character and cipher it
    for i in range(len(plaintext)):

        #if the letter is upper
        if plaintext[i].isupper():

            #runs the algorithm
            ciphertext += chr(((ord(plaintext[i]) - 65 + key) % 26) + 65)

        #if the letter is lower
        elif plaintext[i].islower():

            #runs the algorithm
            ciphertext += chr(((ord(plaintext[i]) - 97 + key) % 26) + 97)

        #if it is a special character
        else:

            #just add the character to the string
            ciphertext += plaintext[i]

    #return ciphertext
    return ciphertext

if __name__ == "__main__":
    main()
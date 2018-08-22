import sys
import cs50

def main():
    if len(sys.argv) != 2:

        print("useage: python vigenere.py [number]")

        exit(1)

    key = sys.argv[1]

    for i in range(len(sys.argv[1])):

        if str.isalpha(key[i]) == False:

            print("ERROR: Argument contains number")

            exit(2)

    print("Plaintext:", end="")

    plaintext = cs50.get_string

    print("Ciphertext:", end="")

    plainlen = len(plaintext)

    keylen = len(key)

    counter = 0

    for n in range(plainlen):

        counter = counter % keylen

        intplain = int(plaintext[n])

        if plaintext[counter].isalpha() == True:

            if plaintext[counter].islower() == True:

                ctext = (((intplain - 65) + (int(key[counter]) - 65)) % 26) + 65

                print("{}".format(chr(ctext)), end="")
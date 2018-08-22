import cs50

def main():

    print("Height:", end="")

    height = get_height()

    for i in range(height):

        print(" " * (height - 1), end ="")

        print("#" * (i + 2), end="")

        print("")

        height = height - 1

def get_height():

    while True:
        n = cs50.get_int()

        if n > 0 and n <= 23:
            break

    return n

if __name__ == "__main__":
    main()
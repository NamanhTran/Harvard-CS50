import cs50

print("O hai! How much change is owed?")

coins = 0

while True:
    amount = cs50.get_float()
    if (amount >= 0):
        break
    print("How much change is owed?")

amount = round(amount * 100)

while True:
    if amount >= 25:
        amount -= 25
        coins += 1

    elif amount >= 10:
        amount -= 10
        coins += 1

    elif amount >= 5:
        amount -= 5
        coins += 1

    elif amount >= 1:
        amount -= 1
        coins += 1

    elif amount == 0.0:
        print("{}".format(coins))
        break
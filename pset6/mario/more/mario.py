import cs50

while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height <= 8:
        break

for i in range(1, height + 1, 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)
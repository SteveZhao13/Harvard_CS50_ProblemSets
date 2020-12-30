import cs50

card = cs50.get_string("Number: ")

sum = 0
card_odd = card[len(card)-2::-2]
card_even = card[::-2]

for odd in card_odd:
    tmp = int(odd) * 2
    for i in str(tmp):
        sum += int(i)

for even in card_even:
    sum += int(even)

if sum % 10 == 0:
    if len(card) == 15 and (card[0:2] in ['34', '37']):
        print("AMEX")
    elif len(card) == 16 and (card[0:2] in ['51', '52', '53', '54', '55']):
        print("MASTERCARD")
    elif len(card) in [13, 16] and card[0] == '4':
        print("VISA")
    else:
        print("INVALID")

else:
    print("INVALID")
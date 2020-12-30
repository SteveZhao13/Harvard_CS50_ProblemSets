import cs50

text = cs50.get_string("Text: ")

letter_count = 0
word_count = 1
sentence_count = 0

for c in text:
    if c.isalpha():
        letter_count += 1
    if c == ' ':
        word_count += 1
    if c in ['.', '?', '!']:
        sentence_count += 1

L = letter_count / word_count * 100
S = sentence_count / word_count * 100
result = round(0.0588 * L - 0.296 * S - 15.8)

if result < 1:
    print("Before Grade 1")
elif result >= 16:
    print("Grade 16+")
else:
    print(f"Grade {result}")
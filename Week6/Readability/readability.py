text = input("Text: ")
L = 0
S = 0
W = 1
punctArray = [".", "?", "!"]

for i in text:
    if (i.isspace()):
        W += 1
    elif (i.isalpha()):
        L += 1
    elif (i in punctArray):
        S += 1

cal = round((0.0588 * (L/W) * 100) - (0.296 * (S/W) * 100) - 15.8)

if (cal < 1):
    print("Before Grade 1")

elif (1 <= cal < 16):
    print("Grade", cal)

elif (cal >= 16):
    print("Grade 16+")

else:
    print("INVALID")

import copy
num = int(input("Number: "))
numToStr = str(copy.deepcopy(num))
lenArray = [13, 15, 16]
masterArray = ["1", "2", "3", "4", "5"]
counter = 0
sum = 0
digit = 0

if (len(numToStr) == lenArray[0]):
    if (numToStr[0] == "4"):
        for i in range(len(numToStr)):
            if ((i+1) % 2 == 0):
                rem = num % pow(10, i+1)
                digit = (rem // pow(10, i))*2
                if digit >= 10:
                    sum = sum + (digit // 10) + (digit % 10)
                else:
                    sum = sum + digit
            else:
                rem = num % pow(10, i+1)
                digit = rem // pow(10, i)
                sum = sum + digit
        if sum % 10 == 0:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

elif (len(numToStr) == lenArray[1]):
    if (numToStr[0] == "3" and (numToStr[1] == "4" or numToStr[1] == "7")):
        for i in range(len(numToStr)):
            if ((i+1) % 2 == 0):
                rem = num % pow(10, i+1)
                digit = (rem // pow(10, i))* 2
                if digit >= 10:
                    sum = sum + (digit // 10) + (digit % 10)
                else:
                    sum = sum + digit
            else:
                rem = num % pow(10, i+1)
                digit = rem // pow(10, i)
                sum = sum + digit
        if sum % 10 == 0:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")

elif (len(numToStr) == lenArray[2]):
    if (numToStr[0] == "5" and numToStr[1] in masterArray):
        for i in range(len(numToStr)):
            if ((i+1) % 2 == 0):
                rem = num % pow(10, i+1)
                digit = (rem // pow(10, i))*2
                if digit >= 10:
                    sum = sum + (digit // 10) + (digit % 10)
                else:
                    sum = sum + digit
            else:
                rem = num % pow(10, i+1)
                digit = rem // pow(10, i)
                sum = sum + digit
        if sum % 10 == 0:
            print("MASTERCARD")
        else:
            print("INVALID")
    elif (numToStr[0] == "4"):
        for i in range(len(numToStr)):
            if ((i+1) % 2 == 0):
                rem = num % pow(10, i+1)
                digit = (rem // pow(10, i))*2
                if digit >= 10:
                    sum = sum + (digit // 10) + (digit % 10)
                else:
                    sum = sum + digit
            else:
                rem = num % pow(10, i+1)
                digit = rem // pow(10, i)
                sum = sum + digit
        if sum % 10 == 0:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

else:
    print("INVALID")

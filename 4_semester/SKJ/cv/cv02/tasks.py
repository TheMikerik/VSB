def fizzbuzz(num):
    if num % 3 == 0 and num % 5 == 0:
        return "FizzBuzz"
    elif num % 3 == 0:
        return "Fizz"
    elif num % 5 == 0:
        return "Buzz"
    else:
        return num
    pass


def fibonacci(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci(n-2) + fibonacci(n-1) 
    pass

def dot_product(a, b):
    length = len(a)
    res = 0
    for i in range(length):
        res += a[i] * b[i] 
    return res
    pass


def redact(data, chars):
    output = ""
    for char in data:
        if char in chars:
            output += 'x'
        else:
            output += char
    return output
    pass

def count_words(data):
    if not data:
        return {}
    
    words = data.split(" ")
    word_count = {}
    
    for word in words:
        if word in word_count:
            word_count[word] += 1
        else:
            word_count[word] = 1
    
    return word_count
    pass




def bonus_fizzbuzz(num):
    pass
def bonus_utf8(cp):
    pass
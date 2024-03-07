import random

# cv03 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

lst1 = [[f'{x}:{y}' for y in range(10)] for x in range(10)]
# print(lst1)

lst2 = {k:v for k,v in zip(range(10), range(10, 20))}
# print(lst2)

dict = [random.randint(1,6) for x in range(1000)]
# print(dict)

# Mnoziny - unikatni set prvku
s = set(dict)
# print(s)

for i,v in enumerate([random.randint(0,10) for x in range(10)]):
# print(f'{i}:{v}')

def lex_compare(a,b):
    for x,y zip(a,b):
        if x < y:
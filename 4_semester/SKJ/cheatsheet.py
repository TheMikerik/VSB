# File operations, context manager, exceptions, functions, iterators, generators, decorators

# Functions
# arbitrary and keyword parameters
def fn1(a, b, *l, **d):
    return (a, b, l, d)

fn1(1, 2, 3, 4, 5, t=5, x=8)    # (1, 2, (3, 4, 5), {'t': 5, 'x': 8})

# Default return value
def fn2():
    pass

fn2()   # None

# Default parameter value
def fn3(a=[]):
    a.append(5)
    return a

fn3()   # [5]
fn3()   # [5, 5] !!!

# Unpacking
def fn4(a, b):
    return a + b

fn4(*[1, 2])    # 3

def fnk(**w):
    print(w)

fnk(**{'a': 5, 'b': 6})  # {'a': 5, 'b': 6}

# Scope
a = 8
def fn5():
    a = 10
fn5()   # a == 8

a = 8
def fn6():
    global a # refer to `a` in global scope
    a = 10
fn6()   # a == 10


def fn7(x):
    def fn():
        nonlocal x # refer to `x` in outer function scope
        print(x)
        x += 1
    return fn

x = fn7(1)
x()
x()

def fn8(p1, p2, *, kw_only_1, kw_only_2):
    pass

fn8(1, 2, kw_only_1=1, kw_only_2=2)
# fn8(1, 2, 3) # error

# Lambda functions
a = lambda x: x + 1
a(8)    # 9


# Closures
def make_closure(x):
    return lambda: x + 1

a = make_closure(5)
a() # 6
a() # 6


# Higher-order functions
def map(seq, fn):
    return [fn(x) for x in seq]


def filter(seq, fn):
    return [x for x in seq if fn(x)]


# Iterators
l = [1, 2, 3]
for x in l:
    print(x)

# translates to

it = iter(l)
while True:
    try:
        x = next(it)
        print(x)
    except StopIteration:
        break


# Generators
def gen():
    yield 1
    yield 2
    x = 3
    for i in range(3):
        yield x
        x += 1

print([x for x in gen()])   # [1, 2, 3, 4, 5]


def gen2():
    yield from gen()
    yield 6
print([x for x in gen2()])  # [1, 2, 3, 4, 5, 6]


def gen3():
    a = yield 5
    yield a + 1

g = gen3()
print(next(g))      # 5
print(g.send(8))    # 9


def xml(input):
    tag = ""
    state = 0 # 0 = nic, 1 = tag

    for i in input:
        if state == 0 and i == "<":
            state = 1
        elif state == 1:
            if i == ">":
                state = 0
                yield tag
                tag = ""
            else:
                tag += i


# Decorators
def decorator(f):
    x = 5
    def wrapper(*args, **kwargs):
        nonlocal x
        print("wrapper called: {}".format(x))
        return f(*args, **kwargs)
    return wrapper


@decorator
# @decorator() # This does something different!
def fn(x):
    print(x)

fn(5)

import time
import contextlib


# Create own context generator
@contextlib.contextmanager
def timer():
    print("start")
    start = time.time()
    try:
        yield
    finally:
        print(f"end, duration: {time.time() - start}")

with timer():
    # do something
    pass


# File operations
f = open("file.txt", "r+") # r == read, w == write, a == append, r+,w+,a+ - read and write, rb/wb/ab == read/write/append in byte mode
f.write("hello\n")
f.writelines("\n".join(["a", "b", "c"]))
f.seek(0)
for l in f: # iterates over lines in f
    print(l.strip())

f.flush()   # flush write buffers
f.close()   # close the file
exit()

# Context manager
# automatically closes file at the end of the `with` block
with open("file.txt", "r") as f:
    # work with f
    pass
# here f was closed

# Exceptions
try:
    raise Exception("hello")
except (KeyError, ValueError) as e:
    # executes if there was an exception of type KeyError or ValueError
    pass
except Exception as e:
    raise e     # reraise exception
    # raise Exception('wut') from e  # raise new exception, chain it with `e`
else:
    # executes if there was no exception
    pass
finally:
    # executes always
    pass
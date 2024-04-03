# Ukazka z hodiny

def cached(func):
    cache_args = None
    cache_ret = None
    def wrapper(*args):
        nonlocal cache_args
        nonlocal cache_ret
        if args == cache_args:
            cache_args = args
            cache_ret = func(*args)
            return cache_ret
        else:
            cache_args = args
            cache_ret = func(*args)
            return cache_ret
    return wrapper

runs = 0


def argsum(*args):
    global runs
    runs += 1
    return sum(args)

argsum(10)
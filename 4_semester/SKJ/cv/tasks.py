# Notes: nonlocal 




def is_palindrome(data):
    for i in range(len(data) // 2):
        if data[i] != data[-i - 1]:
            return False
    return True
    pass

def count_successive(string):
    if string == '':
        return []
    out = []
    char = string[0]
    count = 1
    for i in range(1, len(string)):
        if string[i] == char:
            count += 1
        else:
            out.append((char, count))
            char = string[i]
            count = 1
    out.append((char, count))
    return out


def create_appender(default_value):
    my_list = []
    
    def appender(input_value=""):
        if input_value == "":
            my_list.append(default_value)
        else:
            my_list.append(input_value)
        return my_list.copy()

    return appender

def fibonacci_closure():
    a = 1
    b = 1

    def next_fibonacci():
        nonlocal a, b
        result = a
        a, b = b, a + b  # Update a and b for the next Fibonacci number
        return result

    return next_fibonacci

def word_extractor(sentence):
    """
    Return a generator that will iterate through individual words from the input sentence.
    Words are separated by the following separators: space (' '), dot ('.'), exclamation mark ('!')
    and question mark ('?'). Skip empty words and separators.

    If you encounter the word "stop", ignore the word and stop the generator.

    Example:
        sentence = "Hello world. How are you doing today? I'm doing fine!"
        for word in word_extractor(sentence):
            print(i)
        # "Hello", "world", "How", "are", "you", "doing", "today", ...

        sentence = "Hello world stop this is not extracted anymore."
        for word in word_extractor(sentence):
            print(i)
        # "Hello", "world"
    """
    pass


def tree_walker(tree, order):
    """
    Write a generator that traverses `tree` in the given `order` ('inorder', 'preorder' or 'postorder').
    You should know this from 'Algoritmy II'.
    The tree is represented with nested tuples (left subtree, value, right subtree).
    If there is no subtree, it will be marked as None.
    Example:
        tree = (((None, 8, None), 3, (None, 4, None)), 5, (None, 1, None))
            5
           / \
          3   1
         / \
        8   4
        list(tree_walker(tree, 'inorder')) == [8, 3, 4, 5, 1]
        list(tree_walker(tree, 'preorder')) == [5, 3, 8, 4, 1]
        list(tree_walker(tree, 'postorder')) == [8, 4, 3, 1, 5]
    """
    pass
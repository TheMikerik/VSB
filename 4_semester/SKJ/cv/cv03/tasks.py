def is_palindrome(data):
    for i in range(len(data) // 2):
        if data[i] != data[-i - 1]:
            return False
    return True
    pass


def lex_compare(a, b):
    output_list = [a, b]
    output_list.sort()
    return output_list[0]
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
    pass



def find_positions(items):
    output_dict = {}

    for i in range(len(items)):
        item = items[i]
        if item in output_dict:
            output_dict[item].append(i)
        else:
            output_dict[item] = [i]
    return output_dict
    pass


def invert_dictionary(dictionary):
    output_dict = {}

    for key, value in dictionary.items():
        if value in output_dict:
            return None
        output_dict[value] = key
    return output_dict
    pass
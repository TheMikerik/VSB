import inspect
from collections import deque

from tasks import count_successive, create_appender, fibonacci_closure, is_palindrome, tree_walker, \
    word_extractor


def test_is_palindrome():
    assert is_palindrome('')
    assert is_palindrome('a')
    assert is_palindrome('aa')
    assert is_palindrome('aba')
    assert is_palindrome('AbA')
    assert is_palindrome('bbbb')
    assert not is_palindrome('ab')
    assert not is_palindrome('abc')
    assert not is_palindrome('abca')
    assert not is_palindrome('Aba')
    assert not is_palindrome('abc c ba')


def test_count_successive():
    assert count_successive("") == []
    assert count_successive("aaabbcccc") == [("a", 3), ("b", 2), ("c", 4)]
    assert count_successive("aabaaa") == [("a", 2), ("b", 1), ("a", 3)]
    assert count_successive("aaaa") == [("a", 4)]


def test_create_appender():
    appender = create_appender(5)
    assert appender(1) == [1]
    assert appender(2) == [1, 2]
    assert appender() == [1, 2, 5]
    assert appender() == [1, 2, 5, 5]

    appender = create_appender(0)
    l = appender(3)
    assert l == [3]
    l.append(8)
    assert appender() == [3, 0]


def test_word_extractor():
    gen = word_extractor("A B C.")
    assert inspect.isgenerator(gen)

    assert next(gen) == "A"
    assert next(gen) == "B"
    assert next(gen) == "C"

    sentence = "Hello world. How are you doing today? I'm doing fine!"

    assert list(word_extractor(sentence)) == ["Hello", "world", "How", "are", "you", "doing",
                                              "today", "I'm", "doing", "fine"]

    assert list(word_extractor("Stop stopword now stop. Ignore this.")) == ["Stop", "stopword",
                                                                            "now"]


def test_fibonacci_closure():
    f = fibonacci_closure()
    q = deque((f(), f()), maxlen=2)

    assert q[0] == 1
    assert q[1] == 1

    for _ in range(1000):
        x = f()
        assert x == sum(q)
        q.append(x)


def test_tree_walker():
    tree = (((None, 8, None), 3, (None, 4, None)), 5, (None, 1, None))
    assert list(tree_walker(tree, 'inorder')) == [8, 3, 4, 5, 1]
    assert list(tree_walker(tree, 'preorder')) == [5, 3, 8, 4, 1]
    assert list(tree_walker(tree, 'postorder')) == [8, 4, 3, 1, 5]

    assert list(tree_walker((None, 1, None), 'postorder')) == [1]

    tree = (((None, 1, None), 2, ((None, 3, None), 4, (None, 5, None))), 6,
            (None, 7, ((None, 9, None), 8, None)))
    assert list(tree_walker(tree, 'inorder')) == [1, 2, 3, 4, 5, 6, 7, 9, 8]
    assert list(tree_walker(tree, 'preorder')) == [6, 2, 1, 4, 3, 5, 7, 8, 9]
    assert list(tree_walker(tree, 'postorder')) == [1, 3, 5, 4, 2, 9, 8, 7, 6]
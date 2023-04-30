# Iterator Over Graph
This code starts [iterating](https://en.wikipedia.org/wiki/Iterator) over graph from the smallest number in each component of it.

## How to use it
There is no need to select graphs manually. Currently it autmatically load 7 graphs from Graphs folder.
So just type
```bash
g++ ./main.cpp -o iterator -Wall -Wextra -g -fsanitize=address -lm -lstdc++
```
Then just run it by
```bash
./iterator
```
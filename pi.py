#!/usr/bin/env python

import sys
import time

N = 10 ** 10000


def arctan(m):
    global N
    c = N
    a = b = c // m
    m2 = m * m
    s = k = 1
    while c:
        b //= m2
        k += 2
        c, s = b // k, -s
        a += c * s
    return a


def main(args):
    global N
    if len(args) > 1:
        N = 10 ** int(args[1])
    t1 = time.time()
    pi = str((arctan(5) * 4 - arctan(239)) * 4)
    t2 = time.time()
    print(pi[0] + "." + pi[1:])
    print("Time: {}".format(t2 - t1))


if __name__ == "__main__":
    main(sys.argv)

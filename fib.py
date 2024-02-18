#!/usr/bin/python

def fib(max):
    n,a,b=0,0,1
    while n<max:
        print("1")
        yield b
        a,b=b,a+b
        n=n+1
        print("123")
if __name__ == "__main__":
    f=fib(6)
    next(f)
    next(f)

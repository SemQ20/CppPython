def func(a = "asd", b = "sdfd", c = "asdq"):
    d = a, b, c
    print(__str__(type(d)), d)

def func1():
    a, b = func("sda","sdf", "sadje")
    print(a, b)

def main():
    func()

if __name__ == '__main__':
    main()
    
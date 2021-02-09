def func(a = "asd", b = "sdfd", c = "asdq"):
    d = a, b, c
    f = type(d).__str__(type(d))
    print(f)

def func1():
    a, b = func("sda","sdf", "sadje")
    print(a, b)

def main(a):
    func("sda0", "asdjnq", "sadiq")

if __name__ == '__main__':
    main()
    
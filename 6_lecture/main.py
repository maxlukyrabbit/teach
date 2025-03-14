import random
def create_mass(size_w, size_h):
    array = []
    for i in range(size_h):
        array.append([0] * size_w)
        for j in range(size_w):
            array[i][j] = random.randint(1, 99)
    return array

def print_array(array):
    for i in array:
        for j in i:
            print(j, end=" ")
        print("\n")

def max_elem(array):
    max = array[0][0]
    for i in array:
        for j in i:
            if max < j:
                max = j
    return max
a = create_mass(4, 5)
b = create_mass(5, 5)
c = create_mass(4, 6)

print("Массив a")
print_array(a)
print("Массив b")
print_array(b)
print("Массив c")
print_array(c)

max_a = max_elem(a)
max_b = max_elem(b)
max_c = max_elem(c)

print(f"max_a = {max_a}, max_b = {max_b}, max_c = {max_c}")



array = []
for i in range(4):
    array.append([0] * 4)
print(array)
for i in range(4):
    for j in range(4):
        a = input()
        array[i][j] = a
for i in range(4):
    for j in range(4):
        print(array[i][j], end=' ')
    print("\n")

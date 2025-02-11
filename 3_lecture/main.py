array = []
a = int(input("Вводите число, для остановки ввода укажите 0 "))
while a != 0:
    array.append(a)
    a = int(input("Вводите число, для остановки ввода укажите 0 "))
print(array)
array_end = []
for i in range(len(array)):
    for j in range(1, len(array)):
        if array[i] == array[j] and i != j:
            array[j] = 0
for i in array:
    if i != 0:
        array_end.append(i)

print(array_end)
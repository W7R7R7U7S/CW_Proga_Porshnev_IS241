import random
numbers = [random.randint(1, 10000000) for _ in range(32768)]
with open('sorted_numbers_random.txt', 'w') as file:
    for number in numbers:
        file.write(str(number) + '\n')

print("Файл 'sorted_numbers_random.txt' успешно создан с отсортированными числами.")



numbers1 = [random.randint(1, 10000000) for _ in range(32768)]
numbers1.sort()
with open('sorted_numbers_ascending.txt', 'w') as file:
    for number1 in numbers1:
        file.write(str(number1) + '\n')

print("Файл 'sorted_numbers_ascending.txt' успешно создан с отсортированными числами.")




numbers2 = [random.randint(1, 10000000) for _ in range(32768)]
numbers1.sort(reverse=True)
with open('sorted_numbers_descending.txt', 'w') as file:
    for number2 in numbers2:
        file.write(str(number2) + '\n')

print("Файл 'sorted_numbers_descending.txt' успешно создан с отсортированными числами.")
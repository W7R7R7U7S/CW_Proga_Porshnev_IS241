import random
numbers = [random.randint(1, 10000000000) for _ in range(32768)]
with open('sorted_numbers_random.txt', 'w') as file:
    for number in numbers:
        file.write(str(number) + '\n')

print("Файл 'sorted_numbers_random.txt' успешно создан с отсортированными числами.")
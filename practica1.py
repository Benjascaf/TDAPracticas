import time 

# Ej 1
#a) (Comsultar)
#Las soluciones candidatas serian aquellas tuplas de tres elementos cuyos vaores pueden ser 1 o 0
#o, en otras palabras, todas las posibles permutaciones de tuplas de tras elementos dodede cada elemento puede tomar solo dos valores.
#Algunos ejemplos: (0,0,0) (0,1,1) etc.

#b) (1,0,1) (0,1,0)

#c) (0) (1) (0,1) (0,0) (1,0) (1,1)

#d)

#f)
def subset_sum(c,i,j):
    if i == 0:
        return j == 0
    else:
        return subset_sum(c, i - 1, j) or subset_sum(c, i - 1, j - c[i - 1])



#h)
def subset_sum2(c, i, j):
    if j < 0:
        return False
    if i == 0: 
        return j == 0
    else: 
        return subset_sum(c, i - 1, j) or subset_sum(c, i - 1, j - c[i -1])

#i  Noc

#j
def ss (c, i, j, v):
    if j < 0:
        if v:
            #Remove last element to go back to previous state
            v.pop() 
        return False
    if i == 0:
        if j == 0:
            v.reverse()
            print(v)
            #No need to go back to previous step since execution will stop
            return True
        else:
            if (v):
                v.pop()
            return False
    else:
        v.append(c[i - 1])
        return ss(c, i - 1, j - c[i-1], v) or ss(c, i - 1, j, v)
    

#2
#a (n^2)!
#b

#Dictionary for fast lookup on whether or not a specific number isp present
missing_numbers = []
present_numbers = {}
generated_squares = []
global magic_num
magic_num = 0
def sum_col(matrix, col):
    col_sum = 0
    for row in range(len(matrix)):
            col_sum += matrix[row][col]
    return col_sum
def is_magic(square):
    rows_sum = sum(square[0])
    for row in square:
        row_sum = sum(row)
        if rows_sum != row_sum:
            return False
    for col in range(len(square)):
        col_sum = sum_col(square, col)
        if col_sum != rows_sum:
            return False
    diagonal_sum = 0
    for i in range(len(square)):
        diagonal_sum += square[i][i]
    if diagonal_sum != rows_sum:
        return False
    diagonal_sum = 0
    j = len(square) - 1
    for i in range(len(square)):
        diagonal_sum += square[i][j]
        j -= 1
    return diagonal_sum == rows_sum
    
def count_magic_squares(square, i,j):
    n = len(square)
    global magic_num
    if magic_num == 0:
        magic_num = (n**3 + n) / 2
    if i == n + 1:
        generated_squares.append(str(square))
        if is_magic(square):
            return 1 
        else: 
            return 0
    global missing_numbers
    if len(missing_numbers) == 0:
        missing_numbers = [num for num in range (1, n ** 2 + 1)]
    if j == n:
        total = 0
        for num in missing_numbers: 
            if num in present_numbers:
                continue
            if sum(square[i - 1]) > magic_num:
                return 0
            if sum_col(square, j - 1) > magic_num: 
                return 0
            square[i - 1][j - 1] = num
            present_numbers[num] = True
            total += count_magic_squares(square, i + 1, 1)
            del present_numbers[num]
            square[i - 1][j - 1] = 0
            missing_numbers[num - 1] = num
        return total 
    else: 
        total = 0
        for num in missing_numbers:
            if num in present_numbers:
                continue
            if sum(square[i - 1]) > magic_num:
                return 0
            if sum_col(square, j - 1) > magic_num: 
                return 0
            square[i - 1][j - 1] = num 
            present_numbers[num] = True
            total += count_magic_squares(square, i, j +1)
            del present_numbers[num]
            square[i - 1][j - 1] = 0
            missing_numbers[num - 1] = num
        return total 
# start_time = time.time()   
# print(count_magic_squares([[0 for _ in range(3)] for _ in range(3)], 1,1))
# print(time.time() - start_time)

#c 
# 1. **Definición del tamaño del problema**: Sea \(n\) el tamaño del problema, donde el número de opciones en cada paso es proporcional al cuadrado de \(n\), es decir, tenemos \(n^2\) opciones.

# 2. **Árbol de backtracking**: Cada nivel \(l\) del árbol (donde \(1 \leq l \leq n^2\)) representa el estado del problema después de tomar \(l\) decisiones, cada una de las cuales tiene \(n^2 - (l - 1)\) opciones.

# 3. **Número de nodos por nivel**: El número de nodos en el nivel \(l\) del árbol se calcula como el producto de todas las opciones disponibles hasta ese nivel, es decir, 
# \[n^2 \times (n^2 - 1) \times \cdots \times (n^2 - (l - 1)).\]

# 4. **Total de nodos en el árbol**: El total de nodos en el árbol de backtracking es la suma de los nodos en todos los niveles. Dado que estamos interesados en el peor caso (sin poda), el total de nodos es igual al número total de permutaciones de \(n^2\) opciones, que es \((n^2)!\).

# 5. **Demostración formal**:
#     - El primer nivel del árbol tiene \(n^2\) nodos.
#     - El segundo nivel del árbol tiene \(n^2 \times (n^2 - 1)\) nodos.
#     - ...
#     - El último nivel, \(n^2\), tiene \(n^2 \times (n^2 - 1) \times \cdots \times 1 = (n^2)!\) nodos.
   
#    Entonces, el número total de nodos \(N\) en el árbol de backtracking, sumando todos los niveles, satisface que \(N = (n^2)!\), demostrando que el árbol de backtracking tiene \(O((n^2)!)\) nodos en el peor caso.



#Ej 3
#a
from collections import deque
def total(matrix: list[list[int]], subset: list[int]):
    total: int = 0
    for i in subset:
        for j in subset:
            total += matrix[i - 1][j - 1]
    return total

current_max = [[], 0]
def maxi_subconjunto(matrix: list[list[int]], k: int, subset: list[int], i:int):
    if len(subset) == k:
        # print(subset)
        global current_max
        if total(matrix, subset) > current_max[1]:
            current_max[0] = subset.copy()
            current_max[1] = total(matrix, subset)
            return 
    elif i <= len(matrix):
        subset.append(i)
        maxi_subconjunto(matrix, k, subset, i + 1)
        subset.pop()
        maxi_subconjunto(matrix, k, subset, i + 1)

maxi_subconjunto([
    [0,10,10,1],
    [10,0,5,2],
    [10,5,0,1],
    [1,2,1,0]
    ], 3, [], 1)
print(current_max)
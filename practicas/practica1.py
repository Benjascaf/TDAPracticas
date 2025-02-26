import time 
import np
# Ej 1
#a) (Comsultar)
#Las soluciones candidatas serian aquellas tuplas de tres elementos cuyos valores pueden ser 1 o 0
#o, en otras palabras, todas las posibles permutaciones de tuplas de tres elementos dodede cada elemento puede tomar solo dos valores.
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

#Dictionary for fast lookup on whether or not a specific number is present
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
#a No me guista como lo implemente
def total(matrix: list[list[int]], subset: list[int]):
    total: int = 0
    for i in subset:
        for j in subset:
            total += matrix[i - 1][j - 1]
    return total

#Makin 2^n recursive calls
def maxi_subconjunto(matrix: list[list[int]], k: int, subset: list[int], i:int, current_max = [[], 0]):
    if len(subset) == k: #O(k)
        # print(subset)
        if total(matrix, subset) > current_max[1]: #O(k^2)
            current_max[0] = subset.copy()
            current_max[1] = total(matrix, subset)
            return current_max[0]
    elif i <= len(matrix): #O(n)
        subset.append(i)
        maxi_subconjunto(matrix, k, subset, i + 1)
        subset.pop()
        maxi_subconjunto(matrix, k, subset, i + 1)
        return current_max[0]

s = maxi_subconjunto([
    [0,10,10,1],
    [10,0,5,2],
    [10,5,1,1],
    [1,2,1,0]
    ], 2, [], 1)

# print("Prueba 1")
M = [ [3,1,2,4],
                    [1,4,3,5],
                    [2,3,5,6],
                    [4,5,6,6] ] # [1,2,3]

# print(maxi_subconjunto(M, 3, [], 1))


#b
#Si nom me quivoco, en pero caso se hacen un total de 2^n llamados recursivos, 
# cada uno con complejidad O(k)  + O(n) + O(k^2) (Este ultimo no estoy seguro pq solo lo haces en las hojas, como tengo esto en cuenta?)
#Luego, la complejidad quedaria O(2^n(k^2 + n))

#Noc como calcular complejidad espacial


#Ej 4 

def calculate_sum(matrix: list[list[int]], permutation: list[int]):
    n = len(matrix) - 1
    total = matrix[permutation[n] - 1][permutation[0] - 1]
    for i in range(n):
        total += matrix[permutation[i] - 1][permutation[i+1] - 1]
    return total

def replaceElements(original: list[any], replacement: list[any]):
    for i in range(len(original)):
        original[i] = replacement[i]
def rutaMinima(matrix: list[list[int]], curr_permutation: list[int], min_permutation: list[int], present_numbers: dict[int, bool], missing_numbers:list[bool]):
    n = len(matrix)
    if not missing_numbers:
        missing_numbers += [n for n in range(1, len(matrix) + 1)]
    if len(curr_permutation) == n:
        total = calculate_sum(matrix, curr_permutation)
        if total < calculate_sum(matrix, min_permutation):
            replaceElements(min_permutation, curr_permutation)
    else:
        for num in missing_numbers:
            if num not in present_numbers:
                present_numbers[num] = True 
                curr_permutation.append(num)
                rutaMinima(matrix, curr_permutation, min_permutation, present_numbers, missing_numbers)
                curr_permutation.pop()
                rutaMinima(matrix, curr_permutation, min_permutation, present_numbers, missing_numbers)
                del present_numbers[num]
min_permutation = [n for n in range (4,0, -1)]
# print(min_permutation)
# Ejemplo = np.array([[0, 1, 10, 10],
#                         [10, 0, 3, 15],
#                         [21, 17, 0, 2],
#                         [3, 22, 30, 0]]).T

# rutaMinima(Ejemplo, [], min_permutation, {}, [])
# print(min_permutation)

#Ej 5
#c
M = [[None for _ in range(0, 34 + 1)] for _ in range(0, 14 + 1)]

def ss_top(c, i, j):
    if j < 0:
        return False
        
    if i == 0:
        return j == 0
    elif not M[i][j]:
        M[i][j] = ss_top(c, i - 1, j) or ss_top(c, i - 1, j - c[i - 1])
    else:
        print(M[i][j])
    return M[i][j]
#f
M = []
def ss_bottom(c, k):
    global M
    if not M:
        M = [[None for _ in range(k+1)] for _ in range(len(c) + 1)]
        for col in range(k+1):
            M[0][col] = col == 0
    for i in range(1, len(c) + 1):
        for j in range(k  +1):
            print(i, j)
            if j >= c[i - 1]:
                M[i][j] = M[i-1][j] or M[i-1][j - c[i- 1]]
            else:
                M[i][j] = M[i-1][j]

#g Esta mal, noc xomo evitar tener siempre dos listas que representen la fila actual y la anterior
    #pq si uso solo uno modifico las posiciones lo que termina afectando calculos posteriores
    #Esto funca, pero no me convence
def ss_bottom_more_betterer(c, k):
    prev_row = [n == 0 for n in range (k+1)]
    # curr_row = [None for _ in range(k + 1)]
    for i in range(1, len(c) + 1):
        for j in range(k + 1):
            if j >= c[i - 1]:
                prev_row[j] = prev_row[j] or prev_row[j - c[i -1 ]]
            else:
                prev_row[j] = prev_row[j]
        # prev_row = curr_row.copy()
    return prev_row[j]

# print(ss_bottom_more_betterer([6,11,3, 5, 5, 5], 7))


#Ej 6 

#O(2^n) porque se realizan 2^n llamados recursivos y cada una cuesta O(1)
def min_cc(fst: list[int, int], snd:list[int, int]):
    if fst[0] == snd[0]:
        if fst[1] < snd[1]:
            return fst
        else: 
            return snd
    return fst if fst[0] < snd[0] else snd
def cc(B: list[int], i: int, j: int) -> list[int, int]:
    if j <= 0:
        return [0,0]
    elif i == 0:
        return [float("inf"), float("inf")]
    else:
        without_last =  cc(B, i - 1, j)
        with_last = cc(B, i - 1, j - B[i - 1])
        with_last[1] += 1
        with_last[0] += B[i - 1]
        return min_cc(without_last, with_last)
    

R = []
#e
#O(nc)? pq evito repeticion de estados?
def ccp(B: list[int], i: int, j: int) -> list[int, int]:
    global R
    if not R:
        R = [[None for _ in range(j + 1)] for _ in range(i + 1)]
    if j <= 0:
        return [0,0]
    elif i == 0:
        R[i][j] = [float("inf"), float("inf")]
    elif not R[i][j]:
        without_last =  cc(B, i - 1, j)
        with_last = cc(B, i - 1, j - B[i - 1])
        with_last[1] += 1
        with_last[0] += B[i - 1]
        R[i][j] =  min_cc(without_last, with_last)
    return R[i][j]


#f Anda pero no me gusta, pero tampoco se como hacer para usar solo una lista, 
# porque si lo hago asi tengo q cambio los valores de posiciones q puedo llegar a usar dsp
def ccp_bottom(B: list[int], i:int, j:int) -> list[int, int]:
    curr = [[float("inf"), float("inf")] for _ in range(j + 1)]
    prev = curr.copy()
    curr[0] = [0,0]
    for i in range(i, 0, -1):
        for j in range(1, j + 1):
            resta = j - B[i -1] if j >= B[i - 1] else 0
            fst = prev[j].copy()
            snd = prev[resta].copy()
            snd[0] += B[i - 1]
            snd[1] += 1
            curr[j] = min_cc(fst, snd)
        prev = curr.copy()
    return curr[j]

print(ccp_bottom([2, 3, 5, 10, 20, 20], 6, 14))

#g Ej de demostracion consultar


#ej 7
#Arranque asi para asegurarme que la idea este bien
#La complejidad seria 3^n?
def mgn(P: tuple[int], asteroid_amount:int , current_day: int):
    if asteroid_amount < 0 or asteroid_amount > current_day:
        return float("-inf")
    if current_day == 0:
        return 0
    else:
        return max(mgn(P, asteroid_amount + 1, current_day - 1) + P[current_day - 1], mgn(P, asteroid_amount - 1, current_day - 1) - P[current_day - 1], mgn(P, asteroid_amount, current_day - 1))

#La complejidad espacial y temproal seria n^2?
result = []
def mgn_pd_top(P: tuple[int], asteroid_amount:int , current_day: int):
    global result
    if not result:
        result = [[None for _ in range(current_day)] for 
              _ in range(current_day + 1)]
        result[0] = [0 for _ in range(current_day)]
    if asteroid_amount < 0 or asteroid_amount > current_day:
        return float("-inf")
    if current_day == 0:
        return 0
    if not result[current_day][asteroid_amount]:
        result[current_day][asteroid_amount] = max(mgn(P, asteroid_amount + 1, current_day - 1) + P[current_day - 1], mgn(P, asteroid_amount - 1, current_day - 1) - P[current_day - 1], mgn(P, asteroid_amount, current_day - 1))
    return result[current_day][asteroid_amount]

# print(mgn_pd_top((6,7), 0, 2))

#falta implemenat el bottom up


#Ej 8
#d)
ce_top_res = []
def ce_top(cuts, since, to):
    global ce_top_res
    if not ce_top_res:
        ce_top_res = [[None for _ in range(to)] for _ in range(to + 1)]
    if not ce_top_res[to][since]:
        cost = to - since 
        possible_costs = []
        for cut in cuts:
            if not (since < cut < to):
                continue
            possible_costs.append(ce_top(cuts, since, cut) + ce_top(cuts, cut, to))
        if possible_costs:
            ce_top_res[to][since] = cost + min(possible_costs)
        else:
            ce_top_res[to][since] = 0
    return ce_top_res[to][since]
    
print(ce_top((2,4,7), 0, 10))

# def ce_bottom(cuts, since, to):
#     for i in range()

#d) no entiendo



#9

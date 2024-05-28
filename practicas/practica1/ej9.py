minimos = []
def minVida(i,j, A):
    global minimos
    n = len(A)
    m = len(A[n - 1])
    if not minimos:
        minimos = [[None for _ in range(m)] for _ in range(n)]
    if i == n and j == m:
        return max(1, -A[i - 1][j - 1] + 1)
    if not minimos[i - 1][j - 1]:
        if j == m:
            minimos[i - 1][j - 1] = max(1, minVida(i + 1, j, A) - A[i-1][j-1])
        elif i == n:
            minimos[i - 1][j - 1] = max(1, minVida(i, j + 1, A) - A[i-1][j-1])
        else:
            minimos[i-1][j-1] = max(1, min(minVida(i+1, j,A), minVida(i, j + 1,A)) - A[i-1][j - 1])
    return minimos[i-1][j-1]

print(minVida(1,1, [[-2,-3,3], [-5, -10,1], [10,30, -5]]))
print(minimos)
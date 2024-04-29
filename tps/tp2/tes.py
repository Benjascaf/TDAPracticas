def longest_increasing_subsequence(heights, widths):
    n = len(heights)
    # Store solutions for each subproblem
    dp = [0] * n
    # Base case: the longest subsequence ending at each building initially has length of its own width
    for i in range(n):
        dp[i] = widths[i]

    # Build the DP table
    for i in range(n):
        for j in range(i):
            if heights[j] < heights[i]:
                dp[i] = max(dp[i], dp[j] + widths[i])

    return max(dp)

def longest_decreasing_subsequence(heights, widths):
    n = len(heights)
    dp = [0] * n
    for i in range(n):
        dp[i] = widths[i]

    for i in range(n):
        for j in range(i):
            if heights[j] > heights[i]:
                dp[i] = max(dp[i], dp[j] + widths[i])

    return max(dp)

def solution(building_heights, building_widths):
    length_increasing = longest_increasing_subsequence(building_heights, building_widths)
    length_decreasing = longest_decreasing_subsequence(building_heights, building_widths)

    if length_increasing >= length_decreasing:
        return f"Increasing ({length_increasing}). Decreasing ({length_decreasing})."
    else:
        return f"Decreasing ({length_decreasing}). Increasing ({length_increasing})."

import sys
input = sys.stdin.read
data = input().split()
index = 0

num_cases = int(data[index])
index += 1
output = []

for case in range(num_cases):
    building_quantity = int(data[index])
    index += 1
    building_heights = list(map(int, data[index:index+building_quantity]))
    index += building_quantity
    building_widths = list(map(int, data[index:index+building_quantity]))
    index += building_quantity

    res = solution(building_heights, building_widths)
    output.append(f"Case {case + 1}. {res}")

for o in output:
    print(o)

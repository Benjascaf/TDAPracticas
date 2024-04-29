def longest_increasing_subsequence(building_heights, building_lengths, curr_index, last_building_height, matrix=None):
    if not matrix:
        matrix = [[None for _ in range(max(building_heights) + 1)] for _ in range(len(building_lengths))]
    if curr_index == len(building_heights):
        return 0
    if not matrix[curr_index][last_building_height]:
        if building_heights[curr_index] <= last_building_height:
            matrix[curr_index][last_building_height] =  longest_increasing_subsequence(building_heights, building_lengths, curr_index + 1, last_building_height, matrix)
        else:
            matrix[curr_index][last_building_height] = max(longest_increasing_subsequence(building_heights, building_lengths, curr_index + 1, last_building_height, matrix), building_lengths[curr_index] + longest_increasing_subsequence(building_heights, building_lengths, curr_index + 1, max(last_building_height, building_heights[curr_index]), matrix))

    return matrix[curr_index][last_building_height]

def longest_decreasing_subsequence(building_heights, building_lengths, curr_index, last_building_height, matrix=None):
    if not matrix:
        matrix = [[None for _ in range(max(building_heights) + 1)] for _ in range(len(building_lengths))]
    if curr_index == -1:
        return 0
    if not matrix[curr_index][last_building_height]:
        if building_heights[curr_index] <= last_building_height:
            matrix[curr_index][last_building_height] =  longest_decreasing_subsequence(building_heights, building_lengths, curr_index - 1, last_building_height, matrix)
        else:
            matrix[curr_index][last_building_height] = max(longest_decreasing_subsequence(building_heights, building_lengths, curr_index - 1, last_building_height, matrix), building_lengths[curr_index] + longest_decreasing_subsequence(building_heights, building_lengths, curr_index - 1, building_heights[curr_index], matrix))
    return matrix[curr_index][last_building_height]

def solution(amount_of_buildings,building_heights, building_widths):
    building_widths = list(map(int, building_widths))
    building_heights = list(map(int, building_heights))
    length_increasing = longest_increasing_subsequence(building_heights, building_widths, 0,0)
    length_decreasing = longest_decreasing_subsequence(building_heights, building_widths, amount_of_buildings - 1, 0)
    
    if length_decreasing <= length_increasing:
        return "Increasing (" + str(length_increasing) + "). Decreasing (" + str(length_decreasing) + ")."
        
    else:
        return "Decreasing (" + str(length_decreasing) + "). Increasing (" + str(length_increasing) + ")."
if __name__ == "__main__":
    num_cases: int = input()      
    output: list[str] = []
    for case in range(int(num_cases)):
        building_quantity = int(input())
        building_heights = []
        building_widths = []
        i = 0
        while i < building_quantity:
            inputs = input().split()
            building_heights += inputs
            i += len(inputs)
        i = 0
        while i < building_quantity:
            inputs = input().split()
            building_widths += inputs
            i += len(inputs)
        res = solution(building_quantity,building_heights, building_widths)
        output.append(f"Case {case + 1}. " + res)
    for o in output:
        print(o)

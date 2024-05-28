def jj(trees, lostHeight, t, h):
    solution = [[0 for _ in range(t)] for _ in range(h)]
    for tree in range(t):
        solution[0][tree] = trees[tree][0]
    for height in range(1, h):
        for tree in range(t):
            if height < lostHeight:
                solution[height][tree] = trees[tree][height] + solution[height - 1][tree]
            else:
                mostAcorns = 0
                for otherTrees in range(t):
                    otherTreesAcorns = solution[height - f][otherTrees]
                    if otherTreesAcorns > mostAcorns:
                        mostAcorns = otherTreesAcorns
                
                solution[height][tree] = trees[tree][height] + max(solution[height - 1][tree], mostAcorns)
    maxAcorns = 0
    for tree in range(t):
        if solution[h - 1][tree] > maxAcorns:
            maxAcorns = solution[h - 1][tree]
    return maxAcorns

if __name__ == "__main__":
    numCases: int = int(input())
    results: list[str] = []
    for case in range(numCases):
        t, h, f = input().split()
        t = int(t)
        h = int(h)
        f = int(f)
        trees = [[0 for _ in range(h)] for _ in range(t)]
        for tree in range(t):
            acornLocations = input().split()
            for acorn in acornLocations[1:]:
                trees[tree][int(acorn) - 1] += 1
        results.append(jj(trees, f, t,h))
    input()
    for result in results:
        print(result)
        
            
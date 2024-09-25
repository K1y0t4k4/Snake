from typing import List

def color(begin: List[int], end: List[int], count: int) -> List[int]:
    if count < 2:
        return []
    
    c = []
    steps = [(end[i] - begin[i]) / (count - 1) for i in range(3)]
    for color_index in range(count):
        c.append([int(begin[i] + steps[i] * color_index) for i in range(3)])

    return c
c = color([200, 0, 0], [0, 0, 200], 8)

for i in range(len(c)):
    print(f"\033[38;2;{c[i][0]};{c[i][1]};{c[i][2]}mhello\033[0m")

for i in range(len(c)):
    print(f"{c[i][0]};{c[i][1]};{c[i][2]}")

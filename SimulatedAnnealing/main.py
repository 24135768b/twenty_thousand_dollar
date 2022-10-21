from math import e
from tqdm import trange
import numpy as np

# ---- Setting ----
DEV = False
T = 1
Rt = 0.95
Iter = 2000
Round = 100
N = 4 if DEV else 101
TestCase = "../test.in" if DEV else "../input.txt"
Threshold = 720

# ---- Variable ----
wij = np.zeros((N+1, N+1))


# ---- Function ----
def mapping(n):
    return 2*n-1


def calcE(result):
    size = len(result)
    sum = 0
    for i in range(1, size):
        for j in range(i+1, size):
            sum += wij[i, j]*mapping(result[i])*mapping(result[j])
    return sum


result = np.zeros(N+1)  # will be 0 or 1 array
nowE = calcE(result)


with open(TestCase) as f:
    lines = f.readlines()
    for line in lines:
        line = line.replace("\t", " ").replace(
            "  ", " ").replace("\n", "").lstrip()
        i, j, w = line.split(" ")[:3]
        i = int(i)
        j = int(j)
        wij[i, j] = float(w)
        wij[j, i] = float(w)

for x in range(Round):
    print(f"Round: {x}")
    # Init
    result = np.zeros(N+1)  # will be 0 or 1 array
    nowE = calcE(result)

    t = trange(Iter, ascii=True)
    for it in t:
        size = len(result)
        newResult = np.array(result)

        index = np.random.randint(1, size)
        newResult[index] = -1*(newResult[index]-1)  # 1 to 0, 0 to -1

        newE = calcE(newResult)
        delta = newE-nowE
        if delta <= 0:
            r = np.random.random()
            if r <= np.exp((delta/T)):
                nowE = newE
                result = newResult
        else:
            nowE = newE
            result = newResult
        # 降溫
        T = T*Rt
        # print(result)
        t.set_description(f"Round:{x}  E = {nowE}")
        t.refresh()  # to show immediately the update
    print(nowE)
    if nowE > Threshold:
        print(result)

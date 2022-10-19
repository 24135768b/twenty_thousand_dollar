import pandas as pd
import numpy as np

df = pd.read_csv("101.csv")
df.rename(columns={'Unnamed: 0': 'f','Unnamed: 1': 's','Unnamed: 2': 'w'}, inplace=True)


def count_weight(arr):
    sum = 0
    for i in range(len(arr)):
      for j in range(i+1, len(arr)):
          if(arr[i] == arr[j]):
              pn = 1
          else:
              pn = -1
          sum += pn*((df[(df["f"]==i+1) & (df["s"]==j+1)]['w']).values)
    
    return sum

max_e = 0
tmp_ans = np.random.randint(2,size=101)
while True :

    ans = np.random.randint(2,size=101)
    tmp = count_weight(ans)
            
    if(tmp > max_e):
        max_e = tmp
        tmp_ans = ans
        print(max_e)
        f = open("result.txt", "a")
        f.write(' '.join(str(e) for e in ans) + "\n")
        
        

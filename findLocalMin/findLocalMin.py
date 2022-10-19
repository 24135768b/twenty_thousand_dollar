import pandas as pd
import numpy as np

df = pd.read_csv("relation_matrix.csv")
df.rename(columns={'Unnamed: 0': 'f','Unnamed: 1': 's','Unnamed: 2': 'w'}, inplace=True)


def calculate_weight(arr):
    sum = 0
    for i in range(len(arr)):
      for j in range(i+1, len(arr)):
          if(arr[i] == arr[j]):
              pn = 1
          else:
              pn = -1
          sum += pn*((df[(df["f"]==i+1) & (df["s"]==j+1)]['w']).values)
    
    return sum



groupInput = input()
groupArr = [int(i) for i in groupInput.split(" ")]
print(groupArr)
print(calculate_weight(groupArr))

maxWeight = 643.7063
while True:
    # For each student, calculate the value of after sent to the other group. 
    for i in range(101):
        temp = groupArr[i] # store initial groupArr[i] value
        groupArr[i] = (groupArr[i] + 1) % 2 # swap to the other group
        currentValue = calculate_weight(groupArr)
        # swap if higher 
        if  currentValue > maxWeight :
            maxWeight = currentValue
            print(groupArr)
            print(maxWeight)
        else :
            groupArr[i] = temp # remain the same if not higher
    


    
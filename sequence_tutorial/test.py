import numpy as np
from collections import Counter

li =np.array([[1,-12,-15],
              [2,22,-12],
              [3,-4,11],
              [4,5,7],
              [2,13,-12],
              [1,-44,-23],
              [2,31,-24],
              [3,-6,7]])

a1 = li[:,0]
a3 = li[:,1]
print(a3)

count=Counter(a1)
print(count)
print(count.most_common(1)[0][0])

row_sum = np.sum(li, axis=0)
print(row_sum)

col_sum = np.sum(li, axis=1)
print(col_sum)

x=np.average(li[np.where(li[:,0]==count.most_common(1)[0][0]),1])
print(x)
y=np.average(li[np.where(li[:,0]==count.most_common(1)[0][0]),2])
print(y)

"""
TorF = list(map(lambda x:x==count.most_common(1)[0][0], li[:,0]))
print(TorF)

raw_sum = list(filter(lambda x:x==count.most_common(1)[0][0], li[:,0]))
print(raw_sum)
"""

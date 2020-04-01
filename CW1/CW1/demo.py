import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np
# with open("log.txt") as f:
#     for line in f.readlines():
#         print line

a = np.loadtxt("log.txt")
b = 0
c = 1
ave = []
best = []
tmp = []
print(len(a))
for i in range(0, len(a)):
    #print(a[i])
    b = b + a[i]
    c = c + 1
    if(c % 30 == 0):
        b = b / 30
        ave.append(b)
        #print(b)
        b = 0
        c = 0
# for i in range(0, len(ave)):
#     print(ave[i])
c = 0
for i in range(0, len(a)):
    c = c + 1
    tmp.append(a[i])
    if(c % 30 == 0):
        bestEpoch = np.max(tmp)
        best.append(bestEpoch)
        #print(bestEpoch)
        tmp = []
        c = 0
# for i in range(0, len(best)):
#     print(best[i])
plt.xlabel("epoch")
plt.ylabel("fitness")

l1, = plt.plot(ave, color = 'red', linestyle = '-', label = "ave")
l2, = plt.plot(best, color = 'green', linestyle = '-', label = "best")
plt.plot(ave, best, linewidth = 2)
plt.legend(loc = 'upper right')
#plt.plot(ave)
plt.title("Q1", fontsize = 10)
plt.savefig("ccc")

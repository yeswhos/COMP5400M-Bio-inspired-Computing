import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

a = np.loadtxt("pred.txt")
best = []
ave = []
tmp = np.zeros(30)
c = -1
total = 0
for i in range(0, len(a)):
    if((i % 149 == 0) & (i != 0)):
        maximum = max(tmp) / 5
        best.append(maximum)
        for i in range(0, 30):
            total = total + tmp[i]
        average = total / 30 / 5
        ave.append(average)
        c = -1
        tmp = np.zeros(30)
        total = 0

    c = c + 1
    tmp[c] = tmp[c] + a[i]
    if(c == 29):
        c = -1
    

# for i in range(0, len(best)):
#     #print(best[i])
# for i in range(0, len(ave)):
#     #print(ave[i])


plt.xlabel("epoch")
plt.ylabel("fitness")

l1, = plt.plot(ave, color = 'red', linestyle = '-', label = "average fitness")
l2, = plt.plot(best, color = 'green', linestyle = '-', label = "best fitness")
#l3, = plt.plot(distance, color = 'blue', linestyle = '-', label = "distance")
plt.plot(ave, best, linewidth = 0.5)
plt.legend(loc = 'upper right')
#plt.plot(ave)
plt.title("Q5 Predator agent", fontsize = 10)
#plt.xlim(0, 610)
plt.savefig("1000 epoch pred")

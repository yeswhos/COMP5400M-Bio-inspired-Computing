import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

a = np.loadtxt("ZumoQueen.txt")
best = []
ave = []
tmp = np.zeros(5)
c = -1
total = 0
for i in range(0, len(a)):
    if((i % 4 == 0) & (i != 0)):
        maximum = max(tmp) / 1
        #maximum = 1 / maximum 
        best.append(maximum)
        for i in range(0, 5):
            total = total + tmp[i]
        average = total / 5 / 1
        #average = 1 / average
        ave.append(average)
        c = -1
        tmp = np.zeros(5)
        total = 0

    c = c + 1
    tmp[c] = tmp[c] + (1 / a[i])
    if(c == 4):
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
plt.title("Q5 prey agent", fontsize = 10)
#plt.xlim(0, 610)
plt.savefig("1000 epoch prey")

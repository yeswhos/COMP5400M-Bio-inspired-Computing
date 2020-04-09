import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np
# with open("log.txt") as f:
#     for line in f.readlines():
#         print line

a = np.loadtxt("total.txt")
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
        print(b)
        ave.append(b)
        #print(b)
        b = 0
        c = 0

a = np.loadtxt("totalOrigin.txt")
b = 0
c = 1

best = []
tmp = []
print(len(a))
for i in range(0, len(a)):
    #print(a[i])
    b = b + a[i]
    c = c + 1
    if(c % 30 == 0):
        print(b)
        best.append(b)
        #print(b)
        b = 0
        c = 0


plt.xlabel("epoch")
plt.ylabel("total")

l1, = plt.plot(ave, color = 'red', linestyle = '-', label = "cheese eaten priority")
l2, = plt.plot(best, color = 'green', linestyle = '-', label = "origin")
#l3, = plt.plot(distance, color = 'blue', linestyle = '-', label = "distance")
plt.plot(ave, best, linewidth = 0.5)
plt.legend(loc = 'upper right')
#plt.plot(ave)
plt.title("Q4 with proximity sensors", fontsize = 5)
plt.xlim(0, 610)
plt.savefig("111")

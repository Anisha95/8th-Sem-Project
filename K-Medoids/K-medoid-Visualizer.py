import numpy as np
import matplotlib.pyplot as plt
import csv
import random


def generate_color():
    a = hex(random.randrange(3, 255))
    b = hex(random.randrange(3, 255))
    c = hex(random.randrange(3, 255))
    a = a[2:]
    b = b[2:]
    c = c[2:]
    if len(a) < 2:
        a = "0" + a
    if len(b) < 2:
        b = "0" + b
    if len(c) < 2:
        c = "0" + c
    z = a + b + c
    return "#" + z.upper()


filename = input("Enter the filename(with extension)..\n")
with open(filename, 'rU') as p:
    my_list = list(list(rec) for rec in csv.reader(p, delimiter=','))

k = int(input("Enter the number of clusters :\n"))

wm = plt.get_current_fig_manager()
wm.window.state('zoomed')


plt.suptitle("K-Medoids Visualizer Off-line")
plt.subplot(3, 1, 1)
plt.title("Before Clustering")
for i in my_list:
    plt.plot(i[0], i[1], 'red', marker='o')
plt.show(block=False)

plt.subplot(3, 1, 3)
plt.title(r"After clustering")

for i in range(0, k):
    clr = generate_color()
    x = str(i)
    x += ".csv"
    with open(x, 'rU') as p:
        my_list = list(list(rec) for rec in csv.reader(p, delimiter=','))
        for j in my_list:
            lbl = "cluster " + str(i+1)
            plt.plot(j[0], j[1], clr, marker='o', linestyle='-', linewidth=0.)

with open("out_medoid.csv", 'rU') as p:
    my_list = list(list(rec) for rec in csv.reader(p, delimiter=','))
for i in my_list:
    plt.plot(i[0], i[1], 'black', marker='x')

plt.savefig("fig1.png")
plt.show()

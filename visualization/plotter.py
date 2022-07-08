import matplotlib.pyplot as plt
import numpy as np
#from os import listdir
import os

def plotDerived():
    datapath = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + "/simFiles/derived/"
    files = os.listdir(datapath)
    for file in files:
            data = np.genfromtxt(datapath + file, delimiter=',')
            plt.rcParams['text.usetex'] = True
            fig, ax = plt.subplots(figsize=(6,4), tight_layout=True)
            ax.plot(data)
            ax.set_xlabel("Time")
            ax.set_ylabel("Magnetization")
            ax.grid()
            plt.savefig(file[0:-4] + '.png', dpi = 200, bbox_inches='tight')
            plt.close()

datapath = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + "/simFiles/data/"
files = os.listdir(datapath)
print("Starting figure creation. This might take a while...")
plotDerived();
for file in files:
    data = np.genfromtxt(datapath + file, delimiter=',')
    plt.rcParams['text.usetex'] = True
    fig, ax = plt.subplots(figsize=(6,4), tight_layout=True)
    ax.imshow(data)
#    ax.set_title("Timestep: " + file[11:-4])
    plt.axis('off')
    plt.savefig("figures/" + file[0:-4] + '.png', dpi = 200, bbox_inches='tight')
    plt.close()


print("Figures done.")

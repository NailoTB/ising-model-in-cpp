import matplotlib.pyplot as plt
import numpy as np
#from os import listdir
import os

def plotRawData():
    datapath = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + "/data/"
    files = os.listdir(datapath)

    for file in files:
        data = np.genfromtxt(datapath + file, delimiter=',')
        plt.rcParams['text.usetex'] = True
        fig, ax = plt.subplots(figsize=(6,4), tight_layout=True)
        ax.imshow(data)
        #    ax.set_title("Timestep: " + file[11:-4])
        plt.axis('off')
        plt.savefig("../figures/" + file[0:-4] + '.png', dpi = 200, bbox_inches='tight')
        plt.close()

def plotDerived():
    datapath = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + "/derived/"
    files = os.listdir(datapath)
    for file in files:
            data = np.genfromtxt(datapath + file, delimiter=',')
            plt.rcParams['text.usetex'] = True
            fig, ax = plt.subplots(figsize=(6,4), tight_layout=True)
            ax.plot(tempSpace, data)
            ax.set_xlabel("T")
            ax.set_ylabel("Magnetization")
            ax.set_ylim((-0.01, 1.01))
            plt.axvline(x = 2.27, color = 'r', ls='--')
            ax.grid()
            plt.savefig(file[0:-4] + '.png', dpi = 200, bbox_inches='tight')
            plt.close()


print("Starting figure creation. This might take a while...")
tempSpace = np.linspace(0.015, 200*0.015, 200)
plotDerived()
plotRawData()

print("Figures done.")

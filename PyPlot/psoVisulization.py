from pathlib import Path
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize
import pandas as pd


df = pd.read_csv("../particleCords.txt", low_memory=False)
#print(df)
particleNum = df[(df['particle'] == '0')]

#print(particleNum.head())

numParticles = 0
temp = "0"

#while df.iterrows() != temp:

for index, row in df.iterrows():
    if row['particle'] == temp:
        numParticles += 1
        while

##########################################################

# xCordsNotCalculated = []
# yCordsNotCalculated= []
# zCordsNotCalculated = []
#
# xCordsCalculated = []
# yCordsCalculated= []
# zCordsCalculated = []
#
# path = Path('/home/charli/CLionProjects/pso/particleCords.txt')
# content = path.read_text()
# content = content.rstrip()
# lines = content.splitlines()
#
# afterCalc = "After Calculations:"
# for line in lines:
#    if afterCalc in line:
#       continue
#    parts = line.split('|')
#    xCordsCalculated.append(float(parts[0].strip()))
#    yCordsCalculated.append(float(parts[1].strip()))
#    zCordsCalculated.append(float(parts[2].strip()))
#
# plt.style.use('seaborn-v0_8')
# fig, ax = plt.subplots()
# ax.scatter(xCordsCalculated, yCordsCalculated, color='red', marker='o', s=50)
# ax.set_xlim(-1, 1)
# ax.set_ylim(-1, 1)
#
# plt.show()
# print(xCordsCalculated)
# print(yCordsCalculated)
# print(zCordsCalculated)

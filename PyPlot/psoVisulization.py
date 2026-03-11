import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.animation import FuncAnimation
import numpy as np
import pandas as pd

df = pd.read_csv("../particleCords.txt")
df.columns = df.columns.str.strip()

plt.style.use('seaborn-v0_8')
fig, ax = plt.subplots()
ax.set_title("Particles")
ax.set_xlim(-1, 1)
ax.set_ylim(-1, 1)
groups = df.groupby("iter")
iterations = sorted(groups.groups.keys())

def contourFunction(x, y):
    return (x - 0.4)**2 + (y - 0.6)**2 - 0.4

xLayout = np.linspace(-1, 1, 200)
yLayout = np.linspace(-1, 1, 200)
X, Y = np.meshgrid(xLayout, yLayout)

Z = contourFunction(X, Y)
contourFuncmap = cm.plasma
contourDraw = ax.contourf(X, Y, Z, levels=50, cmap=contourFuncmap, alpha=0.5)

cbar = plt.colorbar(contourDraw, ax=ax, fraction=0.046, pad=0.04)
cbar.set_label("Terrain")
cbar.set_ticks([Z.min(), Z.max()])
cbar.set_ticklabels(['-', '+'])

globalbest = None
scatter = None

def video(frame):
    particle = groups.get_group(iterations[frame])
    x = particle["x"].to_numpy()
    y = particle["y"].to_numpy()

    partileMin = particle.loc[particle["z"].idxmin()]
    xBest = partileMin["x"]
    yBest = partileMin["y"]

    coords = np.column_stack((x, y))
    scatter.set_offsets(coords)

    globalbest.set_offsets([[xBest, yBest]])
    return scatter, globalbest

Z = contourFunction(X, Y)
ax.contourf(X, Y, Z, levels=50, cmap='plasma', alpha=0.5)

scatter = ax.scatter([], [], color='darkorange', s=40)
globalbest = ax.scatter([], [], color='gold', marker='*', s=140)
animation = FuncAnimation(fig, video, frames=len(iterations), interval=0.001, blit=True)

plt.show()

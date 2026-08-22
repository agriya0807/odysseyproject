import csv
import matplotlib
import matplotlib.animation as animation

# Force Matplotlib to open an external interactive pop-up window
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt


def getfile():
    return r"C:\Users\Agriya Bhattacharya\Downloads\Depth Data.csv"


# Getting data from file
def getdata(path):
    time = []
    depth = []
    last_depth = None

    with open(path, newline="") as csvfile:
        reader = csv.reader(csvfile)
        next(reader)

        for row in reader:
            time.append(float(row[0]))

            try:
                d = abs(float(row[1]))
            except ValueError:
                d = None

            if d is None or (last_depth is not None and abs(d - last_depth) > 80):
                d = last_depth if last_depth is not None else 0.0

            depth.append(d)
            last_depth = d

    return time, depth


def smooth_data(udata):
    clean_data = []
    for i in range(len(udata)):
        neighbors = [udata[i]]
        if i > 0:
            neighbors.append(udata[i - 1])
        if i < len(udata) - 1:
            neighbors.append(udata[i + 1])
        clean_data.append(sum(neighbors) / len(neighbors))
    return clean_data


# Graphing
def animate_data(times, raw_depths, clean_depths):
    fig, ax = plt.subplots()

    ax.set_title("Sea Floor Depth Profile")
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Depth (m)")
    ax.grid(True)

    raw_line, = ax.plot([], [], color="red", alpha=0.5, label="Raw Depth")
    clean_line, = ax.plot([], [], color="blue", linewidth=2, label="Clean Depth")
    ax.legend()

    ax.set_xlim(0, max(times))
    ax.set_ylim(max(raw_depths) + 20, 0)

    def update_graph(frame):
        raw_line.set_data(times[:frame], raw_depths[:frame])
        clean_line.set_data(times[:frame], clean_depths[:frame])
        return raw_line, clean_line

    ani = animation.FuncAnimation(
        fig, update_graph, frames=range(1, len(times) + 1), interval=10, repeat=False
    )

    plt.tight_layout()
    plt.show()
    return ani



path = getfile()
times, raw_depths = getdata(path)
clean_depths = smooth_data(raw_depths)
ani = animate_data(times, raw_depths, clean_depths)


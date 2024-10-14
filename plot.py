import pandas as pd
import matplotlib.pyplot as plt

# Read data from CSV file
data = pd.read_csv('result.csv')

# Filter data for first 100 rows except header
data_get_1 = data.iloc[1:99, :]

# Filter data for next 100 rows except header
data_get_2 = data.iloc[101:199, :]

# Filter data for next 100 rows except header
data_get_3 = data.iloc[201:299, :]

# Function to plot graphs
def plot_graphs(x, y, title, xlabel, ylabel, ax, i, j):
    ax[i][j].plot(x, y)
    ax[i][j].set_title(title)
    ax[i][j].set_xlabel(xlabel)
    ax[i][j].set_ylabel(ylabel)
    ax[i][j].grid()

# If num_server = 1
if not data_get_1.empty:
    fig, ax = plt.subplots(nrows = 2, ncols = 2, figsize = (10, 20))
    plot_graphs(data_get_1['buffer_size'], data_get_1['num_dropped'], 'Buffer Size vs Num Dropped', 'Buffer Size', 'Num Dropped', ax, 0, 0)
    plot_graphs(data_get_1['buffer_size'], data_get_1['avg_wait_time'], 'Buffer Size vs Avg Wait Time', 'Buffer Size', 'Avg Wait Time', ax, 0, 1)
    plot_graphs(data_get_1['buffer_size'], data_get_1['server_util'], 'Buffer Size vs Server Utilization', 'Buffer Size', 'Server Utilization', ax, 1, 0)
    plot_graphs(data_get_1['buffer_size'], data_get_1['avg_queue_length'], 'Buffer Size vs Avg Queue Length', 'Buffer Size', 'Avg Queue Length', ax, 1, 1)
    plt.show()

# If num_server > 1
if not data_get_2.empty:
    fig, ax = plt.subplots(nrows = 4, ncols = 2, figsize = (15, 25))

    plot_graphs(data_get_3['buffer_size'], data_get_3['num_dropped'], 'Buffer Size vs Num Dropped (Num Servers Constant)', 'Buffer Size', 'Num Dropped', ax, 0, 0)
    plot_graphs(data_get_2['num_server'], data_get_2['num_dropped'], 'Num Servers vs Num Dropped (Buffer Size Constant)', 'Num Servers', 'Num Dropped', ax, 0, 1)

    plot_graphs(data_get_3['buffer_size'], data_get_3['avg_wait_time'], 'Buffer Size vs Avg Wait Time (Num Servers Constant)', 'Buffer Size', 'Avg Wait Time', ax, 1, 0)
    plot_graphs(data_get_2['num_server'], data_get_2['avg_wait_time'], 'Num Servers vs Avg Wait Time (Buffer Size Constant)', 'Num Servers', 'Avg Wait Time', ax, 1, 1)

    plot_graphs(data_get_3['buffer_size'], data_get_3['server_util'], 'Buffer Size vs Server Utilization (Num Servers Constant)', 'Buffer Size', 'Server Utilization', ax, 2, 0)
    plot_graphs(data_get_2['num_server'], data_get_2['server_util'], 'Num Servers vs Server Utilization (Buffer Size Constant)', 'Num Servers', 'Server Utilization', ax, 2, 1)

    plot_graphs(data_get_3['buffer_size'], data_get_3['avg_queue_length'], 'Buffer Size vs Avg Queue Length (Num Servers Constant)', 'Buffer Size', 'Avg Queue Length', ax, 3, 0)
    plot_graphs(data_get_2['num_server'], data_get_2['avg_queue_length'], 'Num Servers vs Avg Queue Length (Buffer Size Constant)', 'Num Servers', 'Avg Queue Length', ax, 3, 1)
    plt.show()
# Airport Security Queue Simulation

## Overview

This project simulates an airport security queue system using a discrete-event simulation model. The aim is to optimize the efficiency of airport security screening processes by adjusting various system parameters like the number of servers, buffer size, arrival rate (λ), and service rate (μ). The simulation outputs metrics such as average wait time, average queue length, and server utilization, helping to determine the optimal configuration for the security system.

## Key Features

- **Single and Multi-Server Simulation**: The system supports both single-server and multiple-server configurations, allowing comparison of different setups.
- **Buffer Size Optimization**: Simulates scenarios with varying buffer sizes to assess the effect on packet drop rates and server utilization.
- **Performance Metrics**: Calculates key metrics like average waiting time, queue length, and server utilization.
- **Exponential Distribution**: Passenger arrivals and service times follow an exponential distribution, providing a realistic model for the simulation.

## Simulation Parameters

- **Number of Passengers (n)**: The total number of passengers processed in the simulation. (Default: 100,000)
- **Number of Servers (s)**: The number of security servers in the simulation. Varies between single and multi-server configurations.
- **Buffer Size (b)**: The size of the buffer to hold incoming passengers before they are processed.
- **Arrival Rate (λ)**: The rate at which passengers arrive at the security checkpoint.
- **Service Rate (μ)**: The rate at which passengers are processed by the security servers.

## Output

The simulation results are written to `result.csv` with the following metrics:

- `population_size`: The number of passengers processed.
- `num_server`: The number of servers used in the simulation.
- `buffer_size`: The buffer size for each server.
- `lambda`: The arrival rate.
- `mu`: The service rate.
- `num_dropped`: The number of packets (passengers) dropped due to insufficient buffer space.
- `avg_wait_time`: The average waiting time for passengers.
- `avg_queue_length`: The average queue length during the simulation.
- `server_util`: The server utilization percentage.

## How to Run

1. **Compilation**:
   Compile the C++ file using a C++ compiler:

   ```bash
   g++ main.cpp -o queue_simulation
   ```

2. **Execution**:
   Run the compiled program:

   ```bash
   ./queue_simulation
   ```

   This will simulate various scenarios with different numbers of servers and buffer sizes, writing the results to `result.csv`.

## Example Usage

The program runs three sets of simulations:

- **Single Server, Variable Buffer**: For a single server, the buffer size is varied from 1 to 100.
- **Multiple Servers, Fixed Buffer**: For a fixed buffer size, the number of servers is varied from 1 to 100.
- **Two Servers, Variable Buffer**: With two servers, the buffer size is varied from 1 to 100.

The results are stored in the CSV file, which can then be analyzed to determine the optimal configuration.

## Dependencies

- C++11 or higher.
- Standard Template Library (STL).

## Report

For more detailed analysis and simulation results, refer to the report that accompanies this project, which discusses optimization strategies like buffer size and multi-server configurations.
import re

# Define a function to parse ping output and calculate the average queue delay
def calculate_average_queue_delay(input_file, output_file):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Extract round-trip times and convert to float
    delays = [float(line.split()[-2].replace('time=', '')) for line in lines if 'time=' in line]

    min_delay = min(delays)
    queue_delays = [delay - min_delay for delay in delays]
    average_queue_delay = sum(queue_delays) / len(queue_delays) if queue_delays else 0

    # Write the average queue delay to the output file
    with open(output_file, 'w') as file:
        file.write(f"Average Queue Delay: {average_queue_delay} ms\n")

    return average_queue_delay

# Paths to the input and output files
input_file_path = 'ping_output.txt'
output_file_path = 'average_queue_delay.txt'

# Calculate the average queue delay and write it to a file
average_queue_delay = calculate_average_queue_delay(input_file_path, output_file_path)
print(f"Average Queue Delay has been calculated and written to {output_file_path}: {average_queue_delay} ms")

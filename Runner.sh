#!/bin/bash

# Folders containing C++ files
FOLDER1="Gemini"
FOLDER2="ChatGPT"
FOLDER3="Serial"

# Output log file
LOG_FILE="execution_log.txt"

# Gather system information
RAM=$(free -h | grep Mem | awk '{print $2}')
CPU=$(lscpu | grep "Model name" | awk -F: '{print $2}' | xargs)
THREADS=$(nproc)

# Write system info into log file
echo "System Information:" > $LOG_FILE
echo "RAM: $RAM" >> $LOG_FILE
echo "CPU: $CPU" >> $LOG_FILE
echo "Threads: $THREADS" >> $LOG_FILE
echo "" >> $LOG_FILE

# Function to compile and execute a C++ file and log the time
run_cpp() {
    CPP_FILE=$1
    MODE=$2
    
    # Compile the file
    if [ "$MODE" == "omp" ]; then
        g++ -fopenmp -o output "$CPP_FILE"
    else
        g++ -o output "$CPP_FILE"
    fi
    
    # Check if the compilation was successful
    if [ $? -eq 0 ]; then
        # Measure execution time and log it
        echo "Running $CPP_FILE" >> $LOG_FILE
        START=$(date +%s.%N)
        ./output
        END=$(date +%s.%N)
        DIFF=$(echo "$END - $START" | bc)
        echo "Execution time: $DIFF seconds" >> $LOG_FILE
        echo "" >> $LOG_FILE
    else
        echo "Failed to compile $CPP_FILE" >> $LOG_FILE
        echo "" >> $LOG_FILE
    fi
    
    # Clean up
    rm -f output
}

# Run C++ files in the first folder without OpenMP
for file in "$FOLDER1"/*.cpp; do
    run_cpp "$file" "no-omp"
done

# Run C++ files in the second folder with OpenMP
for file in "$FOLDER2"/*.cpp; do
    run_cpp "$file" "omp"
done

# Run C++ files in the third folder with OpenMP
for file in "$FOLDER3"/*.cpp; do
    run_cpp "$file" "omp"
done

echo "All files executed. Check $LOG_FILE for details."

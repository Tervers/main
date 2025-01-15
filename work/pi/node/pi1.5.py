import serial
import RPi.GPIO as GPIO
import time
import os
import _thread
import threading
from datetime import datetime
from queue import Queue

# Setup UART
uart = serial.Serial('/dev/serial0', baudrate=9600, timeout=2)
de_re = 18
uart_lock = threading.Lock()

# Setup GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(de_re, GPIO.OUT)

# Setup Relay Channels
Relay_Ch1 = 26
Relay_Ch2 = 20
Relay_Ch3 = 21
GPIO.setup(Relay_Ch1, GPIO.OUT)
GPIO.setup(Relay_Ch2, GPIO.OUT)
GPIO.setup(Relay_Ch3, GPIO.OUT)
print("Relay module connected!")

# UART Functions
def enable_tx():
    GPIO.output(de_re, GPIO.HIGH)

def enable_rx():
    GPIO.output(de_re, GPIO.LOW)

# Request temps from Pico
def request_temperatures():
    enable_tx()
    uart.write(b"R")   # Send IRQ signal ('R' for Request)
    time.sleep(0.01)
    enable_rx()

# Parse temperature data
def parse_temperatures(data):
    try:
        temp1, temp2, temp3 = map(int, data.split(","))
        return temp1, temp2, temp3
    except ValueError:
        return None, None, None

# Temperature logging
def log_temperatures(temp1, temp2, temp3):
    print(f"Log function called with: temp1={temp1}, temp2={temp2}, temp3={temp3}")
    base_dir = "/home/tervs/Temperatures/"
    date_str = datetime.now().strftime("%Y-%m-%d")
    month_year_dir = os.path.join(base_dir, datetime.now().strftime("%Y-%m"))
    log_file_path = os.path.join(month_year_dir, f"{date_str}.csv")
    
    try:
        print(f"Creating directory: {month_year_dir}")
        os.makedirs(month_year_dir, exist_ok=True)
        print(f"Writing to log file: {log_file_path}")
        with open(log_file_path, "a") as log_file:
            timestamp = datetime.now().strftime("%H:%M:%S")
            log_file.write(f"{timestamp},{temp1},{temp2},{temp3}\n")
    except Exception as e:
        print(f"Error while logging temperatures: {e}")

# Control relays
def control_relays(temp1, temp2, temp3):
    #Startup Logic
    GPIO.output(Relay_Ch1, GPIO.HIGH)
    GPIO.output(Relay_Ch2, GPIO.HIGH)
    GPIO.output(Relay_Ch3, GPIO.HIGH)

    #Relay Channel 1 Logic
    
    # Relay Channel 2 Logic
    if temp2 < 33 or temp2 > 180:
        GPIO.output(Relay_Ch2, GPIO.HIGH)
    else:
        GPIO.output(Relay_Ch2, GPIO.LOW)  # LED ON when GPIO.LOW
        
    # Relay Channel 3 Logic
    if temp3 < 40 or temp3 > 45:
        GPIO.output(Relay_Ch3, GPIO.HIGH)
    else:
        GPIO.output(Relay_Ch3, GPIO.LOW)  # LED ON when GPIO.LOW

# Shared Queue for Logging and Relay Threads
data_queue = Queue()

# Dedicated UART Reader Thread
def uart_reader_thread():
    while True:
        try:
            with uart_lock:
                raw_data = uart.readline()
                if raw_data:
                    data = raw_data.decode("utf-8", errors="replace").strip()
                    if data:
                        data_queue.put(data)
        except Exception as e:
            print(f"Error in uart_reader_thread: {e}")

# Combined Logging and Relay Thread
def data_processor_thread():
    while True:
        if not data_queue.empty():
            data = data_queue.get()
            temp1, temp2, temp3 = parse_temperatures(data)
            if temp1 is not None:
                log_temperatures(temp1, temp2, temp3)
                control_relays(temp1, temp2, temp3)

# Thread for sending IRQs every 5 seconds
def irq_thread():
    while True:
        print("Sending IRQ to Pico.")
        request_temperatures()
        time.sleep(5.0)  # Slightly longer delay to avoid overlap

# Main function
def main():
    try:
        # Start threads
        _thread.start_new_thread(uart_reader_thread, ())
        _thread.start_new_thread(data_processor_thread, ())
        _thread.start_new_thread(irq_thread, ())
        
        # Keep the main thread alive
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        GPIO.cleanup()
        print("Program terminated.")

if __name__ == "__main__":
    main()

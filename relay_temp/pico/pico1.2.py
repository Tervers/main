from machine import Pin, ADC, UART
import time
import math

#set ADC pins for thermistors
Therm_1 = ADC(26)
Therm_2 = ADC(27)
Therm_3 = ADC(28)

#setup UART
uart = UART(0, baudrate=9600, tx=Pin(12), rx=Pin(13))
de_re = Pin(15, Pin.OUT)

#functions to control UART
def enable_tx():
    de_re.value(1)   #enables transmit mode

def enable_rx():
    de_re.value(0)   #enables receive mode

#Temperature conversion formula
def temp_fahr(Therm_X): 
    Therm_X_Value = Therm_X.read_u16()
    Therm_X_Voltage = Therm_X_Value / 65535.0 * 3.3
    Rt = 10 * Therm_X_Voltage / (3.3-Therm_X_Voltage)
    tempK = (1 / (1 / (273.15+25) + (math.log(Rt/10)) / 3950))
    #tempC = int(tempK - 273.15)
    tempF = (((float(tempK - 273.15) * 9.0) / 5.0) + 32.0)
    tempF = int(tempF) # truncate decimal
    return tempF

#read temperatures from thermistors
def read_temps():
    temp1 = temp_fahr(Therm_1)
    time.sleep(0.05)
    temp2 = temp_fahr(Therm_2)
    time.sleep(0.05)
    temp3 = temp_fahr(Therm_3)
    return temp1, temp2, temp3

#main function
def main():
    enable_rx()
    print("Pico: Waiting for IRQ...")
    
    while True:
        if uart.any():   #read UART signal
            try:
                irq_signal = uart.read(1)
                if irq_signal:
                    irq_signal = irq_signal.decode('utf-8', errors="ignore")   #store UART signal to verify
                    print(f"Pico received: {irq_signal}")
                    
                    if irq_signal == 'R':
                        print("Pico: IRQ received. Sending temperatures...")
                        temp1, temp2, temp3 = read_temps()
                
                        #send temperatures as a single string
                        enable_tx()
                        try:
                            print(f"Pico: Sending temperatures: {temp1},{temp2},{temp3}")
                            uart.write(f"{temp1},{temp2},{temp3}\n".encode("utf-8"))
                            time.sleep(0.2)   #ensure data is sent; increase time for more data
                        except Exception as e:
                            print(f"Pico error sending data: {e}")
                        finally:
                            enable_rx()
            except Exception as e:
                print(f"Pico error handling IRQ: {e}")
                print(f"Error details: {type(e).__name__} - {e}")
        else:
            time.sleep(0.1)

try:
    main()
except Exception as e:
    print(f"Unhandled Pico error: {e}")
    print(f"Error details: {type(e).__name__} - {e}")
except KeyboardInterrupt:
    print("Program stopped.")
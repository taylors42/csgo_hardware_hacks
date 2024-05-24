import serial
import time
import win32api

# for i in range(2, 11):
#     try:
#         arduino = serial.Serial('COM' + str(i), 9600)
#         print("Connected to COM" + str(i))
#         break
#     except:
#         print("Failed to connect to COM" + str(i))
#     time.sleep(1)
arduino = serial.Serial('COM6', 9600)
time.sleep(2)

def envia_comando(num):
    if win32api.GetAsyncKeyState(1) < 0: # when press mouse1 start the RCS
      arduino.write(str(num).encode())
last_time_x_sent = 0
while True:

    if win32api.GetAsyncKeyState(90) < 0 and time.time() - last_time_x_sent > 0.2: # quando pressionado z envia 'r' para controlar o RCS ligado/desligado 
        arduino.write(b'z')
        last_time_x_sent = time.time()
        time.sleep(0.01)
    if win32api.GetAsyncKeyState(88) < 0 and time.time() - last_time_x_sent > 0.2: # quando pressionado x envia 'r' para controlar o RCS ligado/desligado 
        arduino.write(b'x')
        last_time_x_sent = time.time()
        time.sleep(0.01)
    if win32api.GetAsyncKeyState(78) < 0 and time.time() - last_time_x_sent > 0.2: # quando pressionado n envia 'r' para controlar o RCS ligado/desligado 
        arduino.write(b'n')
        last_time_x_sent = time.time()
        time.sleep(0.01)
    if win32api.GetAsyncKeyState(77) < 0 and time.time() - last_time_x_sent > 0.2: # quando pressionado m envia 'v' para controlar o RCS ligado/desligado 
        arduino.write(b'm')
        last_time_x_sent = time.time()
        time.sleep(0.01)
    # if win32api.GetAsyncKeyState(80) < 0 and time.time() - last_time_x_sent > 0.2: # quando pressionado p envia 'v' para controlar o RCS ligado/desligado 
    #     break
    num = 1  # Reinicia num aqui
    while num <= 29 and win32api.GetAsyncKeyState(1) < 0:
        envia_comando(num)
        num += 1
        time.sleep(0.1)

arduino.close()
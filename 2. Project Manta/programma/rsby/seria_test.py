import serial

ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]
while True:
    read_serial=ser.readline()
    s[0] = str(int (ser.readline(),16))
    print (s)
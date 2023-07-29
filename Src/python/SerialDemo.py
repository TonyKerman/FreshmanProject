import serial
import serial.tools.list_ports

# search for available ports
ports = list(serial.tools.list_ports.comports())
print(ports)
if len(ports) == 0:
    print('No available ports found')
else:
    print('Available ports:')
    for p in ports:
        print(p)
#open serial port
try:
    ser = serial.Serial(ports[0][0], 115200)
except SerialException as e:
    print('Error opening serial port\n',e)
    exit()
    

def mdecode(data):
    length= int((len(data)-1)/2)
    val = []
    for i in range(length):
        val.append(int(data[2*i]+data[2*i+1],16))
    return val


while True:
    # read one byte
    byte = ser.read(1)
    # decode the byte as UTF-8
    if byte == b'\x55' and ser.read(1) == b'\x55':
        length = int(ser.read(1).hex(),16)
        print('length is ',length)
        data = []
        for i in range(length):
            data.append(ser.read(1).hex())
        data = mdecode(data)
        print('read a frame ',data)
    else:
        pass
        #print('read a byte ',byte)
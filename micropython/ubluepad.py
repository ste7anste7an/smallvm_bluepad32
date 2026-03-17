from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

from microremote import MicroRemote

class BluePad:
    """
    Class for using LMS-ESP32 running BluePad for MicroBlocks firmware. Defines methods for reading
    connected Bluetooth gamepad (such as PS4 or Nintendo Switch) and for driving NeoPixels and Servo motors connected
    to the LMS-ESP32 board.
    Flash the LMS-ESP32 board with BluePad32 LPF2 for PyBricks projects from 
    https://firmware.antonsmindstorms.com/.
   
    :param port: The port to which the LMS-ESp32 running BluePad32 is connected.
    :type port: Port (Example: Port.A)
    """
    def __init__(self,port):
        self.ur=MicroRemote(port)

    def is_connected(self):
        ack, data = swlf.ur.call("connected")
        return (data)

    def buttons(self):
        ack, data = self.ur.call("btns")
        return (data)

    def dpad(self):
        ack, data = self.ur.call("dpad")
        return (data)

    def joystick_left(self):
        ack, data = self.ur.call('left')    
        x, y = data
        return (x,y)

    def joystick_right(self):
        ack, data = self.ur.call('right')    
        x, y = data
        return (x,y)
        
    def accelerometer(self):
        ack, data = self.ur.call('accel')
        gx, gy, gz = data
        return (gx, gy, gz)
    
    def gyro(self):
        ack, data = self.ur.call('gyro')
        gx, gy, gz = data
        return (gx, gy, gz)
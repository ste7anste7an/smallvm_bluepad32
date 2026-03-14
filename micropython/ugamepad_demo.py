from pybricks.hubs import EV3Brick
from pybricks.ev3devices import Motor, ColorSensor, GyroSensor, InfraredSensor, TouchSensor, UltrasonicSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

hub = EV3Brick()

from ubluepad import BluePad


bp = BluePad(Port.S1)

while 1:
    print(bp.joystick_left(),bp.joystick_right(),bp.buttons(),bp.dpad())
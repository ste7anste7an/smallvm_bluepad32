
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch


from ubluepad import BluePad


bp = BluePad(Port.A)

while 1:
    print(bp.joystick_left(),bp.joystick_right(),bp.buttons(),bp.dpad())
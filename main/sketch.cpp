
#include "sdkconfig.h"

#include <Arduino.h>
#include <Bluepad32.h>


#include "mem.h"
#include "interp.h"
#include "persist.h"
//#include <arduino.h>


ControllerPtr myControllers[BP32_MAX_GAMEPADS];

bool bp32_controller_connected = false;

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            //Console.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            //Console.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName(), properties.vendor_id,
            //               properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            bp32_controller_connected = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Console.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            //Console.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            bp32_controller_connected = false;
            break;
        }
    }

    if (!foundController) {
        //Console.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

int bp32_index = 0;
int bp32_buttons = 0;
int bp32_dpad = 0;
int bp32_axisx = 0;
int bp32_axisy = 0;
int bp32_axisrx = 0;
int bp32_axisry = 0;
int bp32_brake = 0;
int bp32_throttle = 0;
int bp32_misc_buttons = 0;
int bp32_gyrox = 0;
int bp32_gyroy = 0;
int bp32_gyroz = 0;
int bp32_accelx = 0;
int bp32_accely = 0;
int bp32_accelz = 0;

int bp32_playerled = -1;
int bp32_colorledr=-1;
int bp32_colorledg=-1;
int bp32_colorledb=-1;

bool bp32_isconnected() {
    return bp32_controller_connected;
}

int bp32_get_index() {
    return bp32_index;
}

int bp32_get_buttons() {
    return bp32_buttons;
}
int bp32_get_dpad() {
    return bp32_dpad;
}

int bp32_get_axisx() {
    return bp32_axisx;
}

int bp32_get_axisy() {
    return bp32_axisy;
}

int bp32_get_axisrx() {
    return bp32_axisrx;
}

int bp32_get_axisry() {
    return bp32_axisry;
}

int bp32_get_brake() {
    return bp32_brake;
}

int bp32_get_throttle() {
    return bp32_throttle;
}

int bp32_get_misc_buttons() {
    return bp32_misc_buttons;
}

int bp32_get_gyrox() {
    return bp32_gyrox;
}

int bp32_get_gyroy() {
    return bp32_gyroy;
}

int bp32_get_gyroz() {
    return bp32_gyroz;
}

int bp32_get_accelx() {
    return bp32_accelx;
}

int bp32_get_accely() {
    return bp32_accely;
}

int bp32_get_accelz() {
    return bp32_accelz;
}

void bp32_set_player_led(int led) {
    bp32_playerled = led & 0xf;
}


void bp32_set_color_led(int r, int g, int b) {
    bp32_colorledr = r;
    bp32_colorledg = g;
    bp32_colorledb = b;
}

void dumpGamepad(ControllerPtr ctl) {
    // set global variables
    bp32_buttons = ctl->buttons();
    bp32_dpad = ctl->dpad();
    bp32_axisx = ctl->axisX();
    bp32_axisy = ctl->axisY();
    bp32_axisrx = ctl->axisRX();
    bp32_axisry = ctl->axisRY();
    bp32_index =  ctl->index();
    bp32_brake =  ctl->brake();        // (0 - 1023): brake button
    bp32_throttle =  ctl->throttle();     // (0 - 1023): throttle (AKA gas) button
    bp32_misc_buttons =  ctl->miscButtons();  // bitmask of pressed "misc" buttons
    bp32_gyrox =  ctl->gyroX();        // Gyro X
    bp32_gyroy =  ctl->gyroY();        // Gyro Y
    bp32_gyroz =  ctl->gyroZ();        // Gyro Z
    bp32_accelx = ctl->accelX();       // Accelerometer X
    bp32_accely = ctl->accelY();       // Accelerometer Y
    bp32_accelz = ctl->accelZ();

    if (bp32_playerled>=0) {
        ctl->setPlayerLEDs(bp32_playerled);
        bp32_playerled=-1;
    }

    if (bp32_colorledr>=0) {
        ctl->setColorLED(bp32_colorledr, bp32_colorledg, bp32_colorledb);
        bp32_colorledr=-1;
    }

    /* Console.printf(

        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
    */
}


void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...
    // if (ctl->a()) {
    //     static int colorIdx = 0;
    //     // Some gamepads like DS4 and DualSense support changing the color LED.
    //     // It is possible to change it by calling:
    //     switch (colorIdx % 3) {
    //         case 0:
    //             // Red
    //             ctl->setColorLED(255, 0, 0);
    //             break;
    //         case 1:
    //             // Green
    //             ctl->setColorLED(0, 255, 0);
    //             break;
    //         case 2:
    //             // Blue
    //             ctl->setColorLED(0, 0, 255);
    //             break;
    //     }
    //     colorIdx++;
    // }

    // if (ctl->b()) {
    //     // Turn on the 4 LED. Each bit represents one LED.
    //     static int led = 0;
    //     led++;
    //     // Some gamepads like the DS3, DualSense, Nintendo Wii, Nintendo Switch
    //     // support changing the "Player LEDs": those 4 LEDs that usually indicate
    //     // the "gamepad seat".
    //     // It is possible to change them by calling:
    //     ctl->setPlayerLEDs(led & 0x0f);
    // }

    // if (ctl->x()) {
    //     // Some gamepads like DS3, DS4, DualSense, Switch, Xbox One S, Stadia support rumble.
    //     // It is possible to set it by calling:
    //     // Some controllers have two motors: "strong motor", "weak motor".
    //     // It is possible to control them independently.
    //     ctl->playDualRumble(0 /* delayedStartMs */, 250 /* durationMs */, 0x80 /* weakMagnitude */,
    //                         0x40 /* strongMagnitude */);
    // }
    
    // Another way to query controller data is by getting the buttons() function.
    // See how the different "dump*" functions dump the Controller info.
    dumpGamepad(ctl);

    // See ArduinoController.h for all the available functions.
}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            } else {
                Console.printf("Unsupported controller\n");
            }
        }
    }
}



extern "C" {
	bool update_bp32(void) {
        return BP32.update();
    }
	
}

extern "C" {
	void loop_process_controllers(void) {
        processControllers();
    }
	
}




void setup() {
    #ifdef ARDUINO_NRF52_PRIMO
        sd_softdevice_disable();
    #endif
    #ifdef DUELink
        // Workaround: start USB clock
        LL_RCC_HSI48_Enable();
        while (LL_RCC_HSI48_IsReady() != 1) {}
    #endif
    Console.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Console.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    bool startScanning = true;
    BP32.setup(&onConnectedController, &onDisconnectedController, startScanning);
    BP32.forgetBluetoothKeys();
    BP32.enableVirtualDevice(false);

    // Enables the BLE Service in Bluepad32.
    // This service allows clients, like a mobile app, to setup and see the state of Bluepad32.
    // By default, it is disabled.
    BP32.enableBLEService(false);

        delay(5000);
        memInit();
        primsInit();
        hardwareInit();
        outputString((char *) "Welcome to MicroBlocks!");
        restoreScripts();
        //if (BLE_isEnabled()) BLE_start();
        startAll();
        
    
    }
    
    void loop() {

        vmLoop();
    }
    

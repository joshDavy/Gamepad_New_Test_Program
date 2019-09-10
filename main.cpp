

// Includes
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "stdio.h"


// objects
Gamepad pad;
N5110 lcd;

void check_buttons();

int main()
{
    lcd.init();
    lcd.setContrast(0.5);
    pad.init();

    lcd.backLightOn();
    lcd.printString("Hello Gamepad!",0,0);
    lcd.refresh();
    pad.tone(1000.0,2.0);

    for (int i = 0; i < 1000; i++) {
        lcd.setContrast( pad.read_pot1());
        wait_ms(10);
    }

    for (int i = 0; i < 10; i++) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
    }

    for (float x = 0.0f; x <= 1.0f ; x+=0.1f) {
        pad.leds(x);
        wait(0.1);
    }

    for (int n = 1; n <= 6; n++) {
        pad.led(n,0.5);
        wait(0.5);
    }

    pad.leds_off();

    while(1) {
        pad.leds_off();
        lcd.clear();   
        lcd.setContrast( pad.read_pot1());
        check_buttons();
        lcd.drawCircle(WIDTH/2,HEIGHT/2,20,FILL_TRANSPARENT);  // x,y,radius,transparent with outline
        Vector2D coord = pad.get_mapped_coord();
        float x = coord.x;
        float y = coord.y;

        if ( pad.A_pressed()) {
            lcd.drawCircle(WIDTH/2+int(20*x),HEIGHT/2-int(20*y),3,FILL_BLACK);
        } else {
            lcd.drawCircle(WIDTH/2+int(20*x),HEIGHT/2-int(20*y),3,FILL_TRANSPARENT);
        }

        lcd.refresh();
        wait(1.0f/5.0f);
    }
}

void check_buttons()
{
    if ( pad.A_pressed())  {
        lcd.printChar('A',0,0);
        pad.led(1,0.5);
        pad.tone(1000.0,0.2);
        printf("A pressed\n");
    }
    if ( pad.B_pressed())  {
        lcd.printChar('B',0,1);
        pad.led(2,0.5);
        pad.tone(1000.0,0.2);
        printf("B pressed\n");
    }
    if ( pad.X_pressed())  {
        lcd.printChar('X',0,2);
        pad.led(3,0.5);
        pad.tone(1000.0,0.2);
        printf("X pressed\n");
    }
    if ( pad.Y_pressed() ) {
        lcd.printChar('Y',0,3);
        pad.led(4,0.5);
        pad.tone(1000.0,0.2);
        printf("Y pressed\n");
    }
    if ( pad.start_pressed()) {
        lcd.printChar('S',78,2);
        pad.tone(1000.0,0.2);
        printf("Start pressed\n");
    }


}
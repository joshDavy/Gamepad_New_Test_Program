#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <bitset>

// Forward declaration of the classes that we use from the mbed library
// This avoids the need for us to include the huge mbed_os.h header inside our
// own library API
namespace mbed
{
class AnalogIn;
class InterruptIn;
class PwmOut;
class Timeout;
class AnalogOut;
class Ticker;
}

#define TOL 0.1f
#define RAD2DEG 57.2957795131f

/** Enum for direction */
enum Direction {
    CENTRE,  /**< joystick centred */
    N,       /**< pushed North (0)*/
    NE,      /**< pushed North-East (45) */
    E,       /**< pushed East (90) */
    SE,      /**< pushed South-East (135) */
    S,       /**< pushed South (180) */
    SW,      /**< pushed South-West (225) */
    W,       /**< pushed West (270) */
    NW       /**< pushed North-West (315) */
};

/** Vector 2D struct */
struct Vector2D {
    float x; /**< float for x value */
    float y; /**< float for y value */
};

/** Polar coordinate struct */
struct Polar {
    float mag;  /**< float for magnitude */
    float angle; /**< float for angle (in degrees) */
};

/** Gamepad Class
 * @brief Library for interfacing with ELEC2645 Gamepad PCB, University of Leeds
 * @author Dr Craig A. Evans
 * @author Dr Alex Valavanis
 */
class Gamepad
{

private:
    mbed::PwmOut *_led1;
    mbed::PwmOut *_led2;
    mbed::PwmOut *_led3;
    mbed::PwmOut *_led4;
    mbed::PwmOut *_led5;
    mbed::PwmOut *_led6;

    mbed::InterruptIn *_button_A;
    mbed::InterruptIn *_button_B;
    mbed::InterruptIn *_button_X;
    mbed::InterruptIn *_button_Y;
    mbed::InterruptIn *_button_start;

    mbed::AnalogIn *_vert;
    mbed::AnalogIn *_horiz;

    mbed::AnalogOut  *_speaker;
    mbed::AnalogIn *_pot1;
    mbed::AnalogIn *_pot2;

    mbed::Timeout *_timeout;
    mbed::Ticker *_ticker;


    
    // centred x,y values
    float _x0;
    float _y0;

public:
    /** Constructor */
    Gamepad();

    /** Initialise all peripherals and configure interrupts */
    void init();

    /** Turn all LEDs on */
    void leds_on();

    /** Turn all LEDs off */
    void leds_off();

    /** Set all LEDs to duty-cycle
    *@param value in range 0.0 to 1.0
    */
    void leds(float val) const;

    /** Set LED to duty-cycle
    *@param led number (0 to 5)
    *@param value in range 0.0 to 1.0
    */
    void led(int n,float val) const;

    /** Read potentiometer 1 value
    *@returns potentiometer value in range 0.0 to 1.0
    */
    float read_pot1() const;

    /** Read potentiometer 2 value
    *@returns potentiometer value in range 0.0 to 1.0
    */
    float read_pot2() const;

    /** Play tone on piezo (NOTE: Frequencys below 1kHz can damage the speaker)
    * @param frequency in Hz
    * @param duration of tone in seconds
    */
    void tone(float frequency, float duration);




    /** Get magnitude of joystick movement
    * @returns value in range 0.0 to 1.0
    */
    float get_mag();

    /** Get angle of joystick movement
    * @returns value in range 0.0 to 359.9. 0.0 corresponds to N, 180.0 to S. -1.0 is central
    */
    float get_angle();

    /** Gets joystick direction
    * @returns an enum: CENTRE, N, NE, E, SE, S, SW, W, NW,
    */
    Direction get_direction();    // N,NE,E,SE etc.

    /** Gets raw cartesian co-ordinates of joystick
    * @returns a struct with x,y members, each in the range 0.0 to 1.0
    */
    Vector2D get_coord();         // cartesian co-ordinates x,y

    /** Gets cartesian coordinates mapped to circular grid
    * @returns a struct with x,y members, each in the range 0.0 to 1.0
    */
    Vector2D get_mapped_coord();  // x,y mapped to circle

    /** Gets polar coordinates of the joystick
    * @returns a struct contains mag and angle
    */
    Polar get_polar();            // mag and angle in struct form


    /** Resets all button states. Useful for calling inbetween scenes
    *   where you do not want button presses from the previous scene effecting
    *   the current scene
    */
    void reset_buttons();

    /** Returns true if A has been pressed
    * @returns a bool corresponding to A being pressed
    */

    bool A_pressed();

    /** Returns true if A is held
    * @returns a bool corresponding to A being held
    *
    */
    bool A_held();
    

    /** Returns true if B has been pressed
    * @returns a bool corresponding to B being pressed
    */
    bool B_pressed();

    /** Returns true if B is held
    * @returns a bool corresponding to B being held
    *
    */
    bool B_held();

    /** Returns true if B has been pressed
    * @returns a bool corresponding to B being pressed
    */
    bool X_pressed();

    /** Returns true if X is held
    * @returns a bool corresponding to X being held
    *
    */
    bool X_held();    

    /** Returns true if Y has been pressed
    * @returns a bool corresponding to Y being pressed
    */
    bool Y_pressed();

    /** Returns true if Y is held
    * @returns a bool corresponding to Y being held
    *
    */
    bool Y_held();


    /** Returns true if start has been pressed
    * @returns a bool corresponding to start being pressed
    */
    bool start_pressed();

    /** Returns true if start is held
    * @returns a bool corresponding to start being held
    *
    */
    bool start_held();




private:

    void tone_off();
    void flip_DAC();

    volatile bool A_fall;
    void A_fall_interrupt();

    volatile bool B_fall;
    void B_fall_interrupt();
    
    volatile bool X_fall;
    void X_fall_interrupt();

    volatile bool Y_fall;
    void Y_fall_interrupt();

    volatile bool start_fall;
    void start_fall_interrupt();




};

#endif
#include <avr/io.h>
#include <util/delay.h>
#define setbit(reg, bit) reg |= (1<<bit)            // Set a bit
#define clearbit(reg, bit) reg &= ~(1<<bit)         // Clear a bit
#define readbit(reg, bit) (reg & (1<<bit))>>bit     // Read a bit
#define C1 PB0
#define C2 PB1
#define C3 PB2
#define R1 PC0
#define R2 PC1
#define R3 PC2
#define R4 PC3
unsigned char numb[4][3]={{0xF9,0xA4,0xB0},{0x99,0x92,0x82},{0xF8,0x80,0x90},{0x88,0xc0,0x7f}};
//{{1,2,3}, {4,5,6}, {7,8,9}, {*,0,#}}
// hex. codes of numbers in common anode 7-segement, corresponding to 4 rows and 3 columns of the keypad

int main(void) {
  DDRD = 0xff;      // 8 pins of PORTD connected to 8 pins of 7-segement (outputs)
  PORTD = 0xff;     // Initialize all pins to high (No LED in the 7-segment is ON)
  DDRC = 0x0f;      // PC3-->PC0 pins of PORTC connected to 4 rows of keypad (outputs)
  PORTC = 0x0f;     // Initialize all rows' pins to high
  DDRB = 0x00;      // PB2--> PB0 pins of PORTB connected to 3 columns of keypad (inputs)
  PORTB = 0x07;     // Activates internal pull up of PB2-->PB0
  int x, row, col;
  while (1) {
    for (int i = 0; i<4; i++) {      // Loops on the four rows 
      clearbit(PORTC, i);            // Clears each row
      for (int j = 0; j<3; j++) {    // Loops on the 3 columns
        x = readbit(PINB, j);        // Reads the state of buttons
        if (x==0) {                  // Checks if a button on the keypad is pressed
          row = i;
          col = j;
          PORTD = numb[row][col];
        }
      }
      setbit(PORTC, i);              // Sets the row after checking its buttons
      }
    }
    return 0;
}

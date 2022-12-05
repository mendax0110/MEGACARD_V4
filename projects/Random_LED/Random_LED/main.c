/*
 * Random_LED.c
 *
 * Created: 05.12.2022 21:34:02
 * Author : Adrian
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

// Define LED pins
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PB0

// Function to turn the LED on or off
void set_led(int on)
{
  if (on)
  {
    LED_PORT |= (1 << LED_PIN);
  }
  else
  {
    LED_PORT &= ~(1 << LED_PIN);
  }
}

int main(void)
{
  // Set the LED pin as an output
  LED_DDR |= (1 << LED_PIN);

  // Initialize the game variables
  int position = 0;
  int direction = 1;
  int speed = 50;
  int game_over = 0;

  // Game loop
  while (!game_over)
  {
    // Move the LED in the current direction
    position += direction;

    // Check if the LED has reached the end of the screen
    if (position == 0 || position == 7)
    {
      // Change the direction of the LED
      direction *= -1;
    }

    // Clear the LED port
    LED_PORT = 0;

    // Set the LED at the current position
    for (int i = 0; i < 8; i++)
    {
      if (i == position)
      {
        // Set the bit for the current position
        LED_PORT |= (1 << i);
      }
    }

    // Delay to control the speed of the game
    _delay_ms(speed);
  }

  return 0;
}

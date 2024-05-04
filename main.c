#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*Prototypes*/

void stateA(void);
void stateB(void);
void stateC(void);
void initializeSM(void);
void wait(void);

// Enum type to represent each state we have
typedef enum { STATE_A = 0, STATE_B, STATE_C } State_Type;

// Table of pointers to the functions for each state
static void (*state_table[])(void) = {stateA, stateB, stateC};

// Globals
static State_Type curr_state;
static int Clock;
static int out;

int main(void) {
  // init SM
  initializeSM();

  /*The main state transition loop*/
  while (1) {
    state_table[curr_state]();
    wait();
    Clock++;
  }

  return 0;
}

void stateA(void) {
  if (Clock == 2) { // Change State?
    printf("Changing to B\n");
    curr_state = STATE_B; // Next State
    out = 1;              // New Output
  }
}

void stateB(void) {
  if (Clock == 5) {
    printf("Changing to C\n");
    curr_state = STATE_C;
    out = 2;
  }
}

void stateC(void) {
  if (Clock == 9) { // change State?i
    printf("Reverting to A\n");
    Clock = 0; // Reset Clock .... Statrt from the beginning
    curr_state = STATE_A;
    out = 0;
  }
}

void initializeSM(void) {
  printf("Setting up from A\n");
  curr_state = STATE_A;
  out = 0;
  Clock = 1;
}

void wait(void) {
  printf("Waiting for 5 seconds\n");
  sleep(5);
}

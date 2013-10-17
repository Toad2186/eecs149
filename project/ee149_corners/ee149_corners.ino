struct linkedList {
  int col;
  struct linkedList *next;
};

/*
 * Column pins
*/
const int COL_0_0 = 12;
const int COL_1_0 = 21;
const int COL_2_0 = 20;
const int COL_0_1 = 19;
const int COL_1_1 = 18;
const int COL_2_1 = 17;
const int COL_0_2 = 16;
const int COL_1_2 = 15;
const int COL_2_2 = 14;
const int COL_INVALID = 99;
/*
 * Plane pins
*/

const int PLANE_0 = 0;
const int PLANE_1 = 1;
const int PLANE_2 = 2;
const int PLANE_INVALID = 99;
/*
 * Number of columns
*/
const int NUM_COLS = 9;
/*
 * Number of planes
*/
const int NUM_PLANES = 3;

/*
 * Currently ON plane
*/
int plane;
/*
 * Currently ON columns
*/
struct linkedList *cols = (struct linkedList*) malloc(sizeof(struct linkedList));

/*
 * Init pins to be outputs
*/
void setupPins() {
  pinMode(COL_0_0, OUTPUT);
  pinMode(COL_0_1, OUTPUT);
  pinMode(COL_0_2, OUTPUT);
  pinMode(COL_1_0, OUTPUT);
  pinMode(COL_1_1, OUTPUT);
  pinMode(COL_1_2, OUTPUT);
  pinMode(COL_2_0, OUTPUT);
  pinMode(COL_2_1, OUTPUT);
  pinMode(COL_2_2, OUTPUT);
  pinMode(PLANE_0, OUTPUT);
  pinMode(PLANE_1, OUTPUT);
  pinMode(PLANE_2, OUTPUT);

}

void setInvalid() {
  plane = PLANE_INVALID;
  cols->col = COL_INVALID;
  cols->next = NULL;
}

/*
 * Initialize to invalid
*/
void setup() {
  setupPins();
  setInvalid();
  // Turn the first corner ones
  plane = PLANE_0;
  cols->col = COL_0_0; 
  turnOn();
  delay(1000);
}

void loopPins(int mode) {
  struct linkedList *myCols = cols;
  while(myCols) {
    digitalWrite(myCols->col, mode);
    myCols = myCols->next; 
  }
}

void turnOff() {
  loopPins(LOW);
  digitalWrite(plane, LOW);
}

void turnOn() {
  loopPins(HIGH);
  digitalWrite(plane, HIGH);
}

// Alternates between each LED, one at a time
void verifyLeds() {
  turnOff();
  switch(cols->col) {
    case COL_0_0:
      cols->col = COL_1_0;
      break;
    case COL_1_0:
      cols->col = COL_2_0;
      break;
    case COL_2_0:
      cols->col = COL_0_1;
      break;
    case COL_0_1:
      cols->col = COL_1_1;
      break;
    case COL_1_1:
      cols->col = COL_2_1;
      break;
    case COL_2_1:
      cols->col = COL_0_1;
      break;
    case COL_0_2:
      cols->col = COL_1_2;
      break;
    case COL_1_2:
      cols->col = COL_2_2;
      break;
    case COL_2_2:
      cols->col = COL_0_0;
      switch(plane) {
        case PLANE_0:
          plane = PLANE_1;
          break;
        case PLANE_1:
          plane = PLANE_2;
          break;
        case PLANE_2:
          plane = PLANE_0;
          break;
      }
      break;
  }
  turnOn();
}

// Alternates between the bottom corners (one at a time),
// and the top corners.
void alternateCorner() {
  turnOff();
  switch(cols->col) {
    case COL_0_0:
      cols->col = COL_2_0;
      break;
    case COL_2_0:
      cols->col = COL_2_2;
      break;
    case COL_2_2:
      cols->col = COL_0_2;
      break;
    case COL_0_2:
      cols->col = COL_0_0;
      switch (plane) {
        case PLANE_0:
          plane = PLANE_2;
          break;
        case PLANE_2:
          plane = PLANE_0;
          break;
      }
      break;
  }
  turnOn();
}

void loop() {
  alternateCorner(); 
  // Wait a second
  delay(1000);
}

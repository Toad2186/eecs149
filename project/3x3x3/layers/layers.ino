/*
 * Column pins
*/
const int COL_0_0 = 12;
const int COL_1_0 = 19;
const int COL_2_0 = 16;
const int COL_0_1 = 21;
const int COL_1_1 = 18;
const int COL_2_1 = 15;
const int COL_0_2 = 20;
const int COL_1_2 = 17;
const int COL_2_2 = 14;
const int COL_INVALID = 99;
/*
 * Plane pins
*/

const int PLANE_0 = 22;
const int PLANE_1 = 11;
const int PLANE_2 = 13;
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
const int planes[3] = { PLANE_0, PLANE_1, PLANE_2 };
/*
/*
 * Currently ON columns
*/
const int cols[9] = {COL_0_0, COL_1_0, COL_2_0,
                     COL_0_1, COL_1_1, COL_2_1,
                     COL_0_2, COL_1_2, COL_2_2};

void setup() {
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

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(planes[i], HIGH);
    for (int j = 0; j < 9; ++j) {
       digitalWrite(cols[j], HIGH);
    }
    delay(1000);
    for (int j = 0; j < 9; ++j) {
       digitalWrite(cols[j], LOW);
    }
    digitalWrite(planes[i], LOW);
  } 
}

#include <Adafruit_NeoPixel.h>
#include <color.h>
#define PIN 6

int cols = 3;
int values = 4;
int matrix[][3][4] = {
  {
    {
      0,0,0,0    }
    , {
      17,0,0,0    }
    , {
      19,0,0,0    }
  }
  ,
  {
    {
      1,0,0,0    }
    , {
      16,0,0,0    }
    , {
      20,0,0,0    }
  }
  ,
  {
    {
      2,0,0,0    }
    , {
      15,0,0,0    }
    , {
      21,0,0,0    }
  }
  ,
  {
    {
      3,0,0,0    }
    , {
      14,0,0,0    }
    , {
      22,0,0,0    }
  }
  ,
  {
    {
      4,0,0,0    }
    , {
      13,0,0,0    }
    , {
      23,0,0,0    }
  }
  ,
  {
    {
      5,0,0,0    }
    , {
      12,0,0,0    }
    , {
      24,0,0,0    }
  }
  ,
  {
    {
      6,0,0,0    }
    , {
      11,0,0,0    }
    , {
      25,0,0,0    }
  }
  ,
  {
    {
      7,0,0,0    }
    , {
      10,0,0,0    }
    , {
      26,0,0,0    }
  }
  ,
  {
    {
      8,0,0,0    }
    , {
      9,0,0,0    }
    ,  {
      27,0,0,0    }
  }
  ,
};
int rows = sizeof(matrix)/sizeof(*matrix);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}
void loop() {

  /*int c1 = random(0,255);
   int c2 = random(0,255);
   int c3 = random(0,255);  
   for (int i=0; i<rows; i++) {
   setColorToRow(i, c1, c2, c3);
   //setColorToRow(i+1, c1, c2, c3);
   showMatrix();
   delay(125);
   }
   delay(200);*/

customRunner1();
//customRunner2();
//customRunner3();
//customRunner4();

//  customRunner4();
  //  customRunner2();
//  customRunner1();
  //hueRunnerFast();
    //hueRunnerSlow();
  //hueComplete();
  //simpleRunner();
  //simpleRainbow();
}

void showMatrix() {
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      int *led = matrix[i][j];
      strip.setPixelColor(led[0], strip.Color(led[1], led[2], led[3]));
    }
  }
  strip.show();
}

void setColorToRow(int row, Color color) {
  for (int c=0; c<cols; c++) {
    int *led = matrix[row][c];
    Serial.println(color.red);
    led[1] = color.red;
    led[2] = color.green;
    led[3] = color.blue;      
  }
}

void setColorToCompleteMatrix(int r, int g, int b) {
  for (int row=0; row<rows; row++) {
    for (int c=0; c<cols; c++) {
      int *led = matrix[row][c];
      led[1] = r;
      led[2] = g;
      led[3] = b;      
    }
  }
}

Color getHueColor(float hue) {
  Color color = Color(1,1,1);
  float sat = 1.0;
  float val = 0.4;

  color.convert_hcl_to_rgb(hue,sat,val);
  return color;
}

void shiftArrayRight(float* arr, int arrl) {
  float last = arr[arrl-1];
  for (int row=arrl-1; row>=0; row--) {
    arr[row+1] = arr[row];
  }
  arr[0] = last;
}

void shiftArrayLeft(float* arr, int arrl) {
  float first = arr[0];
  for (int row = 1; row<rows; row++) {
    arr[row-1] = arr[row];
  }
  arr[rows-1] = first;
}

void oneTimeRunnerRight(float *hueArr) {
  for (int i=0; i<rows; i++) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hueArr[row]);
      setColorToRow(row, color);      
    }
    showMatrix();
    shiftArrayRight(hueArr, rows);
    delay(20);
  }
}


void oneTimeRunnerLeft(float *hueArr) {
  for (int i=0; i<rows; i++) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hueArr[row]);
      setColorToRow(row, color);      
    }
    showMatrix();
    shiftArrayLeft(hueArr, rows);
    delay(20);
  }
}

void hueComplete() {
  Color color = Color(1,1,1);
  for (float hue=0.0; hue<=1.0; hue+=0.002) {
    color = getHueColor(hue);
    setColorToCompleteMatrix(color.red, color.green, color.blue);
    showMatrix();
    delay(40);
  }
}

void simpleRunner() {
  for (float hue=0.0; hue<=1.0; hue+=0.1) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hue);
      setColorToRow(row, color);
      showMatrix();
      delay(500);
    }
  }
}

void simpleRainbow() {
  int row = random(0, rows);
  int r = random(0,100);
  float hue = r / 100.0;
  Color color = getHueColor(hue);
  setColorToRow(row, color);

  showMatrix();
  delay(1500);

  //delay(250);
}



void hueRunnerFast() {
  float hueArr[rows];
  for (int row=0; row<rows; row++) {
    float hue = (1.0/(rows-1))  * row;
    hueArr[row] = hue;
  }
  
  while(1) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hueArr[row]);
      setColorToRow(row, color);      
    }
    showMatrix();
    delay(20);
    shiftArrayRight(hueArr, rows);
  }
}

void hueRunnerSlow() {
  float hueArr[rows];
  for (int row=0; row<rows; row++) {
    float hue = (1.0/(rows-1))  * row;
    hueArr[row] = hue;
  }
  
  while(1) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hueArr[row]);
      setColorToRow(row, color);      
    }
    showMatrix();
    delay(1500);
    shiftArrayRight(hueArr, rows);
  }
}

void customRunner1() {
  float hueArr[] = {0.0, 0.0, 0.2, 0.2, 0.4, 0.4, 0.6, 0.6, 0.8};
 
  while(1) {
    for (int row=0; row<rows; row++) {
      Color color = getHueColor(hueArr[row]);
      setColorToRow(row, color);      
    }
    showMatrix();
    delay(20);
    shiftArrayRight(hueArr, rows);
  }  
}




void customRunner2() {
  float hueArr[] = {0.15, 0.1, 0.05, 0.0, 0.0, 0.0, 0.05, 0.1, 0.15};
  while(1){
    oneTimeRunnerRight(hueArr); 
  }
}

void customRunner3() {
  float hueArr[] = {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7};
  while(1){
    oneTimeRunnerRight(hueArr); 
  }
}

void customRunner4() {
  float hueArr[] = {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7};
  while(1){
    oneTimeRunnerRight(hueArr); 
    oneTimeRunnerLeft(hueArr); 
  }
}


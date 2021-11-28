#include <Servo.h> // include Servo library

// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 90;    // stand horizontal servo

int servohLimitHigh = 175;
int servohLimitLow = 5;

// 65 degrees MAX
Servo vertical;   // vertical servo
int servov = 45;   // stand vertical servo

int servovLimitHigh = 80;
int servovLimitLow = 15;


// LDR pin connections
//  name  = analogpin;
int ldrlt = A1; //LDR top left 
int ldrrt = A3; //LDR top rigt 
int ldrld = A0; //LDR down left 
int ldrrd = A2; //ldr down rigt 

void setup()
{
 Serial.begin(9600);
// servo connections
 horizontal.attach(9);
 vertical.attach(10);
 horizontal.write(180);
 vertical.write(45);
 delay(3000);
}

void loop()
{
 int lt = analogRead(ldrlt); // top left
 int rt = analogRead(ldrrt); // top right
 int ld = analogRead(ldrld); // down left
 int rd = analogRead(ldrrd); // down rigt
 
 int dtime = 10;
//****** int tol = 1;
 
 int avt = (lt + rt) / 2; // average value top
 int avd = (ld + rd) / 2; // average value down
 int avl = (lt + ld) / 2; // average value left
 int avr = (rt + rd) / 2; // average value right

 int dvert = avt - avd; // diffirence of up and down
 int dhoriz = avl - avr;// diffirence og left and rigt
 
 
 Serial.print(avt);
 Serial.print(" ");
 Serial.print(avd);
 Serial.print(" ");
 Serial.print(avl);
 Serial.print(" ");
 Serial.print(avr);
 Serial.print("   ");
 Serial.print(dtime);
 Serial.print("   ");
//****** Serial.print(tol);
 Serial.println(" ");
 
   
//****** if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
 {
 if (avt > avd)
 {
   servov = ++servov;
    if (servov > servovLimitHigh)
    {
     servov = servovLimitHigh;
    }
 }
 else if (avt < avd)
 {
   servov= --servov;
   if (servov < servovLimitLow)
 {
   servov = servovLimitLow;
 }
 }
 vertical.write(servov);
 }
 
//****** if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
 {
 if (avl > avr)
 {
   servoh = --servoh;
   if (servoh < servohLimitLow)
   {
   servoh = servohLimitLow;
   }
 }
 else if (avl < avr)
 {
   servoh = ++servoh;
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
 }
 else if (avl = avr)
 {
   // nothing
 }
 horizontal.write(servoh);
 }
  delay(dtime);

}

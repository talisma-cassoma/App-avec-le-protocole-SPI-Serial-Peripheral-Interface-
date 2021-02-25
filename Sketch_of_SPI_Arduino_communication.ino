#include <SPI.h> // necessary library
int ss=10; // using digital pin 10 for SPI slave select
int del=15; // used for fading delay
void setup()
{
pinMode(ss, OUTPUT); // we use this for SS pin
SPI.begin(); // wake up the SPI bus.
SPI.setBitOrder(MSBFIRST);
// our AD5204 requires data to be sent MSB (Most Significant Bit) first. See data sheet
allOff(); // we do this as pot memories are volatile
}
void allOff()
// sets all potentiometers to minimum value
{
for (int z=0; z<4; z++)
{
setPot(z,0);
}
}
void allOn()
// sets all potentiometers to maximum value
{
for (int z=0; z<4; z++)
{
setPot(z,255);
}
}
void setPot(int pot, int level)
// sets potentiometer 'pot' to level 'level'
{
digitalWrite(ss, LOW);
SPI.transfer(pot);
SPI.transfer(level);
digitalWrite(ss, HIGH);
}
void blinkAll(int count) {
for (int i=0;i<count;i++) {
for (int z=0; z<4; z++) {
setPot(z,255);
delay(500);
setPot(z,0);
delay(500); }}}
void Infad() {
for (int a=0; a<4; a++) {
for (int l=0; l<255; l++) {
setPot(a,l);
delay(del); }
for (int l=255; l>=0; --l) {
setPot(a,l);
delay(del); }}}
void loop() {
blinkAll(3);
allOn();
delay(1000);
Infad();
delay(5000);
allOff();
delay(1000);
}

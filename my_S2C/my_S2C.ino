
int dec_to_hexa_conversion(int decimal_Number);
//void canSniff(const CAN_message_t &msg);


#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "Arduino.h"
#include "FlexCAN_T4.h"
#include <FreqMeasure.h>

#define IR1 0x3A // Update to 0x5A  // Tire Inside
#define IR2 0x5B // Tire Middle
#define IR3 0x5C // Tire Outside
#define IR4 0x5D // Brake Temperature

Adafruit_MLX90614 mlx;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can0;

int inside_tire_temp = 0;
int middle_tire_temp = 0;
int outside_tire_temp = 0;
int brake_temp = 0;

int wheel_freq = 0;

CAN_message_t msg;
double sum=0;
int count=0;

void setup() {
  Serial.begin(9600);

  FreqMeasure.begin();
  
  Serial.println("Starting S2C Module");  

  mlx.begin(); 

  FreqMeasure.begin();

  can0.begin();
  can0.setBaudRate(500000);
  can0.enableFIFO();
  can0.enableMBInterrupt(FIFO);
  // can0.onReceive(FIFO, canSniff);
  delay(500);
  //Serial.println("CAN setup finished");
  can0.setMB(MB0,TX,EXT);

  msg.len = 8;
  msg.flags.extended = 1;

  msg.id = 0x0010; // SET THE ACTUAL VALUES FOR EACH MODULE

  msg.buf[0] = 00;
  msg.buf[1] = 00; 
  msg.buf[2] = 00;
  msg.buf[3] = 00;
  msg.buf[4] = 00;
  msg.buf[5] = 00;
  msg.buf[6] = 00;
  msg.buf[7] = 00;
  // can1.write(msg);
  delay(500);

  Serial.println("S2C Initialization Complete.");

}

void loop() {
  
  mlx.AddrSet(IR1); 
  // Serial.print("IR1: ");
  // Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  inside_tire_temp = mlx.readObjectTempC();
  delay(50);

  mlx.AddrSet(IR2); 
  // Serial.print("IR2: ");
  // Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  middle_tire_temp = mlx.readObjectTempC();
  delay(50);

  mlx.AddrSet(IR3); 
  // Serial.print("IR3: ");
  // Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  outside_tire_temp = mlx.readObjectTempC();
  delay(50);

  mlx.AddrSet(IR4); 
  // Serial.print("IR3: ");
  // Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  brake_temp = mlx.readObjectTempC();
  delay(50);

  // Measure frequency
  wheel_freq = FreqMeasure.countToFrequency(FreqMeasure.read());



  msg.buf[0] = dec_to_hexa_conversion(inside_tire_temp);
  msg.buf[1] = dec_to_hexa_conversion(middle_tire_temp);
  msg.buf[2] = dec_to_hexa_conversion(outside_tire_temp);
  msg.buf[3] = dec_to_hexa_conversion(brake_temp);

  // MAY NEED TO PLAY AROUND WITH THIS, POTENTIALLY CONVERT TO RPM/KMH
  msg.buf[4] = dec_to_hexa_conversion(wheel_freq);

  can0.write(msg);

  Serial.print("IR1: ");
  Serial.print(inside_tire_temp);

  Serial.print("   IR2: ");
  Serial.print(middle_tire_temp);

  Serial.print("   IR3: ");
  Serial.println(outside_tire_temp);

  Serial.print("Rotor Freq: ");
  Serial.println(wheel_freq);

  // if (FreqMeasure.available()) {
  //   Serial.println("IN");
  //   // average several reading together
  //   sum = sum + FreqMeasure.read();
  //   count = count + 1;
  //   if (count > 30) {
  //     float frequency = FreqMeasure.countToFrequency(sum / count);
  //     Serial.println(frequency);
  //     sum = 0;
  //     count = 0;
  //   }
  // }
  

  //delay(500);
}



int dec_to_hexa_conversion(int decimal_Number) 
// VERIFY THAT THIS IS CORRECT
// CURRENTLY RETURNING THE WRONG THING IN THE WRONG FORMAT...
{ 
    int i = 1, j, temp; 
    char hexa_Number[100]; 
    
    // if decimal number is not  
    // equal to zero then enter in 
    // to the loop and execute the 
    // statements 
    while (decimal_Number != 0) { 
        temp = decimal_Number % 16; 
        
        // converting decimal number  
        // in to a hexa decimal 
        // number 
        if (temp < 10) 
            temp = temp + 48; 
        else
            temp = temp + 55; 
        hexa_Number[i++] = temp; 
        decimal_Number = decimal_Number / 16; 
    } 
    return hexa_Number;
    // printing the hexa decimal number 
    // printf("Hexadecimal value is: "); 
    // for (j = i - 1; j > 0; j--) 
    //     printf("%c", hexa_Number[j]); 
} 

// void canSniff(const CAN_message_t &msg) {
//     Serial.println("Interrupted");
//     Serial.print("MB ");
//     Serial.print(msg.mb);
//     Serial.print(" OVERRUN: ");
//     Serial.print(msg.flags.overrun);
//     Serial.print(" LEN: ");
//     Serial.print(msg.len);
//     Serial.print(" EXT: ");
//     Serial.print(msg.flags.extended);
//     Serial.print(" TS: ");
//     Serial.print(msg.timestamp);
//     Serial.print(" ID: ");
//     Serial.print(msg.id, HEX);
//     Serial.print(" Buffer: ");
//     for ( uint8_t i = 0; i < msg.len; i++ ) {
//         Serial.print(msg.buf[i], HEX);
//         Serial.print(" ");
//     }
//     Serial.println();
// }
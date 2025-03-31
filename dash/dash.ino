//July 20, 2023: Added Nextion code to show most of the information on the dash except for Throttle, RPM, and AC Current
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//#include "EasyNextionLibrary.h"
#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CAN_message_t msg;

//EasyNex myNex(Serial1);
int pageNum = 0;
boolean inCanSniff = true;

#define NUM_TX_MAILBOXES 2
#define NUM_RX_MAILBOXES 8

int Pack_Current;
int Pack_Inst_Vol;
int Pack_Inst_Vol_Pt2;
int Pack_SOC;
int Relay_State;
int Pack_DCL;
int High_Temp;
int Low_Temp;
int ERPM_Pt1;
int ERPM_Pt2;
int acCurrent_Pt1;
int acCurrent_Pt2;
int cellTemp_Pt1;
int cellTemp_Pt2;


void setup(void) {
//myNex.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); delay(400); //9600 baud should theoretically also work
  Can0.begin();
  Can0.setBaudRate(500000); //500 000 baud rate of our can
  Can0.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);
  for (int i = 0; i<NUM_RX_MAILBOXES; i++){
    Can0.setMB((FLEXCAN_MAILBOX)i,RX,EXT);
  }
  for (int i = NUM_RX_MAILBOXES; i<(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++){
    Can0.setMB((FLEXCAN_MAILBOX)i,TX,EXT);
  }
  Can0.setMBFilter(REJECT_ALL); //need this because we're doing specific mailboxes for each variable
  Can0.enableMBInterrupts();
  Can0.onReceive(MB0,canSniff);
  Can0.onReceive(MB1,canSniff);
  Can0.onReceive(MB2,canSniff);
  Can0.onReceive(MB3,canSniff);
  Can0.onReceive(MB4,canSniff);
  Can0.onReceive(MB5,canSniff);
  Can0.onReceive(MB6,canSniff);
  Can0.onReceive(MB7,canSniff);
  Can0.setMBFilter(MB0, 0x680); // Pack current, pack inst vol, ...
  Can0.setMBFilter(MB1, 0x681); // Pack DCL, ...
  Can0.setMBFilter(MB2, 0xAFF); //rpm
  Can0.setMBFilter(MB3, 0x51); //acCurrent
  Can0.setMBFilter(MB4, 0x151); //cell Temp
  Can0.setMBFilter(MB5, 0x251);
  Can0.setMBFilter(MB5, 0x351);
  Can0.setMBFilter(MB5, 0x451);
  //Can0.mailboxStatus();

  // myNex.writeNum("soc.val", 0);
  // myNex.writeNum("dcCurrent.val", 0);
  // myNex.writeNum("packVoltage.val", 0);
  // myNex.writeNum("acTemp.val", 0);
  // myNex.writeNum("rpm.val", 0);
  // myNex.writeNum("temp.val", 0);
  // myNex.writeNum("acCurrent.val", 0);
  // myNex.writeStr("page page0");

  pinMode(4, INPUT);
}

int hexToDec(char hex[]){
}



long long concat(int a, int b) {
} 

void canSniff(const CAN_message_t &msg) {
  inCanSniff = true;
  //Serial.print("MB "); Serial.print(msg.mb);
  //Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  //Serial.print("  LEN: "); Serial.print(msg.len);
  //Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  //Serial.print(" TS: "); Serial.print(msg.timestamp);
  //Serial.print(" ID: "); Serial.print(msg.id, HEX);
  //Serial.print(" Buffer: ");
  //for ( uint8_t i = 0; i < msg.len; i++ ) {
  //  Serial.print(msg.buf[i], HEX); Serial.print(" ");
  //} Serial.println(); 

  // Assign values to variables in mailbox 0 
  if (msg.mb == 0) {
    for ( uint8_t i = 0; i < msg.len; i++ ) {
      switch (i) {
        case 0:
        Pack_Current = msg.buf[i];
        break;
        case 2:
        Pack_Inst_Vol = msg.buf[i];
        //Serial.print(" Pack Inst. Voltage: "); Serial.print(Pack_Inst_Vol);
        break;
        case 3:
        Pack_Inst_Vol_Pt2 = msg.buf[i];
        //Serial.print("Pack part 2: "); Serial.print(Pack_Inst_Vol_Pt2);
        case 4:
        Pack_SOC = msg.buf[i];
        break;
        case 5:
        Relay_State = msg.buf[i];
        break;
      } 
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      inCanSniff = true;
    } 
      int Pack_Volt = concat(Pack_Inst_Vol, Pack_Inst_Vol_Pt2);
      Serial.println("Pack Current: "); Serial.print(Pack_Current);
      //myNex.writeNum("dcCurrent.val", Pack_Current/100);

      Serial.println(" Pack Inst. Voltage: "); Serial.print(Pack_Volt);
      //myNex.writeNum("packVoltage.val", Pack_Volt/100.0);

      Serial.println(" Pack SOC: "); Serial.print(Pack_SOC);
      //myNex.writeNum("soc.val", Pack_SOC);

      Serial.println(" Relay_State: "); Serial.print(Relay_State);
      Serial.println(); 

      // INSERT CODE HERE TO SEND THIS INFO. TO DASH DISPLAY
  }

  // Assign values to variables in mailbox 0 
  if (msg.mb == 1) {
    for ( uint8_t i = 0; i < msg.len; i++ ) {
      switch (i) {
        case 0:
        Pack_DCL = msg.buf[i];
        break;
        case 4:
        High_Temp = msg.buf[i];
        break;
        case 5:
        Low_Temp = msg.buf[i];
        break;
      }
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      inCanSniff = true;
    } Serial.print("Pack DCL: "); Serial.print(Pack_DCL);
      Serial.print(" High Temp: "); Serial.print(High_Temp);
      //myNex.writeNum("temp.val", High_Temp);
      Serial.print(" Low Temp: "); Serial.print(Low_Temp);
      Serial.println(); 
    }
       if (msg.mb == 2) {
    for ( uint8_t i = 0; i < msg.len; i++ ) {
      switch (i) {
        case 2:
        ERPM_Pt1 = msg.buf[i];
        //Serial.println(ERPM_Pt1);
        break;
        case 3:
        ERPM_Pt2 = msg.buf[i];
        break;
      }
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      inCanSniff = true;
    }
    int ERPM = concat(ERPM_Pt1, ERPM_Pt2);
    Serial.print("ERPM: "); Serial.print(ERPM);
    //myNex.writeNum("rpm.val", ERPM/10.0);
     Serial.println(); 
    }
        if (msg.mb == 3) {
    for ( uint8_t i = 0; i < msg.len; i++ ) {
      switch (i) {
        case 0:
        acCurrent_Pt1 = msg.buf[i];
        //Serial.println(ERPM_Pt1);
        break;
        case 1:
        acCurrent_Pt2 = msg.buf[i];
        break;
      }
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      inCanSniff = true;
    }
    int acCurrent = concat(acCurrent_Pt1, acCurrent_Pt2);
    Serial.print("AC Cuurent: "); Serial.print(acCurrent);
    //myNex.writeNum("acCurrent.val", acCurrent/10.0);
     Serial.println(); 
    }
        if (msg.mb == 4) {
    for ( uint8_t i = 0; i < msg.len; i++ ) {
      switch (i) {
        case 0:
        cellTemp_Pt1 = msg.buf[i];
        //Serial.println(ERPM_Pt1);
        break;
        case 1:
        cellTemp_Pt2 = msg.buf[i];
        break;
      }
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      inCanSniff = true;
    }
    int cellTemp = concat(cellTemp_Pt1, cellTemp_Pt2);
    Serial.print("Cell Temp: "); Serial.print(cellTemp);
    //myNex.writeNum("cellTemp.val", cellTemp/10.0);
     Serial.println(); 
    }
    if (msg.mb == 5) {
    // for ( uint8_t i = 0; i < msg.len; i++ ) {
    //   switch (i) {
    //     case 0:
    //     cellTemp_Pt1 = msg.buf[i];
    //     //Serial.println(ERPM_Pt1);
    //     break;
    //     case 1:
    //     cellTemp_Pt2 = msg.buf[i];
    //     break;
    //   }
      //Serial.print(msg.buf[i], HEX); Serial.print(" ");
      
     // inCanSniff = true;
   // }
    // myNex.writeNum("t13.bco", 63488); //turn error message to red
    // myNex.writeStr("t13.txt", "ERROR"); 
    // myNex.writeNum("packvWarning.pco", 65535);
    // myNex.writeStr("packvWarning.txt", "ERROR: Shutdown Circuit OFF!"); // Change t0 text to "Hello World"
    }
}

void loop() {
  inCanSniff = false;
  Can0.events();
  // if(!digitalRead(4)){
  //   Serial.println("Pin 4 is LOW");
  //   //Serial.println(myNex.currentPageId);
  //   if(pageNum == 0){//you are only allowed to go to the next page if there is an error
  //     // myNex.writeStr("page page1");
  //     // myNex.writeNum("t13.bco", 000000);
  //     // myNex.writeStr("t13.txt", "NO ERROR"); //turn errro message to red
      
  //     delay(70);
  //     pageNum = 1;
  //   } else if(pageNum == 1){
  //     //myNex.writeStr("page page0");
  //     pageNum = 0;
  //   } 
  //   delay(100); 
  // }
  delay(40);
  if(inCanSniff == false){
    // myNex.writeNum("soc.val", 0);
    // myNex.writeNum("dcCurrent.val", 0);
    // myNex.writeNum("packVoltage.val", 0);
    // myNex.writeNum("cellTemp.val", 0);
    // myNex.writeNum("rpm.val", 0);
    // myNex.writeNum("temp.val", 0);
    // myNex.writeNum("acCurrent.val", 0);
    //myNex.writeStr("page page0");
    //pageNum = 0;
  }
  //delay(50);
}

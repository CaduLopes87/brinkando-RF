#include <VirtualWire.h>

//===== Hardware Mapping ======//
#define TX_Pin 12

//===== Variables =====//
#define MaxBufferSize 64
byte TX_buffer[MaxBufferSize];

int countReceivedBytes = 0;

String receivedString = "vazio ainda";
int receivedInt;
//char receivedChar;

void setup() {
  Serial.begin(9600);

  vw_set_tx_pin(TX_Pin);
  vw_setup(4000);

}

void loop() {
//  clearBuffer();

  if(Serial.available()){
    // Read the data sent by Rapberry via serial
    byte receivedNumber = Serial.read();
    
    //Stores the received data in a buffer
    TX_buffer[countReceivedBytes] = receivedNumber;
    countReceivedBytes++;

    //Send the data when gets the start number (5)
    if(receivedNumber == 5){
      //send data twice      
      for(int i = 0; i < 2; i++){
        vw_send(TX_buffer, MaxBufferSize);
        vw_wait_tx();
        delay(1000);
      }

      int bytesReadQuantity = countReceivedBytes;
    
      //Print the read data  
      if (bytesReadQuantity > 0) { //verify if the buffer size is biggest than 0
        Serial.println("Read Data: ");
        for(int i = 0; i < bytesReadQuantity; i++){
          Serial.print("Byte ");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(TX_buffer[i]);
        }
      }
      clearBuffer();
    }    
  }
}

void clearBuffer(){
  for(int i = 0; i < MaxBufferSize; i++){
    TX_buffer[i] = 0;
    countReceivedBytes = 0;
  }
}

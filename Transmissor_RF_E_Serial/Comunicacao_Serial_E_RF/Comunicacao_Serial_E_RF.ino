#include <VirtualWire.h>

//===== Hardware Mapping ======//
#define TX_Pin 12

//===== Variables =====//
#define MaxBufferSize 64
byte TX_buffer[MaxBufferSize];

void setup() {
  Serial.begin(9600);

  vw_set_tx_pin(TX_Pin);
  vw_setup(4000);

}

void loop() {
  clearBuffer();

  if(Serial.available() > 0){
    // Read the data sent by Rapberry via serial
    int bytesReadQuantity = Serial.readBytes(TX_buffer, MaxBufferSize);
  
    //Check if the read data is correct  
    if (bytesReadQuantity > 0) { //verify if the buffer size is greater than 0
      Serial.println("Read Data: ");
      for(int i = 0; i < bytesReadQuantity; i++){
        Serial.print("Byte ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(TX_buffer[i]);
      }
    }
    //Envia os dados pela RF com duas tentativas automáticas    
    for(int i = 0; i < 2; i++){
      vw_send(TX_buffer, MaxBufferSize);
      vw_wait_tx();
      delay(1000);
    }
  }
}

void clearBuffer(){
  for(int i = 0; i < MaxBufferSize; i++){
    TX_buffer[i] = 0;
  }
}
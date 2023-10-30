#include <VirtualWire.h>

//===== Hardware Mapping =====//
#define RX_Pin 12

//===== Variables =====//
byte messageLength = VW_MAX_MESSAGE_LEN; //Maximum message length
byte message[VW_MAX_MESSAGE_LEN]; //buffer to store the sent data

void setup() {
  
  Serial.begin(9600);
  Serial.println("Waiting...");

  vw_set_rx_pin(RX_Pin);
  vw_setup(4000);
  vw_rx_start();
}

void loop() {
    
  if (vw_get_message(message, &messageLength)){

    Serial.println("Message:"); 

    for(int i = 0; i < messageLength; i++){
      if(message[i] != 0) {
        Serial.print("byte "); 
        Serial.print(i); 
        Serial.print(": "); 
        Serial.println(message[i]); 
      }
    }
  }
}

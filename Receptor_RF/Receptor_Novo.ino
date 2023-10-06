#include <VirtualWire.h>

//=====Mapeamento de Hardware=====//

#define led_pin 7

//===== Variáveis Globais =====//
byte message[VW_MAX_MESSAGE_LEN]; //buffer para armazenar a mensagem
byte messageLength = VW_MAX_MESSAGE_LEN; //Tamanho da mensagem

void setup() {
  
  Serial.begin(9600);
  Serial.println("Iniciando: ");

  pinMode(led_pin, OUTPUT);

  vw_set_rx_pin(12);
  vw_setup(4000);
  vw_rx_start();
}

void loop() {

  //Serial.println(".");
    
  if (vw_get_message(message, &messageLength)){

    Serial.println("Mensagem Recebida: ");
    Serial.print("Mensagem: ");
    Serial.println(message[0]); 

    analogWrite(led_pin, message[0]);    
    Serial.print("Número: ");
    Serial.println(message[1]);
    
    /*switch(message[0]){

      case 0:
        digitalWrite(led_pin, LOW);
      case 1:
        digitalWrite(led_pin, HIGH);
      break;      
      }*/
      delay(200);
    }
}

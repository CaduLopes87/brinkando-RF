#include <VirtualWire.h>

//=====Mapeamento de Hardware======//
#define Size 2
#define pinPot A0

//=====Variáveis Globais=====//
byte TX_buffer[2];
int leitura;


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando:");

  vw_set_tx_pin(12);
  vw_setup(4000);

  
  //TX_buffer[0] = 0;
  TX_buffer[1] = 1;

}

void loop() {

  TX_buffer[0] = map(analogRead(pinPot), 0 , 1023 , 0 , 255);
  
  Serial.println("Mensagem a ser enviada: ");
  
  Serial.print("Leitura do Potenciômetro: ");
  Serial.println(TX_buffer[0]);
  Serial.print("Ímpar: ");
  Serial.println(TX_buffer[1]);

  vw_send(TX_buffer, Size);
  vw_wait_tx();

  //TX_buffer[0] = TX_buffer[0] + 2;
  TX_buffer[1] = TX_buffer[1] + 2;

  //delay(2000);

}

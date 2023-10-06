#include <VirtualWire.h>

//=====Mapeamento de Hardware======//
#define Size 2

//=====Variáveis Globais=====//
byte TX_buffer[2];
int leitura;


void setup() {
  Serial.begin(9600);

  vw_set_tx_pin(12);
  vw_setup(4000);

}

void loop() {

  if(Serial.available()){
    TX_buffer[0] = Serial.read();
  }

  TX_buffer[1] = 2;

  vw_send(TX_buffer, Size);
  vw_wait_tx();
}

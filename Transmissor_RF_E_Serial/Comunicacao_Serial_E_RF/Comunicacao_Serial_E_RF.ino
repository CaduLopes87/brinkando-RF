#include <VirtualWire.h>

//=====Mapeamento de Hardware======//
// #define Size 2

//=====Variáveis Globais=====//
int bufferSize = 20;
byte TX_buffer[bufferSize];

void setup() {
  Serial.begin(9600);

  vw_set_tx_pin(12);
  vw_setup(4000);

}

void loop() {

  if(Serial.available()){
     // Lê os dados da Raspberry Pi e armazena no buffer
    int bytesRead = Serial.readBytes(TX_buffer, BufferSize);
    // Verifica se os dados foram lidos corretamente e os envia pela RF
    if (bytesRead > 0) {
    vw_send(TX_buffer, bytesRead); // Envia os dados pela RF
    vw_wait_tx();
  }
  }
}

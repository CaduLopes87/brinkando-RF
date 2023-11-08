/* ========================================================================================================

   Code based on Eng. Wagner Rambo project
   
======================================================================================================== */

// ========================================================================================================
// --- Hardware Mapping to motor 1 ---
#define    M1_encoder_C1   2                     //Conexão C1 do encoder amarelo
#define    M1_encoder_C2   4                     //Conexão C2 do encoder verde
#define    M1_pwm_out      5                     //Saída pwm para controle de velocida do motor 1
#define    M1_motor1       6                     //Controle In1 do driver L298N
#define    M1_motor2       7                     //Controle In2 do driver L298N

// --- Hardware Mapping to motor 2 ---
#define    M2_encoder_C1   8                     //Conexão C1 do encoder amarelo
#define    M2_encoder_C2   9                     //Conexão C2 do encoder verde
#define    M2_pwm_out      3                     //Saída pwm para controle de velocida do motor 2
#define    M2_motor1       10                     //Controle In1 do driver L298N
#define    M2_motor2       11                    //Controle In2 do driver L298N

// ========================================================================================================
// --- Global Variables ---
byte      Encoder_C1Last;
int       M1_pulse_number,
          step = 0,
          M1_pwm_value = 80;
          
boolean direction_m;

byte      M2_Encoder_C1Last;
int       M2_pulse_number,
          M2_pwm_value = 80;
          
boolean M2_direction_m;


// ========================================================================================================
// --- initial setup ---
void setup()
{
  Serial.begin(115200);
 
  pinMode(M1_encoder_C1,  INPUT);                //Set C1 to read the encoder
  pinMode(M1_encoder_C2,  INPUT);                //Set C2 to read the encoder
  pinMode(M1_motor1,     OUTPUT);                //Set the first output to motor control (in1 of driver)
  pinMode(M1_motor2,     OUTPUT);                //Set the second output to motor control (in3 of driver)

  pinMode(M2_encoder_C1,  INPUT);                //Set C1 to read the encoder
  pinMode(M2_encoder_C2,  INPUT);                //Set C2 to read the encoder
  pinMode(M2_motor1,     OUTPUT);                //Set the first output to motor control (in1 of driver)
  pinMode(M2_motor2,     OUTPUT);                //Set the second output to motor control (in3 of driver)
 
  
  attachInterrupt(0, M1_count_pulses, CHANGE);      //External interrupt 0 in state change
  attachInterrupt(0, M2_count_pulses, CHANGE);      //
    
} //end setup

// ========================================================================================================
void loop()
{
   //motor_control_stop();                           //chama função para controle do motor
   //delay(2000);
   motor_control_right();                           //chama função para controle do motor
   delay(2000);                                   //taxa de atualização
   motor_control_front();                           //chama função para controle do motor
   delay(2000);
   motor_control_left();
   delay(2000);
   motor_control_turn();
   delay(2000);
} //end loop

// ========================================================================================================
// --- Functions to move Motor ---

//Function to get paramaters with the state of each motor and one to show the current direction
void active_motor(int M1_motor1_state, int M1_motor2_state, int M2_motor1_state, int M2_motor2_state, String direction) {
  digitalWrite(M1_motor1, M1_motor1_state);                //Changes the bit control of each motor
  digitalWrite(M1_motor2, M1_motor2_state);                //
  digitalWrite(M2_motor1, M2_motor1_state);                //
  digitalWrite(M2_motor2, M2_motor2_state);                //
  Serial.print("Direction: ");
  Serial.println(direction); //print the direction
  M1_pwm_value = 80; //Variable to control the speed of the motor
  M2_pwm_value = 80; //
  analogWrite(M1_pwm_out, M1_pwm_value);          //Generates a proporcional PWM at the motor
  analogWrite(M2_pwm_out, M2_pwm_value);          //
}

void show_pulse_number() {
    Serial.print("Motor 1 pulse number: ");             
    Serial.print(M1_pulse_number);
    Serial.print("Motor 2 pulse number: ");
    Serial.print(M2_pulse_number);
}

void restart_pulse_number(){
  M1_pulse_number = 0x00;
  M2_pulse_number = 0x00;
}

void motor_control_right()
{  
  while (step <= 200)
  {
    show_pulse_number();
    active_motor(LOW, HIGH, HIGH, LOW, "right");
    step++;
    //end if step > 200

    /*
    //Apagar Linhas comentadas após teste
    digitalWrite(M1_motor1, LOW);                //Desliga bit de controle M1_motor1 do M1
    digitalWrite(M1_motor2, HIGH);               //Liga bit de controle M1_motor2 do M1
    digitalWrite(M2_motor1, HIGH);             //Liga bit de controle M1_motor1 do M2
    digitalWrite(M2_motor2, LOW);               //Desliga bit de controle M1_motor2 do M2
    Serial.println(" Sentido: direita"); //Imprime
    M1_pwm_value = 80;
    M2_pwm_value = 80;
    analogWrite(M1_pwm_out, M1_pwm_value);                //gera pwm proporcional
    analogWrite(M2_pwm_out, M2_pwm_value);          //gera pwm proporcional
    */

    restart_pulse_number();
  }
  motor_control_stop();                        //stop the car bot after move
} //end rigth move

void motor_control_left()
{  
  while (step <= 200)                             //step maior ou igual a 512? (metade do valor de 10 bits 1024)
  { 
    show_pulse_number();
    active_motor(HIGH, LOW, LOW, HIGH, "Left");
    step++;
    //end if step > 200

    /*
    //Apagar Linhas comentadas após teste
    digitalWrite(M1_motor1, HIGH);                //Liga bit de controle M1_motor1 do M1
    digitalWrite(M1_motor2, LOW);                 //Desliga bit de controle M1_motor2 do M1
    digitalWrite(M2_motor1, LOW);              //Desliga bit de controle M1_motor1 do M2
    digitalWrite(M2_motor2, HIGH);             //Liga bit de controle M1_motor2 do M2
    Serial.println(" Sentido: Esquerda");       //Imprime
    M1_pwm_value = 80;
    M2_pwm_value = 80;
    analogWrite(M1_pwm_out, M1_pwm_value);                //gera pwm proporcional
    analogWrite(M2_pwm_out, M2_pwm_value);          //gera pwm proporcional
    */

    restart_pulse_number();  
  }
  motor_control_stop();                        //stop the car bot after move
} //end left move

void motor_control_front()
{ 
  while (step <= 200)                             //step maior ou igual a 512? (metade do valor de 10 bits 1024)
  {  
    show_pulse_number();
    active_motor(LOW, HIGH, LOW, HIGH, "Front");
    step++;
    //end if step > 200

    /*
    //Apagar Linhas comentadas após teste
    digitalWrite(M1_motor1, LOW);                 //Desliga bit de controle M1_motor1 do M1
    digitalWrite(M1_motor2, HIGH);                //Liga bit de controle M1_motor2 do M1
    digitalWrite(M2_motor1, LOW);              //Desliga bit de controle M1_motor1 do M2
    digitalWrite(M2_motor2, HIGH);             //Liga bit de controle M1_motor2 do M2
    Serial.println(" Sentido: Frente");       //Imprime
    M1_pwm_value = 80;
    M2_pwm_value = 80;
    analogWrite(M1_pwm_out, M1_pwm_value);                //gera pwm proporcional
    analogWrite(M2_pwm_out, M2_pwm_value);          //gera pwm proporcional
   //end if step
    */
    restart_pulse_number();
  }
  motor_control_stop();                        //stop the car bot after move
} //end front move

void motor_control_turn()
{  
  while (step <= 250)                             //step maior ou igual a 512? (metade do valor de 10 bits 1024)
  {
    show_pulse_number();
    active_motor(HIGH, LOW, LOW, HIGH, "Turn");
    step++;
    //end if step > 250

    //Apagar Linhas comentadas após teste
    /*
    digitalWrite(M1_motor1, HIGH);                //Liga bit de controle M1_motor1 do M1
    digitalWrite(M1_motor2, LOW);                 //Desliga bit de controle M1_motor2 do M1
    digitalWrite(M2_motor1, LOW);              //Liga bit de controle M1_motor1 do M2
    digitalWrite(M2_motor2, HIGH);             //Desliga bit de controle M1_motor2 do M2
    Serial.println(" Sentido: Volta");       //Imprime
    M1_pwm_value = 80;
    M2_pwm_value = 80;
    analogWrite(M1_pwm_out, M1_pwm_value);                //gera pwm proporcional
    analogWrite(M2_pwm_out, M2_pwm_value);          //gera pwm proporcional
   //end if step
    */
    restart_pulse_number();
  }
  motor_control_stop();                        //stop the car bot after move
} //end motor_control Volta

void motor_control_stop()
{
  show_pulse_number();
  active_motor(LOW, LOW, LOW, LOW, "Stop");
  step = 0; //set zero to the step counter 
  
  //Apagar Linhas comentadas após teste
  /*                                          
  digitalWrite(M1_motor1, LOW);                 //Desliga bit de controle M1_motor1 do M1
  digitalWrite(M2_motor1, LOW);              //Desliga bit de controle M1_motor1 do M2
  digitalWrite(M1_motor2, LOW);                 //Desliga bit de controle M1_motor2 do M1
  digitalWrite(M2_motor2, LOW);              //Desliga bit de controle M1_motor2 do M2
  Serial.println(" Sentido: Parado");        //Imprime
  M1_pwm_value = 0;
  M2_pwm_value = 0;
  analogWrite(M1_pwm_out, M1_pwm_value);                //gera pwm proporcional
  analogWrite(M2_pwm_out, M2_pwm_value);          //gera pwm proporcional
  */

} //end stop function

// ========================================================================================================
// --- Function to count the encoders pulses ---
// 
// *baseada no artigo do site http://www.arduinoecia.com.br/2016/10/motor-dc-com-encoder-arduino.html
//
//
void M1_count_pulses()
{
  int M1_Lstate = digitalRead(M1_encoder_C1);       //Lê estado de M1_encoder_C1 e armazena em M1_Lstate
  
  if(!Encoder_C1Last && M1_Lstate)               //Encoder_C1Last igual a zero e M1_Lstate diferente de zero?
  {                                           //Sim...
    int val = digitalRead(M1_encoder_C2);        //Lê estado de M1_encoder_C2 e armazena em M1_val

    if(!val && direction_m) direction_m = false;      //Sentido reverso
    
    else if(val && !direction_m) direction_m = true;  //Sentido direto
  } //end if 
 
  Encoder_C1Last = M1_Lstate;                    //Encoder_C1Last recebe o valor antigo
  
  if(!direction_m)  M1_pulse_number++;           //incrementa número do pulso se direction limpa
  else              M1_pulse_number--;           //senão decrementa    
} //end M1_count_pulses

void M2_count_pulses()
{
  int M2_Lstate = digitalRead(M2_encoder_C1);       //Lê estado de M1_encoder_C1 e armazena em M2_Lstate
  
  if(!M2_Encoder_C1Last && M2_Lstate)               //Encoder_C1Last igual a zero e M2_Lstate diferente de zero?
  {                                           //Sim...
    int val2 = digitalRead(M2_encoder_C2);        //Lê estado de M1_encoder_C2 e armazena em M2_val
    
    if(!val2 && M2_direction_m) M2_direction_m = false;      //Sentido reverso
    
    else if(val2 && !M2_direction_m) M2_direction_m = true;  //Sentido direto
    
  } //end if 
 
  M2_Encoder_C1Last = M2_Lstate;                    //Encoder_C1Last recebe o valor antigo

  if(!M2_direction_m)  M2_pulse_number++;           //incrementa número do pulso se direction limpa
  else                 M2_pulse_number--;           //senão decrementa
} //end M2_count_pulses






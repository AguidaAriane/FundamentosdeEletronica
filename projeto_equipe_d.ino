/*O código simula um semáforo simples, controlando as suas diferentes fases com base em temporizadores. Além disso, possui um botão para os pedestres que ao apertar permite a travessia mais rápida. As fases do semáforo incluem verde, amarelo e vermelho para carros, e verde e vermelho para os pedestres.

Foi criada um função chamada travessiaDoPedestre, tem o objetivo de controlar a passagem do pedestre quando o mesmo pressiona o botão.

Parâmetros de entradas: - PUSHBUTTON: é um botão que possui a finalidade de auxiliar a passagem do pedestre quando pressionado.

Parâmetros de Saída: - LED_VERDE: é uma saída digital que retorna um valor HIGH OU LOW, quando o led estiver HIGH os carros poderão passar.
                     - LED_AMARELO : é uma saída digital que retorna um valor HIGH OU LOW, quando o led estiver HIGH os carros devem reduzir a velocidade e se preparar para parar.
                     - LED_VERMELHO: é uma saída digital que retorna um valor HIGH OU LOW, quando o led estiver HIGH os carros devem parar permitindo a passagem dos pedestres.
                     - BUZZER: é uma saída digital que emiti um sinal sonoro nos últimos 10 segundos do sinal vermelho para carros alertando os pedestres de que a travessia está prestes a terminar.
                     - LED_VERDE_PEDESTRE: é uma saída digital que retorna um valor HIGH OU LOW, quando o led estiver HIGH os pedestres poderão passar.
                     - LED_VERMELHO_PEDESTRE: é uma saída digital que retorna um valor HIGH OU LOW, quando o led estiver HIGH os pedestres não devem fazer a travessia.
*/

#define LED_VERDE 2              
#define LED_AMARELO 3            
#define LED_VERMELHO 4           
#define BUZZER 5                 
#define PUSHBUTTON 7             
#define LED_VERDE_PEDESTRE 8     
#define LED_VERMELHO_PEDESTRE 10 

             
unsigned long ultimoTempoVerde = 0; // Tempo do último ciclo verde para carros
unsigned long tempoPushbutton = 0; // Tempo do pressionamento do botão
bool solicitacaoPedestre = false;  // Indica se há uma solicitação de travessia



void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(PUSHBUTTON, INPUT_PULLUP);
  pinMode(LED_VERDE_PEDESTRE, OUTPUT);
  pinMode(LED_VERMELHO_PEDESTRE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  unsigned long tempoCorrido = millis();

  // Fase verde para carros (90 segundos)
  if (tempoCorrido - ultimoTempoVerde < 90000) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO_PEDESTRE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE_PEDESTRE, LOW);
    

    // Verificar se o botão de pedestres foi pressionado
    if (digitalRead(PUSHBUTTON) == LOW && !solicitacaoPedestre ) {
      tempoPushbutton = tempoCorrido;
      solicitacaoPedestre  = true;
     
    }

    // Se a solicitação de travessia foi feita e passaram-se 20 segundos
    if (solicitacaoPedestre  && tempoCorrido - tempoPushbutton >= 20000) {
      travessiaDoPedestre(); // Inicia a sequência de travessia
      ultimoTempoVerde = millis(); // Atualiza o tempo do último ciclo verde para carros
      solicitacaoPedestre  = false; // Reseta a solicitação
    }
    
   

  } else if (tempoCorrido - ultimoTempoVerde < 96000) {
    // Fase amarela para carros (6 segundos)
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    
    
  } else if (tempoCorrido - ultimoTempoVerde < 186000) {
    // Fase vermelha para carros e verde para pedestres (90 segundos)
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERMELHO_PEDESTRE, LOW);
    digitalWrite(LED_VERDE_PEDESTRE, HIGH);
    

    // Nos últimos 10 segundos da fase vermelha, emiti sinal sonoro para pedestres
    if (tempoCorrido - ultimoTempoVerde == 176000) {
   
      for (int i = 1; i <= 4; i++) {
        tone(BUZZER, 329, 1000);
        delay(1500);
      }
      
      
    }
    
  } else {
    // Reinicia para a próxima fase verde
    ultimoTempoVerde = millis();
    
  }
}

void travessiaDoPedestre() {
  // Ativa led amarelo para carros por 6 segundos
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, HIGH);
  delay(6000);

  // Ativa vermelho para carros e verde para pedestres
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_VERMELHO_PEDESTRE, LOW);
  digitalWrite(LED_VERDE_PEDESTRE, HIGH);
  

  delay(25000); // Luz verde para pedestres por 25 segundos

  // Nos últimos 10 segundos da luz verde para pedestres, tocar o Buzzer
  for (int i = 1; i <= 4; i++) {
    tone(BUZZER, 329, 1000);
    delay(1500);
  }
  delay(4000);
  

  // Reseta o semáforo após a travessia
  digitalWrite(LED_VERDE_PEDESTRE, LOW);
  digitalWrite(LED_VERMELHO_PEDESTRE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
}
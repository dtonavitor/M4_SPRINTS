//porta dos leds
int LED1 = 2;
int LED2 = 1;
int LED3 = 4;
int LED4 = 5;

//porta dos botões
int botao1 = 7;
int botao2 = 6;

//porta do buzzer
int buzzer = 10;

//porta do sensor
int sensor = 3;

int valorSensor = 0;

//vetor para armazenar os valores lidos pelo ldr
int vetorMedidas[100];
//posição no vetor acima
int posicaoMedidas = 0;
//vetor para armazenar cada dígito do valor em binário
int valorBinario[4];
//tamanho preenchido do vetor com os valores armazenados
int notasVetor = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);

  pinMode(sensor, INPUT);

  Serial.begin(9600);
}

void loop() {

  //botão pressionado
  if (digitalRead(botao1) == LOW) {
    //leitura do sensor
    valorSensor = analogRead(sensor);
    //conversão do valor para o intervalo de 0-15
    valorSensor = (valorSensor * 15) / 4095;
    Serial.print ("Leitura atual do sensor: ");
    Serial.println(valorSensor);
    //armazena no vetor o valor lido na posição disponível
    vetorMedidas[posicaoMedidas] = valorSensor;
    Serial.print ("Valor armazenado no vetor: ");
    Serial.println(vetorMedidas[posicaoMedidas]);

    // converte o valor em binário
    binario(valorBinario, vetorMedidas[posicaoMedidas]);
    
    //acende os leds de acordo com o valor em binário
    acendeLed(valorBinario);
    
    //toca o som específico para o valor do sensor
    tocarBuzzer(vetorMedidas[posicaoMedidas]);
    //apaga os leds
    apagaLed();

    // próxima posição livre no vetor
    posicaoMedidas += 1;
    //número de dados no vetor
    notasVetor += 1;
  }
  
  //botão 2 pressionado
  if (digitalRead(botao2) == LOW) {
    for(int i = 0; i < notasVetor; i++)
    {
      // converte em binário todos os valores do vetor
      binario(valorBinario, vetorMedidas[i]);

      acendeLed(valorBinario);
      tocarBuzzer(vetorMedidas[i]);
      apagaLed();
    }
    for(int i = 0; i < notasVetor; i++)
    {
      vetorMedidas[i] = 0;
    }
    notasVetor = 0;

  }
}

void apagaLed(void)
{
  delay(700);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void acendeLed(int *valorBinario)
//acendendo os leds (dígito 0 - desligado; dígito 1 - ligado)
{
  if (valorBinario[0] == 0) {
    digitalWrite(LED1, LOW);
  }
  else {
    digitalWrite(LED1, HIGH);
  }


  if (valorBinario[1] == 0) {
    digitalWrite(LED2, LOW);
  }
  else {
    digitalWrite(LED2, HIGH);
  }


  if (valorBinario[2] == 0) {
    digitalWrite(LED3, LOW);
  }
  else {
    digitalWrite(LED3, HIGH);
  }


  if (valorBinario[3] == 0) {
    digitalWrite(LED4, LOW);
  }
  else {
    digitalWrite(LED4, HIGH);
  }
}

void binario(int *vetor, int valor)
{
  int i = 4;
  while (i > 0)   
  {   
    i--;
    vetor[i] = valor % 2; 
    valor = valor/2;
  }
  
}

void tocarBuzzer(int valorSensor) {
  //um som diferente para cada valor possível
  switch(valorSensor) {
    case 1:
      tom(buzzer, 600, 500);
    break;
    case 2:
      tom(buzzer, 700, 500);
    break;
    case 3:
      tom(buzzer, 800, 500);
    break;
    case 4:
      tom(buzzer, 900, 500);
    break;
    case 5:
      tom(buzzer, 1000, 500);
    break;
    case 6:
      tom(buzzer, 1100, 500);
    break;
    case 7:
      tom(buzzer, 1200, 500);
    break;
    case 8:
      tom(buzzer, 1300, 500);
    break;
    case 9:
      tom(buzzer, 1400, 500);
    break;
    case 10:
      tom(buzzer, 1500, 500);
    break;
    case 11:
      tom(buzzer, 1600, 500);
    break;
    case 12:
      tom(buzzer, 1700, 500);
    break;
    case 13:
      tom(buzzer, 1800, 500);
    break;
    case 14:
      tom(buzzer, 1900, 500);
    break;
    case 15:
      tom(buzzer, 2000, 500);
    break;
    default:
      tom(buzzer, 2100, 500);
  }
}


void tom(char buzzer, int frequencia, int duracao){
  float periodo = 1000.0/frequencia; //Periodo em ms
  for (int i = 0; i< duracao/(periodo); i++)
  {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(periodo*500); //Metade do periodo em ms
    digitalWrite(buzzer, LOW);
    delayMicroseconds(periodo*500);
  }
}

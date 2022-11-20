#define PERIODO_50HZ      20     // 20ms ou 1/50
#define MAXBITSRESOLUCAO  1024   // para resulucao de 10bits, o maximo valor do DUTY cycle
#define INICIODUTY_MS     0.9    // o ponto, em ms onde o angulo é -90
#define FIMDUTY_MS        2.5    // o ponto em ms onde o angulo é 90
#define FACTORDEFAULT     0.05   // menor pedaço de movimento em MS
#define CANALDEFAULT      0
#define FREQDEFAULT       50
#define RESOLUCAO         10
#define DELTADEFAULT      2
#define INICIODEFAULT     40
#define FIMDEFAULT        120
#define TEMPOPASSO        50 //tempo para cada mudança de passo em ms

class Servo9G{
  private:
    int canalServo = CANALDEFAULT;
    int freqServo = FREQDEFAULT;
    int resolucaoServo = RESOLUCAO;
    int pinSERVO = 16;
    int delta  = DELTADEFAULT;   // pedaços a cada fração de ms
    int inicio = INICIODEFAULT;  //==> Corresponde aos passos do ponto de 1ms
    int fim    = FIMDEFAULT; //==> Corresponde aos passos do ponto de 2ms
    int posAtual = INICIODEFAULT; // posicao (Em valor de DUTY cyle (ms) atual do motor)
    int tempoPasso = TEMPOPASSO;
    void calculaFatores(float factor){
      int inicioFactor = (float)INICIODUTY_MS/(float)factor;
      int fimFactor = (float)FIMDUTY_MS/(float)factor;
      delta = (int)((float)MAXBITSRESOLUCAO/(float)PERIODO_50HZ) * factor ;// pedaços por  de ms
      inicio = delta *inicioFactor ; //==> Corresponde a 1ms
      fim = delta * fimFactor;// ==> Corresponde a 2ms
      Serial.printf("Fatores calculados para o servo:\n");
      Serial.printf("delta=%i inicio=%i fim=%i canal=%i pino=%i factor=%f\n",delta,inicio,fim,canalServo,pinSERVO,factor);
    }
  public:
    Servo9G(int canal,int pino){
      canalServo = canal;
      pinSERVO = pino;
      pinMode(pinSERVO,OUTPUT);
      ledcAttachPin(pinSERVO, canalServo);
      ledcSetup(canalServo, freqServo, resolucaoServo);
      Serial.printf("Servo9G(%i, %i);\n",canalServo,pino);
    }
    
    void varre(int nrv,float factor=FACTORDEFAULT){
      calculaFatores(factor);
      posiciona(0);
      for(int j=0; j < nrv ; j++){
        for(int i = inicio ; i<fim; i+=delta){
          ledcWrite(canalServo, i);
          posAtual = i;
          delay(tempoPasso);
        }
        for(int i = fim ; i>inicio; i-=delta){
          ledcWrite(canalServo, i);
          posAtual = i;
          delay(tempoPasso);
        }
      }
    }
    void posiciona(int anguloPercentual){
      int dutyPos = inicio + ((float)(fim - inicio)) * (float)anguloPercentual / 100;

      if(dutyPos > posAtual){ // vai pra frente
        for(int j = posAtual ; j<=dutyPos; j+=delta){
          ledcWrite(canalServo, j);
          delay(tempoPasso);
        }
      }else{ // vai pra trás
        for(int j = posAtual ; j>=dutyPos; j-=delta){
          ledcWrite(canalServo, j);
          delay(tempoPasso);
        }
      }
      posAtual = dutyPos;
    }

};
Servo9G *servo1 = NULL;


void setup() {
  Serial.begin(115200);
}



void loop() {
  servo1 = new Servo9G(0,16);
  servo1->varre(2);

  servo1->posiciona(20);

  delay(2000);
  servo1->posiciona(50);

  delay(2000);
  servo1->posiciona(75);

  delay(2000);
  servo1->posiciona(100);

  delay(2000);
  servo1->posiciona(50);

  delete servo1;
  delay(3000);

}



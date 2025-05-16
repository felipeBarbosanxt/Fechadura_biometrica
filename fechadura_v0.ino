// ===== INCLUDES E DEFINES =====

#include <WiFi.h>
#include <Keypad.h>

// ===== VARIÁVEIS GLOBAIS =====

#define PIN_SOLENOIDE 26
#define TIME_SOLENOIDE 1000

const byte ROWS = 4; // quatro linhas
const byte COLS = 4; // quatro colunas

bool portaTrancada = true;

const String correctPassword = "1234";
String passwordTyped = "";

char* SSID = "";
char* PASS = "";

// ===== CONFIGURAÇÃO DO TECLADO =====

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// GPIOs do ESP
byte rowPins[ROWS] = {23, 22, 21, 19}; // Linhas: L1-L4
byte colPins[COLS] = {18, 5, 17, 16};  // Colunas: C1-C4

// ===== OBJETOS =====

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ===== FUNÇÕES AUXILIARES =====

// Inicia a conexão com Wifi
bool initWifi(){
  WiFi.begin(SSID, PASS);

  for(int i = 0; WiFi.status() !=  WL_CONNECTED && i < 60; i++){
    delay(500);
    Serial.println(".");
  }
  if(WiFi.status() == WL_CONNECTED ){
    Serial.println("\nWifi conectado");
    Serial.println("\ Endereço de IP" );
    Serial.println(WiFi.localIP());
    return true;
  }else{
    Serial.println("\nFalha ao conectar ao WiFi.");
    Serial.print("Status: ");
    Serial.println(WiFi.status());
    return false;
  }
}

// Inicializa o pino da solenoide desligada(fechada)
void initPinSolenoide()
{
  pinMode(PIN_SOLENOIDE, OUTPUT);
}

// Função de abrir e fechar solenoide
void trancarPorta() {
  digitalWrite(PIN_SOLENOIDE, HIGH);  // energiza a solenoide = tranca
  portaTrancada = true;
  Serial.println("Porta trancada.");
}

void destrancarPorta() {
  digitalWrite(PIN_SOLENOIDE, LOW);   // desenergiza = destranca
  portaTrancada = false;
  Serial.println("Porta destrancada.");
}

// Função para digitar no teclado e fazer verificação da senha, se correta a solenoide abre, se não a senha escrita é apagada e ai a tentativa pode ser feita novamente.
void keypadProcess() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Tecla pressionada: ");
    Serial.println(key);

    // A letra B inicia o processo de TRANCAR a porta (caso ela esteja destrancada)
    if (key == 'B') {
      if (!portaTrancada) {
        Serial.println("Modo de trancamento ativado. Digite a senha e confirme com '#'.");
        passwordTyped = "";  // Prepara nova senha
      } else {
        Serial.println("A porta já está trancada.");
      }
      return;
    }

    // '*' limpa a senha
    if (key == '*') {
      passwordTyped = "";
      Serial.println("Senha apagada.");
      return;
    }

    // '#' confirma a senha
    if (key == '#') {
      if (passwordTyped == correctPassword) {
        if (portaTrancada) {
          Serial.println("Senha correta. Destrancando porta...");
          destrancarPorta();
        } else {
          Serial.println("Senha correta. Trancando porta...");
          trancarPorta();
        }
      } else {
        Serial.println("Senha incorreta.");
      }
      passwordTyped = "";  // Limpa após tentativa
      return;
    }

    // Adiciona dígito à senha digitada
    passwordTyped += key;
  }
}


// ===== SETUP E LOOP =====

void setup() 
{
  Serial.begin(115200);
  // initWifi();
  initPinSolenoide();
  trancarPorta();  // Estado inicial

}

void loop() 
{
  // put your main code here, to run repeatedly:
  keypadProcess();

}

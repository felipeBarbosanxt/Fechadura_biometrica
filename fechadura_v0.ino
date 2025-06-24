// ===== INCLUDES E DEFINES =====
#include <WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN  5    // Slave Select do RFID (pode ser outro pino livre)
#define RST_PIN 4    // Reset do RFID
#define PIN_SOLENOIDE 15 // Pino da fechadaura

// ===== VARIÁVEIS GLOBAIS =====
bool portaTrancada = true;

unsigned long tempoMensagem = 0;
bool mostrandoMensagem = false;

// ===== SEGURANÇA =====
const String correctPassword = "1234";
String passwordTyped = "";
String authorizedUIDs[] = {"23688C14", "11223344"};

// ===== WIFI E MQTT =====
int tentativasConexao = 0;
bool modoOffline = false; // Novo: indica se o sistema está operando offline
char* SSID = "...";
char* PASS = "505283fb";
const char* MQTT_BROKER = "192.168.255.66";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "admin";
const char* MQTT_PASS = "lMsshXb22";
const char* MQTT_CLIENT_ID = "esp32_fechadura";
const char* COMMAND_TOPIC = "home/status";
const char* STATE_TOPIC = "home/status/state";

// ===== OBJETOS =====
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço pode variar: 0x27 ou 0x3F

// ===== CONFIGURAÇÃO DO TECLADO =====
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 25, 14}; // ROWs
byte colPins[COLS] = {27, 26, 13, 12}; // COLs

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ===== FUNÇÕES AUXILIARES =====
void initWifi() {
  Serial.print("Conectando-se ao WiFi");
  WiFi.begin(SSID, PASS);
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 10) {
    delay(1000);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado com sucesso!");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao conectar no WiFi. Entrando em modo offline.");
    modoOffline = true;
  }
}

void initMqtt() {
  if (!modoOffline) {
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback(callback);
  }
}

void reconnectMqtt() {
  if (modoOffline) return;

  while (!mqttClient.connected() && tentativasConexao < 10) {
    Serial.print("Tentando conectar ao MQTT...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("Conectado ao broker!");
      mqttClient.subscribe(COMMAND_TOPIC);
      tentativasConexao = 0; // Reset em caso de sucesso
    } else {
      tentativasConexao++;
      Serial.print("Falha, tentativas: ");
      Serial.println(tentativasConexao);
      delay(5000);
    }
  }

  if (tentativasConexao >= 10) {
    Serial.println("Falha nas tentativas de conexão MQTT. Entrando em modo offline.");
    modoOffline = true;
  }
}

// ===== COMUNICAÇÃO COM MQTT =====
void publishEstado() {
  if (modoOffline) return; // Evita tentativa de publicar sem conexão
  if (portaTrancada) {
    mqttClient.publish(STATE_TOPIC, "LOCK");
  } else {
    mqttClient.publish(STATE_TOPIC, "UNLOCK");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.print("Comando recebido via MQTT: ");
  Serial.println(msg);

  if (msg == "LOCK") {
    openSolenoide();
    mostrarMensagemTemporaria("Trancando Porta");
  } else if (msg == "UNLOCK") {
    closeSolenoide();
    mostrarMensagemTemporaria("Acesso Liberado");
  }
}

// ===== SOLENOIDE =====
void initPinSolenoide() {
  pinMode(PIN_SOLENOIDE, OUTPUT);
}

void openSolenoide() {
  digitalWrite(PIN_SOLENOIDE, LOW);
  portaTrancada = true;
  Serial.println("Porta trancada.");
  publishEstado();
}

void closeSolenoide() {
  digitalWrite(PIN_SOLENOIDE, HIGH);
  portaTrancada = false;
  Serial.println("Porta destrancada.");
  publishEstado();
}

// // ===== PROCESSAMENTO DE ABERTURA E FECHAMENTO DA FECHADURA =====
void keypadProcess() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Tecla pressionada: ");
    Serial.println(key);

    if (passwordTyped.length() == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Senha:");
    }

    // if (key == 'B') {
    //   if (!portaTrancada) {
    //     Serial.println("Modo de trancamento ativado. Digite a senha e confirme com '#'...");
    //     passwordTyped = "";
    //     lcd.clear();
    //   } else {
    //     Serial.println("A porta já está trancada.");
    //   }
    //   return;
    // }

    if (key == '*') {
      passwordTyped = "";
      lcd.clear();
      Serial.println("Senha apagada.");
      return;
    }

    if (key == '#') {
      if (passwordTyped == correctPassword) {
        if (portaTrancada) {
          Serial.println("Senha correta. Destrancando porta...");
          closeSolenoide();
          mostrarMensagemTemporaria("Acesso Liberado");
        } else {
          Serial.println("Senha correta. Trancando porta...");
          openSolenoide();
          mostrarMensagemTemporaria("Trancando Porta");
        }
      } else {
        Serial.println("Senha incorreta.");
        mostrarMensagemTemporaria("Senha Incorreta");
      }
      passwordTyped = "";
      return;
    }

    passwordTyped += key;

    lcd.setCursor(7, 0); // Após "Senha:"
    for (unsigned int i = 0; i < passwordTyped.length(); i++) {
      lcd.print("*");
    }
  }
}

void processRFID() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String readUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    readUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  readUID.toUpperCase();
  Serial.print("Cartão lido: ");
  Serial.println(readUID);

  bool autorizado = false;

  for (String uid : authorizedUIDs) {
    if (uid == readUID) {
      autorizado = true;
      break;
    }
  }

  if (autorizado) {
    Serial.println("Cartão autorizado!");
    if (portaTrancada) {
      closeSolenoide();
      mostrarMensagemTemporaria("Acesso Liberado");
    }
    else{
      openSolenoide();
      mostrarMensagemTemporaria("Trancando Porta");
    }
  } else {
    Serial.println("Cartão não autorizado!");
    mostrarMensagemTemporaria("Cartao Invalido");
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// ===== VISUALIZAÇÃO NO DISPLAY =====
void mostrarMensagemTemporaria(const String& mensagem) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensagem);
  tempoMensagem = millis();
  mostrandoMensagem = true;
}

// ===== SETUP E LOOP =====
void setup() {
  //
  Serial.begin(115200);

  // INTERNET E MQTT
  initWifi();
  initMqtt();

  // RFID
  SPI.begin(); // Necessário para o RFID
  mfrc522.PCD_Init();
  Serial.println("Leitor RFID iniciado.");

// RFID SS (SDA)	5
// RFID RST	      4
// RFID MOSI	    23
// RFID MISO	    19
// RFID SCK	      18

  // SOLENOIDE
  initPinSolenoide();
  closeSolenoide();
  publishEstado();

  // DISPLAY
  Wire.begin(21, 22); // SDA e SCL do ESP32
  lcd.begin();      //  Para Robojax
  lcd.backlight();
  lcd.clear();
}


void loop() {
  
  // INICIANDO LÓGICA DE ABERTURA E FECHAMENTO
  keypadProcess();
  processRFID();

  // VERIFICACAO MODO OFFLINE
  if (!modoOffline) {
    if (!mqttClient.connected()) {
      reconnectMqtt();
    }
    mqttClient.loop();
  }

  // DISPLAY
  if (mostrandoMensagem && millis() - tempoMensagem > 3000) {
    lcd.clear();
    mostrandoMensagem = false;
  }
}
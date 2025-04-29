# 🔐 Fechadura Biométrica Inteligente Integrada ao Home Assistant

Este projeto consiste no desenvolvimento de uma fechadura eletrônica biométrica baseada em ESP32, com autenticação via impressão digital, integração com o Home Assistant e estrutura física projetada em modelagem 3D.

## 📋 Descrição

Este projeto visa aumentar a segurança e automação de ambientes através de uma fechadura biométrica integrada a sistemas de automação residencial. Utilizando autenticação por impressão digital, o sistema aciona uma solenoide para abrir ou trancar portas, exibindo informações em tempo real em um display LCD, com controle adicional via Home Assistant.

---

## ✅ Funcionalidades

- Autenticação de usuários via sensor biométrico SM15
- Acionamento de solenoide para travamento/destravamento
- Exibição de status em Display LCD
- Entrada de comandos via teclado matricial 4x4
- Comunicação com Home Assistant para monitoramento e controle remoto
- Registro e exclusão de impressões digitais
- Feedback visual via LCD e sonoro (opcional)

---

## 🔧 Componentes Utilizados

- **Microcontrolador:** ESP32-WROOM-32
- **Sensor Biométrico:** SM15 UART
- **Atuador:** Mini Solenoide 12V
- **Display:** LCD 16x2 com I2C
- **Entrada de dados:** Teclado Matricial 4x4
- **Relé:** Módulo de 1 canal
- **Outros:** Fonte 12V, jumpers, protoboard ou placa de circuito impresso

---

## 🏠 Integração com Home Assistant
Comunicação via MQTT ou integração direta por ESPHome (a definir).

- Gatilhos para automações com base em eventos de autenticação.

---

##  🛠 Tecnologias

- **Firmware:** Arduino IDE (C++)
- **Microcontrolador:** ESP32-WROOM-32
- **Automação Residencial:** Home Assistant
- **Modelagem 3D:** Fusion (Autodesk)
- **Versionamento:** Git / GitHub

---

## 🧱 Estrutura Física
A estrutura foi inteiramente modelada no Fusion e projetada para encaixe sob medida dos componentes. A modelagem visa facilitar a impressão 3D e o acesso a portas e interfaces externas.

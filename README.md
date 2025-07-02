# 🔐 Fechadura Biométrica Inteligente Integrada ao Home Assistant

Este projeto consiste no desenvolvimento de uma fechadura eletrônica biométrica baseada em ESP32, com autenticação via impressão RFID, senha via teclado matricial, integração com o Home Assistant e estrutura física projetada em modelagem 3D.

## 📋 Descrição

Este projeto visa aumentar a segurança e automação de ambientes através de uma fechadura  eletrônica. Utilizando autenticação por RFID ou senha via teclado, o sistema aciona uma solenoide para abrir ou trancar portas, exibindo informações em tempo real em um display e visualização de dados extraídos da utilização do dispositivo via Home Assistant.

---

## ✅ Funcionalidades

- Autenticação de usuários via RFID MFRC522
- Acionamento de solenoide para travamento/destravamento
- Exibição de status em Display I2c
- Entrada de comandos via teclado matricial 4x4
- Comunicação com Home Assistant para monitoramento e controle remoto
- Feedback visual via display

---

## 🔧 Componentes Utilizados

- **Microcontrolador:** ESP32-WROOM-32
- **RFID:** MFRC522 SPI
- **Atuador:** Mini Solenoide 12V
- **Display:** Em estudo
- **Entrada de dados:** Teclado Matricial 4x4
- **Relé:** Módulo de 1 canal
- **Outros:** Fonte 12V, jumpers, protoboard ou placa de circuito impresso

---

## 🏠 Integração com Home Assistant
Comunicação via MQTT ou integração direta por Home Assistant

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

---

## 👨‍💻 Autores

- **Emyli Kelri Pereira**  
  - LinkedIn: [Emyli Kelri Pereira](https://www.linkedin.com/in/emyli-kelri-pereira-94210b2bb/)

- **Felipe Barbosa dos Santos**  
  - GitHub: [@felipeBarbosanxt](https://github.com/felipeBarbosanxt)  
  - LinkedIn: [Felipe Barbosa dos Santos](https://www.linkedin.com/in/felipe-barbosa-bbsnxt/)

- **Felipe de Castro Alves**  
  - LinkedIn: [Felipe de Castro Alves](https://www.linkedin.com/in/felipe-de-castro-alves-328983245/)

- **Leticia Gasques de Santana**  
  - LinkedIn: [Leticia Gasques de Santana](https://www.linkedin.com/in/leticia-gasques-de-santana-9220bb2a5/)

- **Thallita Cardoso Tavares**
  - GitHub: [@Tali-Cardoso](https://github.com/Tali-Cardoso) 
  - LinkedIn: [Thallita Cardoso Tavares](https://www.linkedin.com/in/thallita-cardoso-tavares-188455326/)

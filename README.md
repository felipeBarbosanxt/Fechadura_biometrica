# 🔐 Fechadura Eletrônica com Autenticação por RFID, Senha e Integração com Home Assistant

Este projeto consiste no desenvolvimento de uma fechadura eletrônica baseada em ESP32, com autenticação via RFID, senha através de teclado matricial, integração com o Home Assistant e estrutura física projetada em modelagem 3D para impressão.

---

## 📋 Descrição

Este projeto tem como objetivo promover segurança e automação residencial através de uma fechadura eletrônica multifator. O sistema permite o destravamento da porta mediante autenticação via cartão RFID ou senha numérica, utilizando um teclado matricial. A comunicação com o Home Assistant viabiliza o monitoramento remoto, registro de eventos e automações personalizadas. O sistema também exibe feedback em tempo real por meio de um display conectado ao ESP32.

---

## ✅ Funcionalidades

- Autenticação de usuários via RFID (MFRC522)
- Entrada alternativa por senha utilizando teclado matricial 4x4
- Acionamento de solenoide para trancar ou destrancar portas
- Exibição de mensagens de status em Display I2C
- Comunicação com o Home Assistant via MQTT
- Registro e visualização de eventos no painel do Home Assistant

---

## 🔧 Componentes Utilizados

- **Microcontrolador:** ESP32-WROOM-32
- **RFID:** Leitor MFRC522 (SPI)
- **Teclado:** Matricial 4x4
- **Atuador:** Mini Solenoide 12V
- **Display:** (Em definição, com comunicação I2C)
- **Relé:** Módulo de 1 canal
- **Alimentação:** Fonte 12V
- **Outros:** Protoboard, jumpers, parafusos, conectores

---

## 🏠 Integração com Home Assistant

- Integração via **MQTT** com tópicos personalizados para envio de logs e status
- Gatilhos para **automações** (por exemplo, acionar câmeras ou enviar notificações)
- Monitoramento do estado da fechadura diretamente na interface do Home Assistant

---

## 🛠 Tecnologias

- **Firmware:** Desenvolvido com Arduino IDE (linguagem C++)
- **Microcontrolador:** ESP32-WROOM-32
- **Automação Residencial:** Home Assistant
- **Modelagem 3D:** Fusion 360 (Autodesk)
- **Versionamento:** Git + GitHub

---

## 🧱 Estrutura Física

A estrutura da fechadura foi projetada em **Fusion 360** com foco em encaixes precisos para os componentes eletrônicos. O modelo visa facilitar a impressão 3D e garantir um design compacto, funcional e esteticamente agradável.

---

## 👨‍💻 Autores

- **Emyli Kelri Pereira**  
  [LinkedIn](https://www.linkedin.com/in/emyli-kelri-pereira-94210b2bb/)

- **Felipe Barbosa dos Santos**  
  [GitHub](https://github.com/felipeBarbosanxt) • [LinkedIn](https://www.linkedin.com/in/felipe-barbosa-bbsnxt/)

- **Felipe de Castro Alves**  
  [LinkedIn](https://www.linkedin.com/in/felipe-de-castro-alves-328983245/)

- **Leticia Gasques de Santana**  
  [LinkedIn](https://www.linkedin.com/in/leticia-gasques-de-santana-9220bb2a5/)

- **Thallita Cardoso Tavares**  
  [GitHub](https://github.com/Tali-Cardoso) • [LinkedIn](https://www.linkedin.com/in/thallita-cardoso-tavares-188455326/)

# Especificação de Componentes de Hardware

Este documento apresenta a descrição técnica detalhada de todos os componentes de hardware utilizados no desenvolvimento e na montagem física do protótipo de Monitoramento de Estacionamento Público IoT.

---

## 1. Componentes Principais

### 1.1. Microcontrolador: ESP32 DevKit V1
* **Função no Projeto:** Atua como a unidade de processamento central (CPU). É responsável por alimentar os sensores periféricos, executar a varredura lógica das portas digitais, controlar o acionamento dos LEDs locais e gerenciar a pilha de protocolos TCP/IP para envio das mensagens via rede sem fio.
* **Especificações Técnicas:**
  * Processador: Tensilica Xtensa Dual-Core LX6 de 32 bits
  * Clock de Operação: Ajustável até 240 MHz
  * Memória SRAM Interna: 520 KB
  * Conectividade: Wi-Fi 802.11 b/g/n integrado (Frequência de 2.4 GHz) e Bluetooth v4.2 BR/EDR/BLE
  * Tensão de Operação Lógica: 3.3V
  * Tensão de Alimentação: 5V via conector Micro-USB

### 1.2. Sensor: Módulo Sensor de Obstáculo Infravermelho TCRT5000
* **Função no Projeto:** Atua como o elemento de entrada de dados, detectando a presença ou ausência física do chassi de um veículo estacionado sobre a vaga monitorada.
* **Especificações Técnicas:**
  * Princípio de Funcionamento: Sensor óptico reflexivo por emissão e recepção de luz infravermelha
  * Emissor: Diodo emissor de infravermelho de arsenieto de gálio (GaAs)
  * Receptor: Fototransistor de silício de alta sensibilidade
  * Circuito Integrado Integrado: Comparador analógico/digital LM393
  * Ajuste: Potenciômetro integrado para calibração de distância de detecção (faixa ideal de 0,2 cm a 2,5 cm)
  * Tipo de Saída: Digital discreta (Nível lógico Alto/Baixo)

### 1.3. Atuadores: Diodos Emissores de Luz (LEDs) 5mm
* **Função no Projeto:** Atuam como os elementos de saída local, fornecendo feedback visual imediato aos condutores na via pública sobre o status de ocupação da vaga.
* **Especificações Técnicas:**
  * **LED Verde:** Tipo difuso, diâmetro de 5mm. Permanece ativo enquanto o status da vaga for interpretado como "Livre".
  * **LED Vermelho:** Tipo difuso, diâmetro de 5mm. É ativado instantaneamente quando o status passa para "Ocupado".

---

## 2. Componentes Passivos e Infraestrutura

### 2.1. Resistores de Filme de Carbono 330 Ohms
* **Função no Projeto:** Proteção elétrica. São conectados em série com o catodo (terminal negativo) de cada LED para limitar a corrente elétrica fornecida pelas portas GPIO do ESP32, impedindo a queima dos atuadores e danos físicos ao microcontrolador.
* **Especificações Técnicas:**
  * Valor de Resistência: 330 Ohms
  * Tolerância: ±5%
  * Potência Máxima: 1/4W (0.25W)

### 2.2. Matriz de Contatos (Protoboard)
* **Função no Projeto:** Base mecânica e elétrica para interconexão dos componentes sem a necessidade de soldagem fixa. Os barramentos laterais (`+` e `-`) foram dedicados à distribuição de energia, enquanto as trilhas numéricas centrais foram utilizadas para a lógica de sinal.
* **Especificações Técnicas:**
  * Capacidade: 400 pontos de contato

### 2.3. Cabos Condutores (Jumpers Macho-Fêmea)
* **Função no Projeto:** Estabelecer a fiação estruturada entre os pinos expostos do ESP32/Sensor (finais macho) e os barramentos de conexões da protoboard.

---

## 3. Mapeamento de Pinos e Conexões (Pinout)

A tabela abaixo documenta a pinagem exata utilizada na montagem física e na programação do firmware:

| Componente de Hardware | Pino de Origem do Componente | Pino de Destino no ESP32 | Tipo de Interface Eletrônica |
| :--- | :--- | :--- | :--- |
| **Sensor TCRT5000** | VCC | 3V3 (Barramento `+`) | Alimentação Positiva (3.3V) |
| **Sensor TCRT5000** | GND | GND (Barramento `-`) | Referência de Aterramento |
| **Sensor TCRT5000** | DO (Digital Output) | GPIO 12 | Entrada Digital (INPUT) |
| **LED Verde** | Anodo (Perna Longa) | GPIO 22 | Saída Digital (OUTPUT) |
| **LED Vermelho** | Anodo (Perna Longa) | GPIO 16 | Saída Digital (OUTPUT) |
| **Resistores (330 Ohms)** | Terminal de Saída do Catodo | GND (Barramento `-`) | Limitação de Corrente para o Terra |

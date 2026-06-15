# Sistema IoT para Monitoramento de Estacionamento Público (ODS 11)

Este repositório contém o código-fonte, esquemáticos de hardware e a documentação completa do protótipo desenvolvido para a disciplina de Internet das Coisas na Universidade Presbiteriana Mackenzie.

## 1. Descrição do Projeto e Funcionamento
O projeto consiste em um nó sensor inteligente voltado para a detecção de ocupação de vagas públicas de estacionamento em tempo real. O sistema utiliza um sensor óptico reflexivo infravermelho para analisar a presença física de um veículo. Ao sofrer alteração de estado, o microcontrolador aciona atuadores de sinalização local (LEDs indicativos) e realiza a transmissão telemétrica via rede TCP/IP utilizando o protocolo MQTT para uma central de tráfego.

### Como reproduzir este projeto:
1. Monte o circuito elétrico conforme os diagramas da pasta `/hardware`.
2. Abra a pasta `/software` na IDE do Arduino.
3. Instale as bibliotecas `WiFi.h` e `PubSubClient.h`.
4. Altere as credenciais de `ssid` e `password` no arquivo `.ino` para os dados da sua rede local.
5. Realize o upload para a placa ESP32 e monitore as publicações no broker através do painel HiveMQ.

## 2. Especificação do Hardware Utilizado
* **Plataforma de Desenvolvimento:** Módulo ESP32 DevKit V1 (Processador Dual-Core Xtensa LX6 de 32 bits, clock de 240MHz, Wi-Fi nativo).
* **Sensor:** Sensor de Obstáculo Infravermelho TCRT5000 (Princípio reflexivo com comparador integrado LM393).
* **Atuadores:** 1x LED Difuso Verde 5mm, 1x LED Difuso Vermelho 5mm, 2x Resistores de Película de Carbono de 330 Ohms.
* **Infraestrutura de encapsulamento (Opcional/Case):** O protótipo foi projetado para ser acondicionado em uma caixa protetora de ABS com dimensões estimadas de 10cm x 6cm x 4cm para proteção contra intempéries urbanas.

## 3. Software e Documentação de Código
O algoritmo foi desenvolvido em linguagem C/C++ focado em arquitetura assíncrona não-bloqueante para evitar gargalos na varredura periférica durante quedas de rede. 
* O código-fonte documentado linha por linha encontra-se disponível no arquivo: `/software/estacionamento_iot.ino`.

## 4. Interfaces, Protocolos e Módulos de Comunicação
* **Camada de Rede:** TCP/IP via módulo de rádio Wi-Fi 802.11 b/g/n integrado do ESP32.
* **Protocolo de Aplicação:** MQTT (Message Queuing Telemetry Transport) operando em arquitetura Publish/Subscribe.
* **Porta de Conexão:** 1883 (TCP puro para o cliente embarcado).
* **Broker Utilizado:** `broker.hivemq.com`
* **Estrutura de Tópico:** `cidade/mobilidade/estacionamento/vaga01`
* **Payload de Mensagem:** Formato JSON leve (ex: `{"vaga": 1, "status": "ocupada"}`).

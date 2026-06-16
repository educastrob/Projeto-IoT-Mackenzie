# Sistema de Monitoramento de Vagas de Estacionamento com IoT e MQTT

**Autores:** Eduardo Castro Brito (RA: [10423956])
**Universidade Presbiteriana Mackenzie** - Faculdade de Computação e Informática  
**Disciplina:** Internet das Coisas | Junho de 2026

## Simulação Wokwi

https://wokwi.com/projects/466923078597139457

## Descrição

Sistema embarcado para monitoramento contínuo e detecção de ocupação de vagas públicas de estacionamento em tempo real usando ESP32 e sensor óptico reflexivo infravermelho TCRT5000, com feedback visual em LEDs indicativos e comunicação bidirecional via protocolo MQTT com broker HiveMQ. Projeto alinhado à ODS 11 - Cidades e Comunidades Sustentáveis.

## Como Reproduzir o Projeto

1. Acesse https://wokwi.com e crie um novo projeto ESP32 (ou monte fisicamente na bancada).
2. Adicione os componentes: Sensor TCRT5000 (ou Slide Switch na simulação), LED Verde, LED Vermelho e 2x Resistores de 330 Ohms.
3. Conecte conforme a pinagem abaixo.
4. Cole o código do arquivo `estacionamento_iot.ino`.
5. No gerenciador de bibliotecas da IDE (or em `libraries.txt` no Wokwi) adicione: `PubSubClient`.
6. Altere as credenciais de `ssid` e `password` para a sua rede real (se usar hardware físico).
7. Clique em Play para simular ou faça o Upload para a placa física.
8. Abra https://www.hivemq.com/demos/websocket-client/.
9. Conecte e dê *Subscribe* em: `cidade/mobilidade/estacionamento/vaga01` e veja os dados chegando em tempo real!
10. Para testar o comando remoto (*Subscribe*), envie a string `LED_VERMELHO_ON` ou `LED_VERMELHO_OFF` no tópico `cidade/mobilidade/estacionamento/vaga01/cmd`.

## Componentes Utilizados

| Componente | Especificação | Função |
| :--- | :--- | :--- |
| **ESP32** | WiFi integrado, 240 MHz, Dual-Core | Comunicação WiFi e pilha de protocolos MQTT |
| **TCRT5000** | Sensor óptico reflexivo IR, saída digital | Detecção física de presença do veículo na vaga |
| **LED Verde** | Difuso, 5mm | Indicador visual de vaga LIVRE localmente |
| **LED Vermelho** | Difuso, 5mm | Indicador visual de vaga OCUPADA localmente |
| **Resistores** | Filme de Carbono, 330 Ohms | Limitação de corrente para proteção dos LEDs |

## Pinagem - ESP32

| Componente | Pino ESP32 | Observação |
| :--- | :--- | :--- |
| **TCRT5000 VCC** | 3V3 | Alimentação positiva do módulo |
| **TCRT5000 GND** | GND | Referência de aterramento comum |
| **TCRT5000 DO** | GPIO 12 | Entrada digital (Leitura do Sensor) |
| **LED Verde** | GPIO 22 | Saída digital (Controle do LED Verde) |
| **LED Vermelho** | GPIO 16 | Saída digital (Controle do LED Vermelho) |
| **Resistores** | GND | Ligados em série com o catodo dos LEDs ao Terra |

## Protocolo MQTT e Comunicação

* **Broker:** HiveMQ público (broker.hivemq.com)
* **Porta:** 1883
* **Protocolo:** TCP/IP
* **QoS:** nível 0
* **Biblioteca:** PubSubClient (Nick O'Leary)
* **WiFi:** rede `Wokwi-GUEST` (simulação) ou utilize rede real.

## Tópicos MQTT

| Tópico | Descrição | Unidade / Formato |
| :--- | :--- | :--- |
| `cidade/mobilidade/estacionamento/vaga01` | Envio de telemetria de status e métricas da vaga | String JSON estruturada |
| `cidade/mobilidade/estacionamento/vaga01/cmd` | Escuta de comandos remotos vindos da central | String de texto puro (Comando) |

## Lógica de Funcionamento

* **Sensor em HIGH** = Sem obstáculo detectado = **Vaga LIVRE** = LED VERDE ativo + Cálculo do tempo total de permanência que o veículo anterior utilizou.
* **Sensor em LOW** = Veículo detectado = **Vaga OCUPADA** = LED VERMELHO ativo + Inicialização do cronômetro interno (`millis()`).

## Bibliotecas Necessárias

* `WiFi.h` (Nativa do ecossistema ESP32)
* `PubSubClient` (Nick O'Leary)

## Observação sobre Simulação

Na simulação do Wokwi foi utilizada uma chave seletora (*Slide Switch*) no lugar do sensor físico TCRT5000, visto que o comportamento elétrico digital de transição discreta de nível lógico (Alto/Baixo) reflete perfeitamente a lógica de interrupção por barreira física e funcionamento síncrono do hardware real de bancada.

## Autor

Eduardo Castro Brito
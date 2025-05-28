# AquaSense

**Estação de Monitoramento de Qualidade da Água (simulação Wokwi)**

## Descrição do Projeto
AquaSense é um protótipo de estação básica de monitoramento de qualidade da água, desenvolvido para a disciplina "Objetos Inteligentes Conectados". Utiliza um ESP32 para leitura de sensores de pH, turbidez, temperatura (DS18B20) e condutividade, enviando dados via MQTT.

## Estrutura do Repositório
```
├── README.md
├── src/
│   └── sketch.ino
├── hardware/
│   ├── diagram.json
│   └── hardware.md
├── protocols/
│   ├── mqtt.md
│   └── onewire.md
├── results/
│   ├── screenshots/
│   └── data/
└── LICENSE
````

## Pré-requisitos
- Arduino IDE (>=1.8.13)
- Bibliotecas:
  - OneWire
  - DallasTemperature
  - PubSubClient
  - Time
- Conexão com um broker MQTT (ex.: broker.hivemq.com)
- Wokwi (https://wokwi.com/)

## Instalação e Uso
1. Clone este repositório:
```bash
$ git clone https://github.com/seu-usuario/aquasense.git
$ cd aquasense
````

2. Abra `src/sketch.ino` na Arduino IDE.
3. Instale as bibliotecas listadas em **libraries.txt**.
4. Configure SSID e senha Wi‑Fi no início do sketch.
5. Configure o endereço e porta do broker MQTT.
6. Carregue o firmware no ESP32.
7. Abra a simulação Wokwi com `hardware/diagram.json`.
8. Verifique no console MQTT o tópico `aquasense/dados`.

## Resultados
Veja a seção de Resultados no artigo para capturas de tela e tabela de leituras.

## Licença
Este projeto está licenciado sob a licença MIT. Consulte o arquivo LICENSE para detalhes.

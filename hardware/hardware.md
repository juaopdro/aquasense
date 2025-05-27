# Descrição de Hardware

## Componentes Principais
- **ESP32 Dev Module**
  - Microcontrolador dual-core 240 MHz com Wi-Fi e Bluetooth integrados.
- **Sensor de pH**
  - Faixa: 0–14 pH (módulo com circuito de condicionamento de sinal).
- **Sensor de Turbidez**
  - Faixa: 0–1000 NTU (padrão de baixo custo).
- **DS18B20 (Temperatura)**
  - Faixa: -55 °C a +125 °C; precisão de ±0,5 °C.
- **Sensor de Condutividade**
  - Faixa: 0–2000 µS/cm (módulo de interface).
- **LED Indicador**
  - Atua como alerta: acende quando valor fora da faixa definida.

## Diagrama de Montagem
- Veja `diagram.json` para o esquema no Wokwi (porta ONE_WIRE_PIN = 33, PIN_PH = 34, PIN_TURB = 35, PIN_COND = 32, LED_PIN = 2).

## Referências de Datasheets
1. Espressif Systems. *ESP32 Series Datasheet*.
2. Dallas Semiconductor. *DS18B20 Technical Datasheet*.
3. Generic pH Sensor Module Documentation.
4. Generic Turbidity Sensor Module Specification.
5. Generic Conductivity Sensor Module Specification.
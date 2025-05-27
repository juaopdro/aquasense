# Documentação 1-Wire (DS18B20)

## Visão Geral do Protocolo
O protocolo 1-Wire permite comunicação com múltiplos dispositivos usando apenas uma única linha de dados.

## Biblioteca Utilizada
- `OneWire` para comunicação física na porta ONE_WIRE_PIN.
- `DallasTemperature` para conversão e leitura de temperatura.

## Processo de Leitura
1. Inicialização do barramento 1-Wire.
2. Descoberta de dispositivos e seleção de endereço.
3. Comando de conversão de temperatura.
4. Leitura de bytes e conversão para valor em °C.

## Faixa de Operação DS18B20
- Temperatura: -55 °C a +125 °C
- Precisão: ±0.5 °C (−10 °C a +85 °C)
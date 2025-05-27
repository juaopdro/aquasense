# Documentação MQTT

## Tópicos Utilizados
`aquasense/dados` — Payload JSON:
```json
{
  "timestamp": "2025-05-26T12:30:00Z",
  "pH": 7.5,
  "turbidez": 3.4,
  "temperatura": 22.5,
  "condutividade": 1250,
  "alerta": false
}
```

## Configurações de QoS
- QoS = 0 para todas as publicações.
- Retain = false.

## Reconexão e Tratamento de Falhas
1. Se a conexão com o broker for perdida, a função `reconnect()` tenta reconnectar a cada 5 segundos.

## Formato de Payload
| Campo           | Tipo    | Descrição                                 |
| --------------- | ------- | ----------------------------------------- |
| `timestamp`     | string  | Timestamp em ISO 8601 sobre hora atual    |
| `pH`            | float   | Valor medido pelo sensor de pH            |
| `temperatura`   | float   | Valor medido pelo sensor DS18B20          |
| `condutividade` | integer | Valor medido pelo sensor de condutividade |
| `alerta`        | boolean | Valor decidido por lógica em código       |
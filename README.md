# arduino-car-control

Simulação de uma unidade de controle embarcada veicular baseada em Arduino, com comunicação entre subsistemas via barramento I²C. O sistema é modular e composto por três módulos interconectados: **Powertrain**, **Segurança** e **Computador de Bordo**.

---

## 📦 Arquitetura do Sistema

O projeto é dividido em três controladores Arduino:

                     +---------------------+
                     |  Computador de Bordo|
                     |     (Mestre I²C)     |
                     +----------+----------+
                                |
            +-------------------+-------------------+
            |                                       |
     +------v------+                         +------v------+
     |  Powertrain  |                         |  Segurança  |
     | (Escravo I²C)|                         |(Escravo I²C)|
     +-------------+                         +-------------+


### 🔗 Comunicação
- **Protocolo**: I²C
- **Mestre**: Computador de Bordo (`Wire.begin()`)
- **Escravos**:
  - Powertrain (`0x08`)
  - Segurança (`0x09`)

---

## 🧩 Módulos

### 🔹 Powertrain
- Leitura de sensores de acelerador, freio e marcha
- Controle da rotação e sentido do motor
- Cálculo da velocidade de deslocamento
- Envia `n_rotor` e `marcha` via I²C

### 🔹 Segurança
- Leitura de sensores da cadeira, cinto, porta e ultrassônico
- Envia informações codificadas via I²C para o dashboard

### 🔹 Computador de Bordo
- Recebe dados dos módulos via I²C
- Exibe a velocidade no display LCD
- Aciona alarmes (LEDs e alertas sonoros) com base nos dados
- Controla servo para simular trava de porta

---


## ⚙️ Requisitos

- Arduino IDE ou VS Code com extensão Arduino
- Placas simuladas no Tinkercad ou físicas (ex: Arduino Uno)
- Bibliotecas utilizadas:
  - `Wire.h` (nativa)
  - `Servo.h` (nativa)
  - `Adafruit_LiquidCrystal.h` (instalável via Library Manager)

---

## 🚀 Como usar

1. Clone o repositório:
   ```bash
   git clone https://github.com/RafaellLouvain/arduino-car-control.git



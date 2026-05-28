# GS---Edge-Computing | # 📡 AGRO SPACE – Sistema Inteligente de Monitoramento Agrícola

## 📌 Descrição do Projeto

O **AGRO SPACE** é um sistema de monitoramento agrícola inteligente desenvolvido com Arduino, sensores ambientais e lógica de análise de dados. O projeto coleta informações do ambiente como temperatura, umidade do ar, umidade do solo e distância de obstáculos, processando esses dados para gerar indicadores de prioridade, classificação do solo e status da rota.

Além disso, o sistema realiza visualização em **display LCD 20x4** e acompanhamento em tempo real via **Serial Monitor**, permitindo análise rápida das condições do ambiente agrícola.

## 🎯 Objetivo da Solução

O objetivo do projeto é criar uma solução de baixo custo para monitoramento agrícola, auxiliando na tomada de decisões relacionadas a:

* Condições do solo
* Risco climático
* Segurança da rota operacional
* Priorização de ações no campo

O sistema busca simular uma aplicação de **agricultura inteligente (AgroTech)** utilizando sensores básicos e lógica embarcada.

## 🔩 Componentes Utilizados

* Arduino Uno
* Sensor de temperatura e umidade DHT22
* Sensor de umidade do solo (analógico)
* Sensor ultrassônico HC-SR04
* Display LCD 20x4 com módulo I2C
* LEDs:
  * Vermelho
  * Amarelo
  * Verde
* Resistores
* Jumpers
* Protoboard
* Fonte USB / alimentação Arduino

## ⚙️ Explicação do Funcionamento

O sistema funciona em ciclos contínuos dentro do `loop()`:

### 1. Leitura de Sensores

* Temperatura e umidade do ar (DHT22)
* Umidade do solo (entrada analógica)
* Distância (sensor ultrassônico)

### 2. Processamento dos Dados

Os dados coletados são convertidos e analisados para gerar:

* Umidade do solo em porcentagem
* Maturidade do ambiente
* Risco de chuva
* Condição da rota
* Índice de prioridade

### 3. Lógica de Decisão

Com base nos cálculos:

* **Prioridade:** Alta / Média / Baixa
* **Solo:** Crítico / Atenção / Segura
* **Rota:** Classificada automaticamente pelo sistema

### 4. Saída de Dados

* Exibição no **LCD 20x4**
* Exibição detalhada no **Serial Monitor**
* Controle de LEDs:
  * Vermelho → Crítico
  * Amarelo → Atenção
  * Verde → Seguro

## 🔌 Estrutura do Circuito | ### Conexões principais:

**DHT22**

* DATA → A1

**Sensor de solo**

* OUT → A0

**Ultrassônico HC-SR04**

* TRIG → Pino 4
* ECHO → Pino 5

**LEDs**

* Vermelho → A2
* Amarelo → A3
* Verde → 6

**LCD I2C**

* SDA → A4
* SCL → A5

## Modelo Visual do Arduitno
![Arduino modelo WOKWI](file:///C:/Users/jucas/Downloads/Arduino%20Modelo%20WOKWI.png)

## 🚀 Instruções de Execução

1. Instalar a IDE do Arduino
2. Instalar bibliotecas necessárias:
   * `DHT.h`
   * `LiquidCrystal_I2C.h`
3. Conectar os componentes conforme o circuito
4. Selecionar placa:
   * Arduino Uno
5. Selecionar porta COM correta
6. Compilar e enviar o código para a placa
7. Abrir o Serial Monitor (9600 baud)

## 👥 Integrantes do Grupo

* Nome 1: Joao Lucca - rm 569562
* Nome 2: Murillo Farias - rm569045
* Nome 3: Thalles Almeida - rm569925
* Nome 4: Isaac Ambrozevicius - rm569166


## 📂 Arquivos do Projeto

O projeto é composto por:

* `agro_space.ino` → Código fonte principal em Arduino/C++
* Bibliotecas externas:
  * DHT sensor library
  * LiquidCrystal_I2C
* Esquema do circuito (protótipo físico ou simulação)

## 📊 Observações Finais

Este projeto simula um sistema real de monitoramento agrícola inteligente, integrando sensores físicos, processamento de dados e tomada de decisão automatizada, sendo aplicável em conceitos de IoT e Agricultura 4.0.



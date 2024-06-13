## Utilização de Display LCD 20x4 com STM32F411

Este projeto visa demonstrar como integrar e utilizar um display LCD 20x4 com o microcontrolador STM32F411 (Blackpill). O display será configurado para exibir informações textuais, proporcionando uma interface de usuário simples e eficaz.

### Componentes Necessários

- Microcontrolador STM32F411 (Blackpill)
- Display LCD 20x4
- Potenciômetro (para ajuste do contraste do LCD)
- Fonte de alimentação 5V
- Cabos de conexão
- Placa de desenvolvimento (por exemplo, ST-Link V2)

### Conexões

- **RS (Register Select)** do LCD -> Pino B12 do STM32F411
- **E (Enable)** do LCD -> Pino B13 do STM32F411
- **D4, D5, D6, D7** do LCD -> Pinos B3, B4, B5, B6 do STM32F411, respectivamente
- **V0** do LCD -> Conectado a um potenciômetro para ajuste de contraste
- **VCC** do LCD -> 5V (ou outra fonte de 5V)
- **GND** do LCD -> GND
- **VERY HIGH** todas as GPIO (para diminuir latencia)

![image](https://github.com/MatKenji/GPIO_Display/assets/169562589/5af0042c-bed9-4160-9dc3-20ff74e22bed)

![image](https://github.com/MatKenji/GPIO_Display/assets/169562589/555c9711-d426-4d18-8bfe-31f540e40d29)


### Configuração do Projeto

1. **STM32CubeMX:**
   - Configure os pinos GPIO necessários para os sinais RS, E, D4, D5, D6, D7 no STM32CubeMX.
   - Ative os pinos conforme as conexões descritas acima.

2. **Ajuste do Contraste:**
   - Conecte o terminal central do potenciômetro ao V0 do LCD.
   - Conecte um dos terminais do potenciômetro ao GND e o outro ao VCC (5V).

4. **Bibliotéca:**   
   - Adicionar biblioteca do LCD (está disponibilizado)
     
3. **Código na IDE:**
   - Implemente o código C para inicializar o LCD, enviar dados e comandos conforme necessário para exibir informações.

### Funcionamento Esperado

O display LCD 20x4 configurado corretamente com o STM32F411 exibirá informações textuais conforme programado. O ajuste do potenciômetro será usado para ajustar o contraste do LCD, garantindo uma boa legibilidade dos caracteres.

### Considerações

- **Alimentação e Ground:**
  - Certifique-se de fornecer uma alimentação estável de 5V ao display e conectar corretamente os pinos de GND para evitar problemas de funcionamento.

- **Configuração do Software:**
  - Utilize funções apropriadas na HAL (Hardware Abstraction Layer) ou bibliotecas equivalentes para controlar o display LCD. Isso inclui enviar comandos de inicialização, enviar texto para ser exibido e controlar o contraste.

- **Teste e Depuração:**
  - Após a implementação do código, teste o funcionamento do display LCD para verificar se as informações são exibidas corretamente e se o ajuste de contraste está adequado.

Este projeto proporcionará uma introdução prática ao uso de displays LCD com microcontroladores STM32F411, expandindo suas habilidades em desenvolvimento de sistemas embarcados e interfaces de usuário.

- **Nota:** Os arquivos de código fornecidos neste repositório foram desenvolvidos usando STM32CubeIDE. Devido a limitações de minha experiência com o STM32CubeIDE, a importação direta do projeto para o Git pode não ter sido feita da maneira mais eficiente ou padronizada. 

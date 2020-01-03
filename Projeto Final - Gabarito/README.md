# Segunda Fase

## Introdução

Olá a todos e sejam bem-vindos à segunda parte do processo seletivo da computação da equipe ThundeRatz!

Nesta parte, o objetivo principal de vocês é controlar a placa feita pela equipe por meio de um potenciômetro, um botão e 3 sensores infrevermelhos. Estes 3 elementos devem afetar 3 LEDs, um servo motor, um buzzer e um laser. Todas as funções que vocês devem usar ou já estão implementadas ou nós vamos explicar elas neste README. Caso queira saber qual pino está configurado para cada coisa deixamos o esquemático da placa na pasta ```docs/```.

## Funções úteis

Vocês vão fazer uso direto de diversas funções HAL em diversas partes do código, as quais são provenientes de blibliotecas da ST. No caso deste projeto, vocês vão fazer uso das funções a seguir:

``` C
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
```

Essa função inicia a PWM em um timer. Os parâmetros vão depender do timer e do canal. A parte ```&htim1``` é o handler do timer e especifica qual timer a função está se referindo. Já a parte ```TIM_CHANNEL_1``` especifica em qual canal do timer a PWM será iniciada. Essa função é utilizada na inicialização de periféricos que utilizam PWM. 

``` C
__HAL_TIM_SET_COUNTER(&htim1, counter);
```
Esta função determina qual o perído de um timer. Da mesma forma que a função acima, os parâmetros dependem do timer. O handler determina qual o timer a ser afetado. Já o parâmetro counter (não precisa ser esse nome) é o valor do período do timer. Como o timer será usado para gerar uma PWM, com essa função se pode alterar o período da PWM, alterando assim, a sua frequência. Os períodos das PWM já estão previamente definidos, vocês só devem utilizar essa função se for necessário alterar o período.

``` C
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty_cycle);
```

Como utilizaremos os timers para gerar PWM, esta função será utilizada para determinar qual o duty cycle da PWM. Os dois primeiros parâmetros dependem do timer e o parâmetro duty_cycle é o valor desejado de duty cycle ~~duh~~.

``` C
HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    /**< Code **/
}
```

Esta é uma interrupção. Vocês devem se lembrar disso da tarefa de embracados. Quando um botão é apertado essa função é executada. Também é possível realizar diferentes ações dependendo do botão apertado. Verifiquem a tarefa de embarcados para ver melhor como essa função funciona e como pode ser implementada. Essa função não está pré-definida em nenhum lugar, vocês devem fazer isso.

``` C
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
```

Esta função altera o valor escrito em um pino de GPIO (neste caso o PA4). Os parâmtros dependem do pino e do que se colocará no pino, o primeiro parâmetro é a porta, o segundo é o número do pino e o terceiro é o que se escreverá no pino. Para se setar o pino com valor lógico "0" se coloca GPIO_PIN_RESET e para se setá-lo com valor lógico "1" se coloca GPIO_PIN_SET. Isso pode ser usado para acender um LED, por exemplo.

## O Programa

O programa de vocês deve fazer o seguinte:

- Mover um servo com o uso do potenciômetro.
- Mudar a intensidade dos LEDs dos sensores quando se aproxima a mão do sensor infravermelho.
- Mover o servo com o uso dos sensores infravermelhos de modo autônomo, apontando para onde os sensores detectarem a presença de algo.
- Fazer uso da criatividade

Nos arquivos já disponibilizados vocês devem escrever o código de vocês na área escrito ```/**< Code **/```. Isso é impotante de modo a manter uma certa padronização entre os programas de cada grupo.

### Geração de PPM

Para controlar o servo será necessário gerar uma PPM, uma PPM nada mais é que uma PWM com um período de 20000 ms, cujo duty cycle varia de 1000 a 2000. Logo para controlar em qual posição o servo estará se deve alterar o duty cycle da PWM utilizada pra PPM, ao se colocar 1000 o servo vai para a posição -90°, ao se colocar 1500 para a posição 0° e ao se colocar 2000 para a posição 90°, variando gradualmente entre essas posições para valores intermediários de duty cycle.

### Frequência de uma PWM 

Para se calcular a frequência da PWM é necessário saber qual a frequência do microcontrolador e o prescaler (um número utilizado para se dividir o valor da frequência e diminuí-lo), por exemplo no caso do microcontrolador que utilizaremos, ele opera em 64 MHz e utilizamos um prescaler de 64, então as frequências das PWM são no máximo 1 MHz. Para se obter a frequência da PWM deve se dividir esse 1 MHz pelo período da PWM, por exemplo, no caso da PPM, o período é de 20.000, logo obtemos uma PWM de frequência 50 Hz. 

## Periféricos

Aqui vocês podem ver algumas informações úteis de qual periféricos está em qual pino, por exemplo.

- Botão está em um pino de interrupção externa, no pino PC14.
- Laser está em um GPIO de saída, no pino PA4.
- A PPM do servo é gerada no timer 2, no canal 4.
- A PWM do buzzer é gerada no timer 1, no canal 1.
- A PWM do LED do sensor 0 é gerada no timer 2, no canal 3.
- A PWM do LED do sensor 1 é gerada no timer 3, no canal 2.
- A PWM do LED do sensor 2 é gerada no timer 3, no canal 4.

## Considerações Finais

Este projeto é um desafio final para testar seus conhecimentos obtidos até aqui e desafiar vocês a buscar mais conhecimento fora. Nem tudo que vocês vão ter que usar foi explicado por nós. Procure na internet, leia o material disponibilizado e pegunte para nós quando dúvidas surgirem. Tudo pode ser feito e queremos ver a criatividade de vocês!

Bom trabalho e boa sorte!

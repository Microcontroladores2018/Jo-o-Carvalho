# Plot de velocidade de Motor DC em tempo real
## Proposta
Este projeto tem como objetivo plotar, em tempo real, a velocidade de um motor DC através da leitura de um encoder. Os sinais do encoder
serão enviados para duas portas GPIO da Discovery configuradas em modo Alternate Function que serão utilizadas para configurar um TIMER em
modo de leitura de encoder através de biblioteca da própria SPL (Standard Peripherals Library). Serão feitas medições periódicas no valor
do contador do TIMER a fim de, através das devidas conversões matemáticas, obter a velocidade do motor em tempo real.

Além disso, deve haver uma comunicação USB entre a Discovery e um PC de forma que os resultados de medição de velocidade sejam enviados 
continuamente para o PC, onde podem ser plotados através do LabView.

## Periféricos
No projeto serão utilizados:
1 STM32F407 Discovery
1 Motor DC 7.2V
1 Encoder em quadratura de 400 divisões
1 PC - LabView -
1 Roda de Metal

![Diagrama de Blocos](DiagBlocosuC.PNG)
Figura 1: Diagrama de Blocos

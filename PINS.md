## Arduino Micro

```
1. D7 -> PE6 -> CPUMUX0 !A/B
28. D8 -> PB4 -> PMB0 SW+
29. D9 -> PB5 -> OC1A -> CPUMUX0 B : CPUMUX Y -> CPUOUT0 PWM
30. D10 -> PB6 -> OC1B -> INTAKE0 PWM
31. D5 -> PC6 -> OC3A -> EXHAUST0 PWM
32. D13 -> PC7 -> OC4A -> R2 2 : R2 1 -> PFP0 LED+
37. A1 -> PF6 -> ADC6 -> EXHAUST0 TACH
38. A2 -> PF5-> ADC5 -> INTAKE0 TACH
39. A3 -> PF4 -> ADC4 -> CPUOUT0 TACH
40. A4 -> PF1 -> ADC1 -> PFP0 SW+
41. A5 -> PF0 -> ADC0 -> PMB0 LED+
```

## AVR0

```
1. PE6 -> PE6
28. PB4 -> PB4
29. PB5 -> OC1A
30. PB6 -> OC1B
31. PC6 -> OC3A
32. PC7 -> OC4A
37. PF6 -> ADC6
38. PF5 -> ADC5
39. PF4 -> ADC4
40. PF1 -> ADC1
41. PF0 -> ADC0
```

## CPUMUX0

```
1. A -> CPUIN0 PWM
2. B -> OC1A
3. !Y
4. VCC -> VCC
5. Y -> CPUOUT0 PWM
6. !A/B -> PE6
7. GND -> GND
```

## CPUIN0

```
1. GND -> GND
2. 12V
3. TACH -> ADC4
4. PWM -> CPUMUX0 A
```

## CPUOUT0

```
1. GND -> GND
2. 12V -> 12V
3. TACH -> ADC4
4. PWM -> CPUMUX0 Y
```

## INTAKE0

```
1. GND -> GND
2. 12V -> 12V
3. TACH -> ADC5
4. PWM -> OC1B
```

## EXHAUST0

```
1. GND -> GND
2. 12V -> 12V
3. TACH -> ADC6
4. PWM -> OC3A
```

## PFP0

```
1. SW- -> GND
2. SW+ -> ADC1
3. LED- -> GND
4. SW+ -> R2 1
```

## PMB0

```
1. SW- -> GND
2. SW+ -> PB4
3. LED- -> GND
4. LED+ -> ADC0
```

## R2

```
1. 1 -> PFP0 LED+
2. 2 -> OC4A
```

## B0

# Nucleo-F401 활용
## ST electronics에서 판매하는 Nucleo-F401보드를 extention board에 장착하여 많은 기능을 수행함을 목적으로 함


## 1. GPIO 와 UART2 활용
- LD2를 Toggle on/off 수행
- uart2를 이용 printf명령으로 Terminal에 Text출력-> 앞으로 Debugging용으로 이용예정

## 2. LCD1602 출력(4bit)
- HSE활성화 clock를 max로 변경함(84Mhz)
- PC6~PC11핀을 LCD1602의 작동에 사용함.
- LD2가 켜지면 LCD에 LD2 on 출력, 반대이면 LD2 off 출력

## 3. Key input(Polling)
- 윤덕용교수님저 STM32F767정복 코드참조 및 조정사용
- KEY 4개입력 받아 LCD에 해당방향 표시 (UP/DOWN, LEFT/RIGHT)
- LCD1602관련 WARING 제거

## 4. ADC DMA
- 가변저항을 이용해 Analog입력 값을 변화시켜 mcu에 입력 digital 값으로 변환
- 12bit Resolution (0-4095) 출력값을 0-99로 LCD에 표시함

## 4.1 ADC Noise 제거
- Hint 제공 : 공한열 팀장
- ADC값을 200번 읽어 평균, 200번읽고 평균계산을 10번수행하고,
 10번에 대한 평균값을 ADC값으로 함.
 
 ## 5. I2C LCD1602(PCF8574모듈)
 - PCF8574모듈을 LCD1602에 연결하여 I2C로 LCD 작동
 - GPIO 6개핀사용하던 것을 I2C 2핀사용하여 4개핀을 다른 용도로 사용가능함
 
 ## 5.1 I2C SSD1306(0.91" oled ) 구동
 - Olikraus 씨의 u8g2 라이브러리를( https://github.com/olikraus/u8g2 ) 이용한 SSD1306 구동
 - 시계형식과 battery 충전표시적용함

 ## 6. Peripheral Devices
 ### 6.1 HC-SR04 초음파센서를 이용한 거리측정
 - gpio핀 2개를 triger,echo핀에 연결하여 거리측정 결과를 OLED에 표시
 - ADC입력값(POTENTIOMETER)를 OLED에 출력(0~4095)

  ### 6.2 TM1637 4 FND module에 거리표시
 - FND 4 digit에 거리를 표시
 - FND 숫자의 밝기는 Potentiometer를통해 ADC입력받은값을 7단계로 나누어 밝기조절함
 

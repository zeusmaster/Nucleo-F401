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

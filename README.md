# STM32기반 LCD 디스플레이 시계


## 설명
STM 기반 개인 프로젝트로 임베디드 영상 강의에서 배운 점들을 어떻게 사용해볼까 고민 중

LCD 디스플레이 라디오를 보고 "한번 만들어볼까" 라는 막연한 생각으로 진행한 프로젝트 입니다.

## 개발 기간

**2024.07 ~ 2024.10.31(기본 구성)**

**2024.11 ~ (유지보수 및 추가 기능 기획중... )**

## 사용 제품

![ESP32-CAM-Module](https://github.com/user-attachments/assets/a8a1bf2f-3fd1-45b0-aac1-479ce70e7ba7) |![NUCLEO_F722ZE](https://github.com/user-attachments/assets/e165a392-7500-4f10-88c3-7ed9bf41b001)
--- | --- | 

![피에조](https://github.com/user-attachments/assets/e98b5884-a1f2-49e6-890c-c7bb07082b03) |![온습도센서](https://github.com/user-attachments/assets/bf8eafba-9f6e-4409-960d-a6cd4a211f31) |![SSD1306](https://github.com/user-attachments/assets/288146fd-6f26-451b-b55d-9ac311f70ab5) 
--- | --- | --- |

![버튼](https://github.com/user-attachments/assets/13e198e9-eb80-4eab-b7a9-bc1a51b1407f) |![가변저항](https://github.com/user-attachments/assets/630d87b7-6dbf-4302-a552-70bf671d739f)
--- | --- | 


## 사용 GPIO 정보

![사용_PINMAP](https://github.com/user-attachments/assets/63823b5d-786e-4c94-a161-4494b681341f)


## STM32CubeIDE 설정


![GPIO_PIN](https://github.com/user-attachments/assets/ecdb08d8-956b-407d-bfcf-a582590b386e) |![CLOCK_설정](https://github.com/user-attachments/assets/540b0f52-3e21-40c1-893f-d45be0342469)
--- | --- | 


![1초타이머_설정](https://github.com/user-attachments/assets/c77c71bb-fede-4bad-ad2e-2dce11449d02) |![Boozer_PWM](https://github.com/user-attachments/assets/f00e6a1e-ff37-4812-85ae-f03b6a644cd0) |![DHT_데이터취득_타이머](https://github.com/user-attachments/assets/30232928-8692-40dc-a19a-f5fd9226deed)
--- | --- | --- |


![가변저항_ADC](https://github.com/user-attachments/assets/5037dfad-db5e-47bd-bd4d-9cc75eb0d150) |![SSD1306_I2C](https://github.com/user-attachments/assets/ffb08fb9-8182-4ede-9ffb-cfb28f4c4bf2) |![RTC활성화](https://github.com/user-attachments/assets/b6df69d1-16f4-4e78-b36b-d9b99a624411) |![ESP32_USART](https://github.com/user-attachments/assets/53d62c2f-3bbb-465d-9892-aa79f5327f47)
--- | --- | --- | --- | 




## 구현 기능

### 1. 시간 및 온 습도 디스플레이

#### - 전원 재 공급시 이전 타임 유지(내부 RTC 레지스터사용)
https://github.com/user-attachments/assets/dc62d802-92e9-4cf7-9234-1bfa38218090

#### - 메뉴 변경 및 메뉴 이동(보드 자체 버튼, 외부 버튼 인터럽트 이용)
https://github.com/user-attachments/assets/cd414bf6-044e-4998-a5cd-f6cd16bd523e

### 2. 알람 기능


#### - 알람 시간 설정
https://github.com/user-attachments/assets/6e7b8945-9393-4358-a77d-e7966be5a958


#### - 알람 시간시 부저 작동 및 종료(LCD 디스플레이 및 내부 스위치를 통한 타이머 부저 종료)
https://github.com/user-attachments/assets/8eb108ee-4683-4b23-9234-9c692538e95f



### 3. 타이머 기능


#### - 타이머 설정 및 타이머 종료(LCD 디스플레이 및 내부 스위치를 통한 타이머 부저 종료)
https://github.com/user-attachments/assets/a1fedf04-4a7d-40f4-89ef-b98247bda895



### 4. 날짜 및 시간 변경 기능

#### - 초기에 날짜 및 시간 설정(time.h 라이브러리 기반 날짜 자동 업데이트)

https://github.com/user-attachments/assets/25368d83-5319-44fb-b22b-696598ec7078


### 5. 특정 시간 마다 온 습도 정보 서버 전송

#### - 하루에 특정시간(0시, 6시, 12시, 18시)에 온습도 데이터 서버 전송 및 DB 업데이트)
https://github.com/user-attachments/assets/d97ce4f8-9a25-4d57-8c12-def4afa96cc4



## 참고 자료

- [SSD1306_HAL_DRIVER](https://github.com/SL-RU/stm32libs/tree/master)
- [DHT11 HAL_DRIVER](https://github.com/mesutkilic/DHT11-STM32-Library)
- [아날로그 핀 설정](https://m.blog.naver.com/sinbong3/222072690691)
- [Python FLASK_MYSQL_연동](https://minha0220.tistory.com/75#google_vignette)
- [ESP32_STM32_WIFI_BRIDGE 관련 블로그](https://with-rl.tistory.com/entry/ESP32-STM32%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%9C-WiFi-Serial-Bridge-%EB%A7%8C%EB%93%A4%EA%B8%B0)
- [오제이 튜브 임베디드 영상 강의](https://www.youtube.com/playlist?list=PLz--ENLG_8TNjRg1OtyFBvUyV4PHaKwmu)

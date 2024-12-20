# STM32기반 LCD 디스플레이 시계


## 설명
STM 기반 개인 프로젝트로 임베디드 영상 강의에서 배운 점들을 어떻게 사용해볼까 고민 중


LCD 디스플레이 라디오를 보고 "한번 만들어볼까" 라는 막연한 생각으로 진행한 프로젝트 입니다.

## 개발 기간

2024.07 ~ 2024.10.31(기본 구성)

2024.11 ~ (유지보수 및 추가 기능 기획중... )

## 사용 제품


![보드그룹화_사진](https://github.com/user-attachments/assets/936379c0-c5d3-48db-a121-b4015b2d927f)


![사용_모듈](https://github.com/user-attachments/assets/fb7488c1-16f5-43ae-ba2f-76ebc3f4b71c)


![기타부품](https://github.com/user-attachments/assets/5b4a4c84-79b7-4921-be3f-e18c5f8436e6)


## 사용 GPIO 정보


![사용_PINMAP](https://github.com/user-attachments/assets/2f230065-4447-43e0-a4dd-ef5cd405e776)



## STM32CubeIDE 설정


![CLOCK_GPIO_설정](https://github.com/user-attachments/assets/03a5f8ba-77f3-4d87-8d2e-c407ccdb8c7c)


![타이머_관련_세팅](https://github.com/user-attachments/assets/f3de5be4-b863-47bc-ab58-6ebb60e6d112)


![기타설정](https://github.com/user-attachments/assets/dd709b76-6012-4a52-bdb3-c7dd5fd9579a)




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

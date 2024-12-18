# STM32기반 LCD 디스플레이 시계


## 설명
2024년 6월부터 9월까지 진행한 STM 기반 개인 프로젝트로 임베디드 영상 강의에서 배운 점들을 어떻게 사용해볼까 고민 중


어머니께서 소파에서 듣고 계시는 LCD 디스플레이 라디오를 보고 스스로 만들어 보자라는 막연한 생각으로 진행한 프로젝트 입니다.



## 사용 제품


![보드그룹화_사진](https://github.com/user-attachments/assets/936379c0-c5d3-48db-a121-b4015b2d927f)


![사용_모듈](https://github.com/user-attachments/assets/b9a6909c-0db3-49e7-b6f0-fa67872456c5)


![기타부품](https://github.com/user-attachments/assets/5b4a4c84-79b7-4921-be3f-e18c5f8436e6)


## 사용 GPIO 정보


![사용_PINMAP](https://github.com/user-attachments/assets/2f230065-4447-43e0-a4dd-ef5cd405e776)



## STM32CubeIDE 설정


![CLOCK_GPIO_설정](https://github.com/user-attachments/assets/03a5f8ba-77f3-4d87-8d2e-c407ccdb8c7c)


![타이머_관련_세팅](https://github.com/user-attachments/assets/f3de5be4-b863-47bc-ab58-6ebb60e6d112)


![기타설정](https://github.com/user-attachments/assets/dd709b76-6012-4a52-bdb3-c7dd5fd9579a)




## 구현 기능

### 1. 시간 및 온 습도 디스플레이
### 2. 알람 기능
### 3. 타이머 기능
### 4. 날짜 및 시간 변경 기능
### 5. 특정 시간 마다 온 습도 정보 서버 전송



## 참고 자료

- [SSD1306_HAL_DRIVER](https://github.com/SL-RU/stm32libs/tree/master)
- [DHT11 HAL_DRIVER](https://github.com/mesutkilic/DHT11-STM32-Library)
- [오제이 튜브 임베디드 영상 강의](https://www.youtube.com/playlist?list=PLz--ENLG_8TNjRg1OtyFBvUyV4PHaKwmu)
- [아날로그 핀 설정](https://m.blog.naver.com/sinbong3/222072690691)

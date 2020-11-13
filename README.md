# threadServer
멀티스레드 소켓 통신 실습용으로 만든 서버입니다.
<hr>

Server_Header.h - 프로그램 헤더

Server_Init.c - 프로그램 실행 후 서버 소켓 생성 함수

Config.c - 서버 옵션 설정 함수

Server_Main.c - (Main Thread) 메인 스레드

Server_Command.c - (Thread) 서버 명령어를 받아 처리하는 함수

CTR_Client.c - (Thread) 클라이언트 접속 요청 수락 후, 클라이언트 제어(메세지 전송, 접속 끊기)

Auth.c - 데이터베이스로 로그인 작업 수행

Client_Accept.c - 클라이언트 접속 요청 처리

Token_Login.c - 접속 요청 시, 로그인 정보를 토큰화하여 반환

Encrpytion.c - 비밀번호 해쉬화 함수

DB_Command.c - DB에 접속하여 쿼리를 수행하는 함수

Send_MSG.c - 메세지 전송 함수

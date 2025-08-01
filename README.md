# 🏫 신갈청소년문화의집 관리자 프로그램

**2025 강남대학교 해커톤(강냉톤)** 프로젝트  
**개발 언어**: C++  
**프레임워크**: Qt 6 (Qt Creator 사용)  
**개발 목적**: 신갈청소년문화의집 내 시설 이용을 효율적으로 관리하기 위한 관리자 전용 데스크톱 애플리케이션

---

## 📌 주요 기능

### ✅ 1. 시설 타이머 관리
- 각 시설마다 **개별 타이머**를 제공하여 사용 시간 관리
- 타이머 시작, 일시정지, 초기화 기능 제공
- **수동 시간 설정** 기능 (분 단위 입력 가능)
- 타이머 종료 시 상태 자동 변경

지원 시설:
- PC 1~4번
- 닌텐도
- 노래방
- 패드민턴

---

### ✅ 2. 예약자 관리
- 예약자 1~10번까지의 슬롯 제공
- 각 예약자 슬롯에 사용자 이름, 이용 시간 등 표시
- `시설 이용` 버튼을 눌러 **해당 예약자를 사용자로 전환**하고 타이머 자동 시작
- 예약자 리스트 **수정, 초기화, 제거** 기능

---

### ✅ 3. 시설 상태 표시 및 제어
- 각 시설은 `사용 가능`, `사용 중`, `사용 불가` 상태로 구분
- 버튼을 통해 수동으로 상태 전환 가능
- 타이머 또는 예약자 상태와 **연동되어 자동 변경**

---

### ✅ 4. 공지사항 등록
- 공지사항 텍스트 입력 및 등록 기능
- **이미지 업로드** 지원 (jpeg, png 등)
- 메인 화면에 공지 이미지와 함께 표시 가능

---

### ✅ 5. 회원 관리
- 사용자 이름 + 생일 기반 **간편 로그인**
- 관리자는 회원 정보를 등록, 수정, 삭제 가능
- 로그인 기록은 DB 연동 또는 파일 저장 기능과 연계 예정

---

## 🧠 객체지향 설계 원칙 적용 (SOLID)

| 원칙 | 적용 예시 |
|------|-----------|
| SRP (단일 책임 원칙) | `ComputerFacility`, `SimpleFacility`, `ReservationManager` 각각의 역할 분리 |
| OCP (개방-폐쇄 원칙) | `Facility` 기반 클래스에 가상 함수 사용하여 확장 가능하도록 설계 |
| LSP (리스코프 치환 원칙) | `ComputerFacility`, `SimpleFacility`는 모두 `Facility`를 대체 가능 |
| ISP (인터페이스 분리 원칙) | 불필요한 UI 제어는 `MainWindow`에서만 수행, 기능별 로직만 각 클래스에 유지 |
| DIP (의존 역전 원칙) | `MainController`는 구체 클래스가 아닌 추상 클래스에 의존하도록 설계 가능 |

---

## 🧱 주요 클래스 구조

```plaintext
├── MainWindow (UI 중심)
│   ├── MainController
│       ├── ComputerFacility (PC-1 ~ PC-4)
│       ├── SimpleFacility (닌텐도, 노래방, 패드민턴)
│       ├── ReservationManager
│       └── MemberManager
├── Facility (추상 클래스)
│   └── 각 시설별 구현체 상속

# Unreal Tetris

## 프로젝트 개요
 Unreal Engine 5를 사용하여 구현한 테트리스 게임입니다.

## 기능
- 7가지 테트리스 피스 (I, O, T, S, Z, J, L)
- 실시간 게임 플레이
- 점수 및 레벨 시스템
- 라인 클리어 효과
- 게임 오버 처리

## 프로젝트 구조
```
UnrealTetris/
├── UnrealTetris.uproject    # Unreal 프로젝트 설정 파일
├── CMakeLists.txt           # CMake 빌드 설정
├── Source/
│   └── UnrealTetris/
│       ├── UnrealTetris.h      # 모듈 헤더
│       ├── UnrealTetris.cpp    # 모듈 구현
│       ├── UnrealTetrisGameMode.h/cpp  # 게임 모드
│       ├── UnrealTetrisPawn.h/cpp    # 플레이어 컨트롤
│       ├── UnrealTetrisPiece.h/cpp   # 테트리스 피스
│       └── UnrealTetris.Build.cs     # 모듈 빌드 설정
└── Content/                   # 에셋 폴더
    ├── Textures/
    └── Materials/
```

## 빌드 방법
1. Unreal Engine 5.4 이상 설치
2. 프로젝트 루트에서 `UnrealTetris.uproject` 파일 더블클릭
3. Visual Studio에서 Solution 로드
4. Build > Build All 빌드

## 게임 컨트롤
- 좌측/우측: 피스 이동
- 회전: 피스 회전
- 하단: 빠른 하강 (드롭)

## 개발 정보
- **언어**: C++ (Unreal Engine)
- **버전**: v1.1.0 (코드 수정 완료)
- **제작일**: 2026-10-09
- **마지막 수정**: 2026-10-09
- **빌드 상태**: 코드 수정 완료 (실제 빌드를 위해서는 Unreal Engine 5.6 설치 필요)

## 최근 수정 사항 (v1.1.0)
- 헤더 파일 경로 오류 수정 (TetrisPiece.h → UnrealTetrisPiece.h)
- 미사용 코드 정리
- 검증 보고서 업데이트

## 라이선스
이 프로젝트는 교육 목적으로 제작되었습니다.
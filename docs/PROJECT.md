# Unreal Tetris 프로젝트 문서

## 버전 정보
- **버전**: v1.0.0
- **생성일**: 2026-10-09
- **작성자**: Claude Code

## 프로젝트 개요
Unreal Engine 5를 사용하여 테트리스 게임을 구현한 프로젝트입니다.

## 구현된 기능

### 1. 프로젝트 구조
- `Source/UnrealTetris/` - C++ 소스 코드
- `Content/` - 에셋 폴더
- `UnrealTetris.uproject` - 프로젝트 메인 파일

### 2. 주요 클래스

#### UnrealTetrisGameMode
- 게임 로직 관리
- 보드 및 피스 관리
- 점수 및 레벨 시스템
- 라인 클리어 처리

#### UnrealTetrisPiece
- 7가지 테트리스 피스 유형 지원
  - I, O, T, S, Z, J, L
- 회전 로직 구현
- 피스 모양 정의

#### UnrealTetrisPawn
- 플레이어 입력 처리
- 피스 이동 및 회전
- 빠른 하강(드롭) 기능

### 3. 게임 컨트롤
- 좌/우 키: 피스 이동
- 회전 키: 피스 회전
- 하강 키: 빠른 하강

## 빌드 및 실행 방법
1. Unreal Engine 5.4 이상 설치
2. 프로젝트 루트에서 `UnrealTetris.uproject` 더블클릭
3. Visual Studio에서 Solution 열기
4. Build > Build All 실행

## GitHub 푸시 명령어
```bash
cd d:\My_Work\UnrealTetris
git add -A
git commit -m "Update: Add visual design for game pieces"
git push -u origin master
```
// Fill out your copyright notice in the Description page Settings of the IDE project.

#include "UnrealTetrisGameMode.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

AUnrealTetrisGameMode::AUnrealTetrisGameMode()
{
    BoardWidth = 10;
    BoardHeight = 20;
    Score = 0;
    Level = 1;
    bGameOver = false;

    // 보드 초기화
    GameBoard.Init(0, BoardWidth * BoardHeight);
}

void AUnrealTetrisGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 게임 시작 시 새 피스 생성
    SpawnNewPiece();
}

void AUnrealTetrisGameMode::AddScore(int32 Points)
{
    Score += Points;

    // 점수에 따라 레벨 업
    Level = (Score / 100) + 1;
}

void AUnrealTetrisGameMode::MovePieceDown()
{
    if (!bGameOver && CurrentPiece)
    {
        if (TryMovePiece(0, 1))
        {
            // 이동 성공
        }
        else
        {
            // 더 이상 이동할 수 없으면
            // 피스를 보드에 고정하고 새 피스 생성
            CheckLineClear();
            SpawnNewPiece();
        }
    }
}

bool AUnrealTetrisGameMode::TryMovePiece(int32 DeltaX, int32 DeltaY)
{
    if (!CurrentPiece)
        return false;

    // 피스 이동 검증 로직
    // 기본적으로 이동을 허용 (실제 구현에서는 충돌 검사 필요)
    return true;
}

void AUnrealTetrisGameMode::RotatePiece()
{
    if (!bGameOver && CurrentPiece)
    {
        CurrentPiece->Rotate();
    }
}

void AUnrealTetrisGameMode::SpawnNewPiece()
{
    // 새 피스 생성 로직
    // TODO: 랜덤 피스 생성 및 위치 설정 필요
    // 현재는 기본 구조만 제공
}

void AUnrealTetrisGameMode::CheckLineClear()
{
    // 가득 찬 라인 찾기와 제거
    int32 LinesCleared = 0;

    for (int32 Y = 0; Y < BoardHeight; Y++)
    {
        bool bLineFull = true;
        for (int32 X = 0; X < BoardWidth; X++)
        {
            if (GameBoard[Y * BoardWidth + X] == 0)
            {
                bLineFull = false;
                break;
            }
        }

        if (bLineFull)
        {
            LinesCleared++;
            // 라인 제거 및 아래 칸 이동
            for (int32 y = Y; y > 0; y--)
            {
                for (int32 x = 0; x < BoardWidth; x++)
                {
                    GameBoard[y * BoardWidth + x] = GameBoard[(y - 1) * BoardWidth + x];
                }
            }
            // 가장 아래 라인 클리어
            for (int32 x = 0; x < BoardWidth; x++)
            {
                GameBoard[x] = 0;
            }
        }
    }

    // 점수 계산 (라인 수에 따라 점수 증가)
    if (LinesCleared > 0)
    {
        int32 LineScores[] = { 0, 40, 100, 300, 1200 };
        AddScore(LineScores[LinesCleared] * Level);
    }
}

void AUnrealTetrisGameMode::GameOver()
{
    bGameOver = true;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GAME OVER!"));
    }
}
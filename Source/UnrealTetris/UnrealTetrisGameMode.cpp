// Fill out your copyright notice in the Description page Settings.

#include "UnrealTetrisGameMode.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

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

    // 레벨에 따라 하강 속도 조정
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
            *FString::Printf(TEXT("Level: %d, Score: %d"), Level, Score));
    }
}

void AUnrealTetrisGameMode::MovePieceDown()
{
    if (!bGameOver && CurrentPiece)
    {
        if (TryMovePiece(0, 1))
        {
            // 이동 성공 - 피스 위치 업데이트
        }
        else
        {
            // 더 이상 이동할 수 없으면
            // 피스를 보드에 고정하고 새 피스 생성
            PlacePieceOnBoard();
            CheckLineClear();
            SpawnNewPiece();
        }
    }
}

bool AUnrealTetrisGameMode::TryMovePiece(int32 DeltaX, int32 DeltaY)
{
    if (!CurrentPiece)
        return false;

    // 현재 피스의 위치 가져오기
    TArray<FVector2D> CurrentPositions = CurrentPiece->GetBlockPositions();

    // 새 위치 계산
    TArray<FVector2D> NewPositions;
    for (const FVector2D& Pos : CurrentPositions)
    {
        NewPositions.Add(FVector2D(Pos.X + DeltaX, Pos.Y + DeltaY));
    }

    // 충돌 검사
    for (const FVector2D& Pos : NewPositions)
    {
        // 보드 밖으로 벗어나는지 확인
        if (Pos.X < 0 || Pos.X >= BoardWidth || Pos.Y < 0 || Pos.Y >= BoardHeight)
        {
            return false;
        }

        // 빈칸이 아닌지 확인 (이미 배치된 피스가 있는지)
        int32 BoardIndex = FMath::RoundToInt(Pos.Y) * BoardWidth + FMath::RoundToInt(Pos.X);
        if (GameBoard[BoardIndex] != 0)
        {
            return false;
        }
    }

    // 이동 가능 - 위치 업데이트
    CurrentPiece->SetPosition(
        CurrentPiece->Position.X + DeltaX,
        CurrentPiece->Position.Y + DeltaY
    );

    return true;
}

void AUnrealTetrisGameMode::RotatePiece()
{
    if (!bGameOver && CurrentPiece)
    {
        // 회전 전 위치 저장
        FVector2D OldPos = CurrentPiece->Position;

        CurrentPiece->Rotate();

        // 회전 후 충돌 검사 (필요시 되돌리기)
        TArray<FVector2D> NewPositions = CurrentPiece->GetBlockPositions();
        for (const FVector2D& Pos : NewPositions)
        {
            // 충돌 검사 로직
            if (Pos.X < 0 || Pos.X >= BoardWidth || Pos.Y < 0 || Pos.Y >= BoardHeight)
            {
                // 범위 초과 - 되돌리기
                CurrentPiece->Rotation = (CurrentPiece->Rotation + Shapes.Num() - 1) % Shapes.Num();
                return;
            }
        }
    }
}

void AUnrealTetrisGameMode::SpawnNewPiece()
{
    // 새 피스 생성 로직
    // 랜덤 피스 생성 (현재는 I 파이프로 고정)

    if (GetWorld())
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Name = FName("NewPiece");

        // 7가지 피스 중 랜덤 선택
        ETetrisPieceType PieceType = ETetrisPieceType::I; // TODO: 랜덤 생성

        FVector SpawnLocation = FVector(BoardWidth * 0.5f * 60.0f, 0.0f, BoardHeight * -60.0f);
        FRotator SpawnRotation = FRotator(0, 0, 0);

        CurrentPiece = GetWorld()->SpawnActor<ATetrisPiece>(ATetrisPiece::StaticClass(),
            SpawnLocation, SpawnRotation, SpawnParams);

        if (CurrentPiece)
        {
            CurrentPiece->Initialize(PieceType);

            // 보드 위쪽 중앙에 스폰
            CurrentPiece->Position = FVector2D(BoardWidth / 2, 0);
        }
        else
        {
            // 피스 생성 실패 - 게임 오버
            GameOver();
        }
    }
}

void AUnrealTetrisGameMode::PlacePieceOnBoard()
{
    if (!CurrentPiece)
        return;

    // 피스를 보드에 고정
    TArray<FVector2D> Positions = CurrentPiece->GetBlockPositions();

    for (const FVector2D& Pos : Positions)
    {
        int32 X = FMath::RoundToInt(Pos.X);
        int32 Y = FMath::RoundToInt(Pos.Y);

        if (X >= 0 && X < BoardWidth && Y >= 0 && Y < BoardHeight)
        {
            int32 Index = Y * BoardWidth + X;
            GameBoard[Index] = 1;  // 1 = 배치된 블록
        }
    }
}

void AUnrealTetrisGameMode::CheckLineClear()
{
    // 가득 찬 라인 찾기와 제거
    int32 LinesCleared = 0;

    for (int32 Y = BoardHeight - 1; Y >= 0; Y--)
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

            // 같은 위치의 다른 라인이 채워졌을 수 있으므로 다시 체크
            Y++;
        }
    }

    // 점수 계산 (라인 수에 따라 점수 증가)
    if (LinesCleared > 0)
    {
        int32 LineScores[] = { 0, 40, 100, 300, 1200 };
        AddScore(LineScores[LinesCleared > 4 ? 4 : LinesCleared] * Level);
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
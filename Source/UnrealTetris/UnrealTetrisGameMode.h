// Fill out your copyright notice in the Description page Settings of the IDE project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealTetrisPiece.h"
#include "UnrealTetrisGameMode.generated.h"

UCLASS()
class UNREALTETRIS_API AUnrealTetrisGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AUnrealTetrisGameMode();

protected:
    virtual void BeginPlay() override;

public:
    /** 현재 게임 보드 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    TArray<int32> GameBoard;

    /** 보드 너비 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetris")
    int32 BoardWidth;

    /** 보드 높이 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetris")
    int32 BoardHeight;

    /** 현재 움직이는 테트리스 피스 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    ATetrisPiece* CurrentPiece;

    /** 다음에 나올 피스 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    ATetrisPiece* NextPiece;

    /** 점수 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    int32 Score;

    /** 레벨 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    int32 Level;

    /** 게임 오버 여부 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    bool bGameOver;

    /** 점수 증가 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void AddScore(int32 Points);

    /** 피스 하강 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void MovePieceDown();

    /** 피스 회전 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void RotatePiece();

    /** 피스 이동 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    bool TryMovePiece(int32 DeltaX, int32 DeltaY);

    /** 새 피스 생성 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void SpawnNewPiece();

    /** 라인 제거 확인 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void CheckLineClear();

    /** 게임 오버 처리 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void GameOver();
};
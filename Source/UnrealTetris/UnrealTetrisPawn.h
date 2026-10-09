// Fill out your copyright notice in the Description page Settings of the IDE project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnrealTetrisPiece.h"
#include "UnrealTetrisPawn.generated.h"

class UBoxComponent;

/**
 * 테트리스 플레이어Pawn
 */
UCLASS()
class UNREALTETRIS_API AUnrealTetrisPawn : public APawn
{
    GENERATED_BODY()

public:
    AUnrealTetrisPawn();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    /** 이동 입력 처리 */
    UFUNCTION()
    void MoveLeft();

    UFUNCTION()
    void MoveRight();

    UFUNCTION()
    void RotatePiece();

    UFUNCTION()
    void DropPiece();

protected:
    /** 콜리전 컴포넌트 */
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionBox;

    /** 현재 제어 중인 피스 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    ATetrisPiece* ControlledPiece;

    /** 피스 움직임 속도 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetris")
    float MoveSpeed;

    /** 하강 속도 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetris")
    float FallSpeed;

    /** 타임 머니터링 */
    float TimeSinceLastFall;
};
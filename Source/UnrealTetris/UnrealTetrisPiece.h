// Fill out your copyright notice in the Description page Settings of the IDE project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisPiece.generated.h"

// 테트리스 피스의 형상을 정의하는 enum
UENUM(BlueprintType)
enum class ETetrisPieceType : uint8
{
    None    UMETA(DisplayName = "None"),
    I       UMETA(DisplayName = "I"),
    O       UMETA(DisplayName = "O"),
    T       UMETA(DisplayName = "T"),
    S       UMETA(DisplayName = "S"),
    Z       UMETA(DisplayName = "Z"),
    J       UMETA(DisplayName = "J"),
    L       UMETA(DisplayName = "L")
};

// 피스의 회전 상태
USTRUCT(BlueprintType)
struct FTetrisPieceShape
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FVector2D> Blocks;

    FTetrisPieceShape() {}

    FTetrisPieceShape(TArray<FVector2D> InBlocks) : Blocks(InBlocks) {}
};

/**
 * 테트리스 피스 액터
 */
UCLASS()
class UNREALTETRIS_API ATetrisPiece : public AActor
{
    GENERATED_BODY()

public:
    ATetrisPiece();

    /** 피스 유형 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    ETetrisPieceType PieceType;

    /** 현재 회전 상태 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    int32 Rotation;

    /** 피스의 위치 (그리드 좌표) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    FVector2D Position;

    /** 피스의 색상 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    FLinearColor Color;

    /** 피스의 블록들 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tetris")
    TArray<FTetrisPieceShape> Shapes;

    /** 초기화 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void Initialize(ETetrisPieceType InType);

    /** 회전 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void Rotate();

    /** 위치 설정 함수 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    void SetPosition(float X, float Y);

    /** 블록 위치 가져오기 */
    UFUNCTION(BlueprintCallable, Category = "Tetris")
    TArray<FVector2D> GetBlockPositions() const;
};
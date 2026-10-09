// Fill out your copyright notice in the Description page Settings.

#include "UnrealTetrisPawn.h"
#include "UnrealTetrisGameMode.h"
#include "UnrealTetrisPiece.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

AUnrealTetrisPawn::AUnrealTetrisPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 콜리전 박스 생성
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));

    MoveSpeed = 1.0f;
    FallSpeed = 1.0f;
    TimeSinceLastFall = 0.0f;
    ControlledPiece = nullptr;
}

void AUnrealTetrisPawn::BeginPlay()
{
    Super::BeginPlay();

    // 시작 시점에 피스 생성 시도
    // GameMode에 접근하여 SpawnNewPiece 호출
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->SpawnNewPiece();
        }
    }
}

void AUnrealTetrisPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 입력 바인딩 - 화살표 키와 WASD 지원
    PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealTetrisPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveLeft", this, &AUnrealTetrisPawn::MoveLeft);
    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &AUnrealTetrisPawn::RotatePiece);
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AUnrealTetrisPawn::DropPiece);
}

void AUnrealTetrisPawn::MoveLeft(float AxisValue)
{
    if (AxisValue != 0.f && GetWorld() && GetWorld()->GetAuthGameMode())
    {
        AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            // 왼쪽으로 이동 (음수값이면 왼쪽)
            GameMode->TryMovePiece(-1, 0);
        }
    }
}

void AUnrealTetrisPawn::MoveRight(float AxisValue)
{
    if (AxisValue != 0.f && GetWorld() && GetWorld()->GetAuthGameMode())
    {
        AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            // 오른쪽으로 이동 (양수값이면 오른쪽)
            GameMode->TryMovePiece(1, 0);
        }
    }
}

void AUnrealTetrisPawn::RotatePiece()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->RotatePiece();
        }
    }
}

void AUnrealTetrisPawn::DropPiece()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            // 하단까지 즉시 하강
            // 하강이 가능한 위치까지 하강
            while (GameMode->TryMovePiece(0, 1))
            {
                // 이동 가능하면 계속 하강
            }
            // 이동 불가능하면 피스 고정
            GameMode->MovePieceDown();
        }
    }
}

// Tick 함수 - 자동 하강 처리
void AUnrealTetrisPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastFall += DeltaTime;

    // 자동 하강 로직
    if (TimeSinceLastFall >= FallSpeed)
    {
        TimeSinceLastFall = 0.0f;

        if (GetWorld() && GetWorld()->GetAuthGameMode())
        {
            AUnrealTetrisGameMode* GameMode = Cast<AUnrealTetrisGameMode>(GetWorld()->GetAuthGameMode());
            if (GameMode)
            {
                GameMode->MovePieceDown();
            }
        }
    }
}
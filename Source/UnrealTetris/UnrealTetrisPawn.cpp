// Fill out your copyright notice in the Description page Settings of the IDE project.

#include "UnrealTetrisPawn.h"
#include "Components/BoxComponent.h"
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
}

void AUnrealTetrisPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 입력 바인딩
    PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealTetrisPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveLeft", this, &AUnrealTetrisPawn::MoveLeft);
    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &AUnrealTetrisPawn::RotatePiece);
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AUnrealTetrisPawn::DropPiece);
}

void AUnrealTetrisPawn::MoveLeft()
{
    if (ControlledPiece)
    {
        // 피스를 왼쪽으로 이동
        FVector2D NewPos = ControlledPiece->GetBlockPositions()[0];
        // MoveDirection은 피스의 이동을 처리하는 로직
    }
}

void AUnrealTetrisPawn::MoveRight()
{
    if (ControlledPiece)
    {
        // 피스를 오른쪽으로 이동
    }
}

void AUnrealTetrisPawn::RotatePiece()
{
    if (ControlledPiece)
    {
        ControlledPiece->Rotate();
    }
}

void AUnrealTetrisPawn::DropPiece()
{
    if (ControlledPiece)
    {
        // 하단까지 즉시 하강
    }
}

// Tick 함수는 필요에 따라 구현
void AUnrealTetrisPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastFall += DeltaTime;

    // 자동 하강 로직 (임시 구현)
    if (TimeSinceLastFall >= FallSpeed)
    {
        TimeSinceLastFall = 0.0f;
        // TODO: 하강 처리 로직 추가 필요
    }
}
// Fill out your copyright notice in the Description page Settings of the IDE project.

#include "UnrealTetrisPiece.h"
#include "Engine/Engine.h"

ATetrisPiece::ATetrisPiece()
{
    PrimaryActorTick.bCanEverTick = false;
    Rotation = 0;
    Position = FVector2D(0, 0);
    PieceType = ETetrisPieceType::None;

    // Colors for different piece types
    TMap<ETetrisPieceType, FLinearColor> PieceColors;
    PieceColors.Add(ETetrisPieceType::I, FLinearColor::Cyan);
    PieceColors.Add(ETetrisPieceType::O, FLinearColor::Yellow);
    PieceColors.Add(ETetrisPieceType::T, FLinearColor::Magenta);
    PieceColors.Add(ETetrisPieceType::S, FLinearColor::Green);
    PieceColors.Add(ETetrisPieceType::Z, FLinearColor::Red);
    PieceColors.Add(ETetrisPieceType::J, FLinearColor::Blue);
    PieceColors.Add(ETetrisPieceType::L, FLinearColor::Orange);
}

void ATetrisPiece::Initialize(ETetrisPieceType InType)
{
    PieceType = InType;
    Rotation = 0;

    // 피스 유형에 따라 모양 설정
    switch (InType)
    {
    case ETetrisPieceType::I:
        Color = FLinearColor::Cyan;
        Shapes.Add(FTetrisPieceShape({ FVector2D(-1, 0), FVector2D(0, 0), FVector2D(1, 0), FVector2D(2, 0) }));
        Shapes.Add(FTetrisPieceShape({ FVector2D(0, -1), FVector2D(0, 0), FVector2D(0, 1), FVector2D(0, 2) }));
        break;
    case ETetrisPieceType::O:
        Color = FLinearColor::Yellow;
        Shapes.Add(FTetrisPieceShape({ FVector2D(0, 0), FVector2D(1, 0), FVector2D(0, 1), FVector2D(1, 1) }));
        break;
    case ETetrisPieceType::T:
        Color = FLinearColor::Magenta;
        Shapes.Add(FTetrisPieceShape({ FVector2D(-1, 0), FVector2D(0, 0), FVector2D(1, 0), FVector2D(0, 1) }));
        Shapes.Add(FTetrisPieceShape({ FVector2D(0, -1), FVector2D(0, 0), FVector2D(1, 0), FVector2D(0, 1) }));
        break;
    case ETetrisPieceType::S:
        Color = FLinearColor::Green;
        Shapes.Add(FTetrisPieceShape({ FVector2D(0, 0), FVector2D(1, 0), FVector2D(-1, 1), FVector2D(0, 1) }));
        break;
    case ETetrisPieceType::Z:
        Color = FLinearColor::Red;
        Shapes.Add(FTetrisPieceShape({ FVector2D(-1, 0), FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1) }));
        break;
    case ETetrisPieceType::J:
        Color = FLinearColor::Blue;
        Shapes.Add(FTetrisPieceShape({ FVector2D(-1, 0), FVector2D(0, 0), FVector2D(0, 1), FVector2D(0, 2) }));
        break;
    case ETetrisPieceType::L:
        Color = FLinearColor::Orange;
        Shapes.Add(FTetrisPieceShape({ FVector2D(0, 0), FVector2D(0, 1), FVector2D(0, 2), FVector2D(1, 2) }));
        break;
    }
}

void ATetrisPiece::Rotate()
{
    Rotation = (Rotation + 1) % Shapes.size();
}

void ATetrisPiece::SetPosition(float X, float Y)
{
    Position.X = X;
    Position.Y = Y;
}

TArray<FVector2D> ATetrisPiece::GetBlockPositions() const
{
    TArray<FVector2D> Positions;

    if (Shapes.size() > 0 && Rotation < Shapes.size())
    {
        const FTetrisPieceShape& Shape = Shapes[Rotation];
        for (const FVector2D& Block : Shape.Blocks)
        {
            Positions.Add(FVector2D(Position.X + Block.X, Position.Y + Block.Y));
        }
    }

    return Positions;
}
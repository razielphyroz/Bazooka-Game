// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySlider.h"

AEnemySlider::AEnemySlider()
{
	VelX = 10;
}

void AEnemySlider::BeginPlay()
{
	Super::BeginPlay();
	Lifes = 3;
	InitialPos = GetActorLocation();
}

void AEnemySlider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AEnemySlider::Move()
{
	if (Direction == 0) {
		SetActorLocation(FVector(GetActorLocation().X + VelX, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X >= InitialPos.X + 200.0f) {
			Direction = 1;
		}
	} else {
		SetActorLocation(FVector(GetActorLocation().X - VelX, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X <= InitialPos.X - 200.0f) {
			Direction = 0;
		}
	}
}
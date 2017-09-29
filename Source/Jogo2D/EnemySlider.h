// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemySlider.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API AEnemySlider : public AEnemy
{
	GENERATED_BODY()

	AEnemySlider();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:

	FVector InitialPos;

	int8 Direction;

	void Move();

	float VelX;
	
};

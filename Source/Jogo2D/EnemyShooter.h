// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyShooter.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API AEnemyShooter : public AEnemy
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> MyBullet;

	void Shoot();

	FTimerHandle TurnDown;

	float DistanceToShoot;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "EnemyBullet.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API AEnemyBullet : public ABullet
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};

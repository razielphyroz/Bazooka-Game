// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "BazookaBullet.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API ABazookaBullet : public ABullet
{
	GENERATED_BODY()

	ABazookaBullet();

private:

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
		class USphereComponent* CollectArea;
};

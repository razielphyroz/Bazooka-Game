// Fill out your copyright notice in the Description page of Project Settings.

#include "Punch.h"
#include "Enemy.h"

APunch::APunch()
{
	InitialLifeSpan = 0.1f;
}



void APunch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AEnemy::StaticClass())) {
		Destroy();
	}
}


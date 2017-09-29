// Fill out your copyright notice in the Description page of Project Settings.

#include "BazookaBullet.h"
#include "Personagem.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Enemy.h"

ABazookaBullet::ABazookaBullet()
{
	CollectArea = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollectArea"));
	CollectArea->SetupAttachment(RootComponent);
}

void ABazookaBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AEnemy::StaticClass()) && !OtherActor->IsA(APersonagem::StaticClass())) {
		TArray<AActor*> MyArray;
		CollectArea->GetOverlappingActors(MyArray);
		for (int i = 0; i < MyArray.Num(); i++) {
			if (MyArray[i]->IsA(AEnemy::StaticClass())) {
				MyArray[i]->Destroy();
			}
		}
		Destroy();
	}
}

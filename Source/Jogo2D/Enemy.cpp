// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "PaperSpriteComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Personagem.h"
#include "Punch.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MySprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetupAttachment(RootComponent);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	CollisionComp->SetupAttachment(Sprite);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr) {
		if (OtherActor->IsA(ABullet::StaticClass()) && (!OtherActor->IsA(AEnemyBullet::StaticClass()) || OtherActor->IsA(APunch::StaticClass()))) {
			Lifes--;
			UE_LOG(LogTemp, Warning, TEXT("Inimigo atingido pelo personagem..."));
			if (Lifes <= 0) {
				UE_LOG(LogTemp, Warning, TEXT("Inimigo morreu..."));
				Destroy();
			}
		} else if (OtherActor->IsA(APersonagem::StaticClass())) {
			APersonagem* Personagem = Cast<APersonagem>(OtherActor);
			Personagem->SetLifes(Personagem->GetLifes() - 1);
			UE_LOG(LogTemp, Warning, TEXT("Personagem encostou no inimigo (-1 de LIFE)"));
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


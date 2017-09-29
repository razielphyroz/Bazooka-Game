// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShooter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Personagem.h"
#include "Bullet.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/TimerManager.h"

void AEnemyShooter::BeginPlay()
{
	Super::BeginPlay();
	Lifes = 3;
	DistanceToShoot = 500.0f;
	GetWorldTimerManager().SetTimer(TurnDown, this,	&AEnemyShooter::Shoot, 0.5f, true);
}

void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void AEnemyShooter::Shoot()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn) {
		APersonagem* Personagem = Cast<APersonagem>(Pawn);
		if (Personagem->GetActorLocation().X >= GetActorLocation().X - DistanceToShoot && Personagem->GetActorLocation().X <= GetActorLocation().X + DistanceToShoot) {
			UWorld* World = GetWorld();
			if (World) {
				FActorSpawnParameters SpawnParam;
				if (Personagem->GetActorLocation().X > GetActorLocation().X) {
					ABullet* Bullet = World->SpawnActor<ABullet>(MyBullet, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParam);
				}
				else {
					ABullet* Bullet = World->SpawnActor<ABullet>(MyBullet, GetActorLocation(), FRotator(0.0f, 180.0f, 0.0f), SpawnParam);
				}
			}
		}
	}
	
}

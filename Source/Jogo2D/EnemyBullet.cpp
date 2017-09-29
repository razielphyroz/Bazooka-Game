// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBullet.h"
#include "Personagem.h"

void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Bala do inimigo colidiu com o personagem..."));
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetLifes(Personagem->GetLifes() - 1);
		Destroy();
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TPS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Fire(const FVector& Direction) const;
	void PlayHitEffect(FTransform HitTransform);


	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	FORCEINLINE void SetAttackDamage(float NewAttackDamage) { AttackDamage = NewAttackDamage; }
	FORCEINLINE float GetAttackDamage() { return AttackDamage; }


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphercCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> MeshComponet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;

	UPROPERTY(EditAnywhere, Category = HitEffect)
	TObjectPtr<class UParticleSystem > HitEffect;

	UPROPERTY(EditAnywhere, Category = Properties)
	float InitSpeed = 30000.0f;

	UPROPERTY(EditAnywhere, Category = Properties)
	float MaxSpeed = 30000.0f;

	UPROPERTY(VisibleAnywhere, Category = Properties)
	float AttackDamage = 0.0f;
	

};

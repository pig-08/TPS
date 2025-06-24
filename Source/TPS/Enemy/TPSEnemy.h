// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSEnemy.generated.h"

UCLASS()
class TPS_API ATPSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	void SetHp(float NewHp);
	void Hit();
	void Dead();

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHp = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxHp = 100.0f;
};

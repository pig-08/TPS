// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"
#include "Enemy/TPSEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"


UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Enemy/AM_EnemyHit.AM_EnemyHit'"));
	if (HitMontageRef.Succeeded())
	{
		HitMontage = HitMontageRef.Object;
	}
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ATPSEnemy>(TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;

	if (MovementComponent == nullptr)
		return;

	Velocity = MovementComponent->Velocity;

	bShouldMove = (Velocity.Size2D() > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
}

void UEnemyAnimInstance::PlayHitMontage()
{
	int32 Index = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("Hit%d"), Index);
	Montage_Play(HitMontage);
	Montage_JumpToSection(*SectionName);
}

void UEnemyAnimInstance::PlayDeadMontage()
{
	Montage_Play(HitMontage);
	Montage_JumpToSection(TEXT("Dead"));
}

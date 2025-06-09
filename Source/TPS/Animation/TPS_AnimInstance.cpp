// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TPS_AnimInstance.h"
#include "Character/TPSCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UTPS_AnimInstance::UTPS_AnimInstance()
{

}

void UTPS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ATPSCharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UTPS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;

	if (MovementComponent == nullptr)
		return;

	Velocity = MovementComponent->Velocity;

	FVector ForwardVector = Character->GetActorForwardVector();
	ForwardSpeed = FVector::DotProduct(ForwardVector, Velocity);
	FVector RightVector = Character->GetActorRightVector();
	RightSpeed = FVector::DotProduct(RightVector, Velocity);

	bShouldMove = (Velocity.Size2D() > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);

	bIsFalling = MovementComponent->IsFalling();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework//ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphercCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(SphercCollision);
	SphercCollision->SetSphereRadius(6.0f);
	SphercCollision->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	MeshComponet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponet->SetupAttachment(GetRootComponent());
	MeshComponet->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshComponet->SetRelativeLocation(FVector(-5.0f, 0, 0));
	MeshComponet->SetRelativeRotation(FRotator(0.0f, - 90.0f, 0.0f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_40mm_G.SM_Shell_40mm_G'"));

	if (MeshRef.Succeeded())
	{
		MeshComponet->SetStaticMesh(MeshRef.Object);
	}

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MovementComponent->SetUpdatedComponent(GetRootComponent());
	MovementComponent->InitialSpeed = InitSpeed;
	MovementComponent->MaxSpeed = MaxSpeed;
	MovementComponent->bRotationFollowsVelocity = false;
	MovementComponent->bShouldBounce = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitEffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/_Art/Effect/P_HitEffect.P_HitEffect'"));

	if (HitEffectRef.Succeeded())
	{
		HitEffect = HitEffectRef.Object;
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SphercCollision->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Fire(const FVector& Direction) const
{
	MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
}

void ABullet::PlayHitEffect(FTransform HitTransform)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitTransform);
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Bullet Hit")));

	FTransform BullectTransform;
	BullectTransform.SetLocation(Hit.ImpactPoint);
	PlayHitEffect(BullectTransform);

	Destroy();
}


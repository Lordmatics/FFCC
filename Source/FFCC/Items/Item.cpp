// Fan Made FFCC - July 28th 2017

#include "Item.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FFCC/DataAssets/Item/ItemDataAsset.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;



	MyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollision"));
	MyCollision->SetupAttachment(MyRoot);
	MyCollision->SetSphereRadius(25.0f);
	MyCollision->SetCollisionProfileName(FName(TEXT("Interact")));

	MyItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyItem"));
	MyItem->SetupAttachment(MyCollision);
	MyItem->SetCollisionProfileName(FName(TEXT("Item")));
	MyItem->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnPickedUp()
{
	Destroy();
}

FItemData AItem::GetItemData() const
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->GetItemData();
	}
	return FItemData();
}
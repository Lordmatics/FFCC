// Fan Made FFCC - July 28th 2017

#include "PickupComponent.h"
//#include "FFCC/Items/Item.h"
//#include "FFCC/DataAssets/Item/ItemDataAsset.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...


}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	//ItemPtr = new FItemData();
	//ItemData = *ItemPtr;
	//delete ItemPtr;
	//ItemPtr = nullptr;
	//if (!GetOwner()) return;
	//FString Temp = GetOwner()->GetName();
	//Temp.RemoveAt(0, 3);
	//ItemName = Temp;

	//if (AItem* Owner = Cast<AItem>(GetOwner()) )
	//{
	//	FString Temp = Owner->ItemData.ItemName;
	//	Temp = Temp.Replace(TEXT(" "), TEXT(""));
	//	ItemName = Temp;
	//}

}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UPickupComponent::RegisterItem(const FItemData& ItemToRegister)
//{
//	//ItemData = ItemToRegister;
//}

//FItemData UPickupComponent::GetItemData()
//{
//	if (ItemDataAsset)
//	{
//		return ItemDataAsset->GetItemData();
//	}
//	return FItemData();
//}
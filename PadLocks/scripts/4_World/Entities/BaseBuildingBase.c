modded class BaseBuildingBase extends ItemBase
{
	
	Padlock GetPadlock(){
		int slot_id = InventorySlots.GetSlotIdFromString("Att_CombinationLock");
		if (slot_id != InventorySlots.INVALID){
			return  Padlock.Cast( GetInventory().FindAttachment(slot_id) ); 
		}
		return NULL;
	}
	
	bool CanUnlockDoor(PlayerBase player){
		Padlock lock = GetPadlock();
		if (lock){
			return lock.CanUnlock(player) && !IsOpened();
		}
		return true;
	}
	
	
	bool IsLocked()
	{
		Padlock lock = GetPadlock();
		if ( lock && lock.IsLocked() )
		{
			return true;
		}
		return false;
	}
}

modded class Fence extends BaseBuildingBase {

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionLockOpenFence);
	}

}
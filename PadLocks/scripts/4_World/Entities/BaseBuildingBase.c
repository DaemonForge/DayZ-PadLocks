modded class Fence extends ItemBase
{
	override bool IsOpen(){
		return IsOpened();
	}
}

modded class ItemBase  extends InventoryItem {

	Padlock GetPadlock() {
		return Padlock.Cast( GetAttachmentByType(Padlock) ); 
	}
	
	bool CanUnlockPadlock(PlayerIdentity player) {
		Padlock lock = GetPadlock();
		if (lock){
			return lock.CanUnlock(player);
		}
		return true;
	}
	
	bool IsPadlocked() {
		Padlock lock = GetPadlock();
		if ( lock && lock.IsLocked() )
		{
			return true;
		}
		return false;
	}
}

modded class Fence extends BaseBuildingBase {

	
	override bool IsLocked() {		
		return super.IsLocked() || IsPadlocked();
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionLockOpenFence);
		AddAction(ActionSetPadlockPin);
		AddAction(ActionOpenLockInterface);
	}

}
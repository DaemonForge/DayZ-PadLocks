class Padlock_Heavy extends Padlock {

}

class Padlock extends ItemBase {
	
	autoptr PadlockInterface m_PadlockInterface;
	
	autoptr TStringArray m_RemeberedPlayers;
	int m_Combination = -1;
	bool m_HasCombination = false;
	int m_LastAtemptTime = 0;
	protected LockAction m_LockActionPerformed 		= LockAction.NONE;
	protected EffectSound m_Sound;
	
	const string SOUND_LOCK_OPEN 			= "combinationlock_open_SoundSet";
	const string SOUND_LOCK_CLOSE 			= "combinationlock_close_SoundSet";
	
	void Padlock() {
		RegisterNetSyncVariableInt( "m_LockActionPerformed", 0, LockAction.COUNT );
		RegisterNetSyncVariableBool("m_HasCombination");
		HideAttached();
	}
	
	
	void SetInterface(PadlockInterface interface){
		m_PadlockInterface = interface;
	}
	
	void ClearInterface(){
		m_PadlockInterface = NULL;
	}
	
	void SetCombination(int pin){
		m_Combination = pin;
		if (m_Combination >= 0){
			m_HasCombination = true;
			LockServer(GetHierarchyRoot());
		} else {
			m_HasCombination = false;
		}
		SetSynchDirty();
	}
	
	override void OnStoreSave( ParamsWriteContext ctx ) {   
		super.OnStoreSave( ctx );
		
		//write data
		ctx.Write( m_Combination );
		ctx.Write( m_RemeberedPlayers );
	}
	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version ) {
		if ( !super.OnStoreLoad( ctx, version ) ){
			return false;
		}
		
		if ( !ctx.Read( m_Combination ) ) {
			m_Combination = -1;
			return false;
		}
		
		if ( !ctx.Read( m_RemeberedPlayers ) ) {
			m_RemeberedPlayers = new TStringArray;
			return false;
		}
		if (m_Combination >= 0){
			m_HasCombination = true;
		} else {
			m_HasCombination = false;
		}
		if (GetGame().IsServer()){
			SetSynchDirty();
		}
		return true;
	}
	
	bool IsLocked(){
		return (m_Combination > -1) || HasCombination();
	}
	
	override void AfterStoreLoad() {	
		super.AfterStoreLoad();		
		
		//Check combination lock	
		
		//synchronize
		Synchronize();
		if (m_Combination >= 0){
			m_HasCombination = true;
		} else {
			m_HasCombination = false;
		}
		if (GetGame().IsServer()){
			SetSynchDirty();
			EntityAI parent = GetHierarchyParent();
			if ( parent && parent.IsInherited( BaseBuildingBase ) && m_HasCombination) {
				LockServer( parent );
			}
		}
	}
	
	bool HasCombination(){
		return m_HasCombination;
	}
	
	// --- SYNCHRONIZATION
	void Synchronize() {
		if ( GetGame().IsServer() ) {
			SetSynchDirty();
			
			//UpdateVisuals();
		}
	}
	
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		UpdateSound();
		//update visuals (client)
		UpdateVisuals();
	}
	
	// --- VISUALS
	void UpdateVisuals()
	{
		if ( IsLockAttached() ) {
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( ShowAttached, 	0, false );
		} else {
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( HideAttached, 	0, false );
		}
	}
	
	protected void ShowAttached() {
		ShowSimpleSelection("FenceLock");
	}
	
	protected void HideAttached() {
		ShowSimpleSelection("FenceLock", false);
	}	
	// ---	
	
	void UpdateSound() {
		//was locked
		if ( m_LockActionPerformed == LockAction.LOCKED ) {
			SoundLockClose();
		}
		
		//was unlocked
		if ( m_LockActionPerformed == LockAction.UNLOCKED ) {
			SoundLockOpen();
		}
	}
	
	bool IsLockAttached() {
		ItemBase item = ItemBase.Cast(GetHierarchyParent());
		if ( item && item.GetInventory().HasAttachment(this) ) {
			return true;
		}
		
		return false;
	}
	
	private void ShowSimpleSelection(string selectionName, bool hide = true)
    {
        TStringArray selectionNames = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections",selectionNames);
        int selectionId = selectionNames.Find(selectionName);
        SetSimpleHiddenSelectionState(selectionId, hide);
    };
	
	
	void LockServer( EntityAI parent) {
		if ( IsLockAttached() ) {			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );		
			parent.GetInventory().SetSlotLock( inventory_location.GetSlot(), true );
			
			m_LockActionPerformed = LockAction.LOCKED;
			SetTakeable(false);
			Synchronize();
		}
		
	}
	
	void UnlockServer( EntityAI parent ){
		if ( IsLockAttached() ) {
			ItemBase item = ItemBase.Cast( parent );
			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );			
			item.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );			
	
			SetCombination(-1);
			ClearRemeberedPlayers();
			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			//synchronize
			Synchronize();
		}
	
	}
	
	void UnlockAndDropServer( EntityAI player, EntityAI parent ) {
		if ( IsLockAttached() ) {
			ItemBase item = ItemBase.Cast( parent );
			
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );			
			item.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );			
			
			if (player) {
				player.ServerDropEntity( this );
			} else {
				parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
			}
			PlaceOnSurface();
			SetCombination(-1);
			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			//synchronize
			Synchronize();
		}
	}
	
	
	override void OnWasDetached( EntityAI parent, int slot_id )
	{
		super.OnWasDetached(parent, slot_id);
		
		UpdateVisuals();
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		int pin;
		int curtime = GetGame().GetTime();
		int newtime = curtime + 1900;
		
		Param1<int> resetReq;
		Param1<int> UnlockReq;
		if (rpc_type == PADLOCK_RESETREQUEST && GetGame().IsClient()) {
			if (ctx.Read(resetReq)) {
				if (resetReq.param1 == PadLockRespones.SUCCESS){
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_PadlockInterface.OnReset, 10);
					m_LockActionPerformed == LockAction.UNLOCKED;
				}
				if (resetReq.param1 == PadLockRespones.INVALIDPIN){
					m_PadlockInterface.OnInvalidPin();
					m_LockActionPerformed == LockAction.LOCKED;
				}
				if (resetReq.param1 == PadLockRespones.RATELIMITED){
					m_PadlockInterface.OnRateLimit();
					m_LockActionPerformed == LockAction.LOCKED;
				}
					SetSynchDirty();
			}
		}
		if (rpc_type == PADLOCK_RESETREQUEST && GetGame().IsServer() && sender) {
			//Rate Limiter server side and hard coded
			if (curtime < m_LastAtemptTime){
				GetGame().AdminLog("[PadLock] Player " + sender.GetName() + "(" + sender.GetPlainId() + ")" + " rate limited " + GetPosition());
				RPCSingleParam(PADLOCK_RESETREQUEST, new Param1<int>(PadLockRespones.RATELIMITED), true, sender);
				if (m_LastAtemptTime < newtime){ //if trying to often the block will just keep increasing by ~2 seconds
					m_LastAtemptTime = newtime;
				}
				return;
			}
			m_LastAtemptTime = curtime + 6000; //Attempts can only be once every 6 seconds
			if (ctx.Read(resetReq)) {
				pin = resetReq.param1;
				if (m_Combination == pin){
					UnlockServer(GetHierarchyParent());
					RPCSingleParam(PADLOCK_RESETREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
				} else {
					RPCSingleParam(PADLOCK_RESETREQUEST, new Param1<int>(PadLockRespones.INVALIDPIN), true, sender);
				}
			}
		}
		if (rpc_type == PADLOCK_OPENREQUEST && GetGame().IsClient()) {
			Param1<bool> openReq;
			if (ctx.Read(openReq)) {
				UIScriptedMenu menu = GetGame().GetUIManager().EnterScriptedMenu(PADLOCK_INTERFACE,NULL);
				PadlockInterface interface = PadlockInterface.Cast(menu);
				interface.SetPadLock(this);
				SetInterface(interface);
			}
		}
		if (rpc_type == PADLOCK_UNLOCKREQUEST && GetGame().IsClient()) {
			if (ctx.Read(UnlockReq) && m_PadlockInterface) {
				if (UnlockReq.param1 == PadLockRespones.SUCCESS){
					m_PadlockInterface.OnSuccess();
					GetGame().GetUIManager().CloseMenu(PADLOCK_INTERFACE);
				}
				if (UnlockReq.param1 == PadLockRespones.INVALIDPIN){
					m_PadlockInterface.OnInvalidPin();
					
				}
				if (UnlockReq.param1 == PadLockRespones.RATELIMITED){
					m_PadlockInterface.OnRateLimit();
				}
			}
		}
		if (rpc_type == PADLOCK_UNLOCKREQUEST && GetGame().IsServer() && sender) {
			//Rate Limiter server side and hard coded
			if (curtime < m_LastAtemptTime){
				GetGame().AdminLog("[PadLock] Player " + sender.GetName() + "(" + sender.GetPlainId() + ")" + " rate limited " + GetPosition());
				RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.RATELIMITED), true, sender);
				if (m_LastAtemptTime < newtime){ //if trying to often the block will just keep increasing by ~2 seconds
					m_LastAtemptTime = newtime;
				}
				return;
			}
			m_LastAtemptTime = curtime + 6000; //Attempts can only be once every 6 seconds
			if (ctx.Read(UnlockReq)) {
				pin = UnlockReq.param1;
				HandleUnlockRequest(pin, sender);
			}
		}
	}
	
	protected void HandleUnlockRequest(int pin, PlayerIdentity sender){
		if (!HasCombination()){
			SetCombination(pin);
			AddRemeberedPlayer(sender);
			RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
			Fence fenceSet = Fence.Cast( GetHierarchyParent() );
			if ( fenceSet ) {
				fenceSet.OpenFence();
			} else {
				ItemBase itemSet = ItemBase.Cast(GetHierarchyParent());
				if (itemSet){
					itemSet.Open();
				}
			}
		} else if (m_Combination == pin){
			AddRemeberedPlayer(sender);
			RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.SUCCESS), true, sender);
			Fence fence = Fence.Cast( GetHierarchyParent() );
			if ( fence ) {
				fence.OpenFence();
			} else {
				ItemBase itemOpn = ItemBase.Cast(GetHierarchyParent());
				if (itemOpn){
					itemOpn.Open();
				}
			}
		} else {
			GetGame().AdminLog("[PadLock] Player " + sender.GetName() + "(" + sender.GetPlainId() + ")" + " tried the wrong pin " + GetPosition());
			RPCSingleParam(PADLOCK_UNLOCKREQUEST, new Param1<int>(PadLockRespones.INVALIDPIN), true, sender);
		}
	}
	
	
	bool CanUnlock(PlayerIdentity player){
		if (!m_RemeberedPlayers || !player ) {return false;}
		return (m_RemeberedPlayers.Find(player.GetId()) != -1);
	}
	
	protected void AddRemeberedPlayer(PlayerIdentity player){
		if (!player) { return; }
		if (!m_RemeberedPlayers) { m_RemeberedPlayers = new TStringArray; }
		if ( m_RemeberedPlayers.Find(player.GetId()) == -1 ){
			m_RemeberedPlayers.Insert(player.GetId());
		}
	}
	
	protected void ClearRemeberedPlayers(){
		m_RemeberedPlayers = new TStringArray;
	}
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundLockOpen() {
		PlaySoundSet( m_Sound, SOUND_LOCK_OPEN, 0, 0 );
	}

	protected void SoundLockClose() {
		PlaySoundSet( m_Sound, SOUND_LOCK_CLOSE, 0, 0 );
	}
	
	override void SetActions()
	{
		super.SetActions();
		
	}
	
}